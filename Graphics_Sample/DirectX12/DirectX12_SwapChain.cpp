#include "DirectX12/DirectX12_SwapChain.h"

namespace DirectX12{

    bool DirectX12_SwapChain::CreateSwapChain(ID3D12CommandQueue* _pCommandQueue, HWND _hWnd, Vector2Int _size)
    {
        HRESULT hr;

        // スワップチェインの初期設定
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 2;
        swapChainDesc.BufferDesc.Width = _size.x;
        swapChainDesc.BufferDesc.Height = _size.y;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = _hWnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapChainDesc.Windowed = true;

        IDXGIFactory* pFactory = nullptr;

        IDXGISwapChain* pTempSwap = nullptr;

        hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));

        // スワップチェインの作成
        hr = pFactory->CreateSwapChain(_pCommandQueue, &swapChainDesc, &pTempSwap);
        if (FAILED(hr))
            return false;

        // GetCurrentBackBufferIndexを使うためにIDXGISwapChain3にする
        hr = pTempSwap->QueryInterface(IID_PPV_ARGS(&m_swapChain));
        if (FAILED(hr))
            return false;

        // 現在のバックバッファのインデックスを取得
        m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

        // 解放処理
        pFactory->Release();
        pFactory = nullptr;

        pTempSwap->Release();
        pTempSwap = nullptr;

        return true;
    }

    bool DirectX12_SwapChain::CreateDescriptorHeap(ID3D12Device* _pDevice)
    {
        HRESULT hr = S_OK;

        // DescriptorHeapの初期設定
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
        ZeroMemory(&heapDesc, sizeof(heapDesc));

        heapDesc.NumDescriptors = 2;                        // バックバッファの数
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;     // レンダーターゲットビューのためのヒープ
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;   // デフォルト
        heapDesc.NodeMask = 0;                              // デフォルト

        // DescriptorHeapの作成
        hr = _pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_descriptorHeap));
        if(FAILED(hr))
            return false;

        // RenderTargetViewのオフセットを取得
        m_rtvDescriptorSize = _pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        // Heap内の開始アドレスを取得
        D3D12_CPU_DESCRIPTOR_HANDLE handle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

        // バックバッファの数だけRTVを作成
        for (int i = 0; i < 2; ++i) 
        {
            // バックバッファを取得
            hr = m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargetView[i]));
            if(FAILED(hr))
                return false;

            // バックバッファをもとにRenderTargetViewを作成
            _pDevice->CreateRenderTargetView(m_renderTargetView[i].Get(), nullptr, handle);

            // 次のアドレスに以降
            handle.ptr += m_rtvDescriptorSize;
        }

        return true;
    }

    bool DirectX12_SwapChain::CreateRenderTaergetView(ID3D12Device*)
    {
        return false;
    }

    bool DirectX12_SwapChain::CreateFence(ID3D12Device* _pDevice)
    {
        HRESULT hr = S_OK;

        // フェンスの作成
        hr = _pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
        if(FAILED(hr))
            return false;

        // カウント
        m_fenceValue = 1;

        // フェンス用のイベントを作成
        m_fenceEvent =  CreateEventEx(nullptr, FALSE, false, EVENT_ALL_ACCESS);

        return true;
    }

    void DirectX12_SwapChain::SetRenderTargetView(ID3D12GraphicsCommandList* _pCommandList)
    {
        D3D12_CPU_DESCRIPTOR_HANDLE handle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

        handle.ptr += (m_frameIndex * m_rtvDescriptorSize);

        _pCommandList->OMSetRenderTargets(1, &handle, false, nullptr);
    }

    void DirectX12_SwapChain::ClearRenderTargetView(ID3D12GraphicsCommandList* _pCommandList, float _clearColor[])
    {
        // バリア初期設定
        D3D12_RESOURCE_BARRIER barrier;

        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // Resourceの状態遷移に対してバリアを設定
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // 特に設定しなければこれでいい
        barrier.Transition.pResource = m_renderTargetView[m_frameIndex].Get();      // バリアを張るResourceを設定
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;              // 状態遷移前のState
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;         // 状態遷移後のState
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // どのサブリソースに対してバリアを張るか

        // バリアを設定
        _pCommandList->ResourceBarrier(1, &barrier);

        // Heap内の開始アドレスを取得
        D3D12_CPU_DESCRIPTOR_HANDLE handle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

        // 現在のRenderTargetViewのアドレスに移動
        handle.ptr += (m_frameIndex * m_rtvDescriptorSize);

        // RendrTargetViewをセット
        _pCommandList->OMSetRenderTargets(1, &handle, false, nullptr);

        // RenderTargetViewを指定色でクリア
        _pCommandList->ClearRenderTargetView(handle, _clearColor, 0, nullptr);
    }

    void DirectX12_SwapChain::WaitFenceEvent(ID3D12CommandQueue* _pCommandQueue, ID3D12GraphicsCommandList* _pCommandList)
    {
        // バリア初期設定 
        D3D12_RESOURCE_BARRIER barrier;

        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // Resourceの状態遷移に対してバリアを設定
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // 特に設定しなければこれでいい
        barrier.Transition.pResource = m_renderTargetView[m_frameIndex].Get();      // バリアを張るResourceを設定
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;        // 状態遷移前のState
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;               // 状態遷移後のState
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // どのサブリソースに対してバリアを張るか

        // バリアを設定
        _pCommandList->ResourceBarrier(1, &barrier);

        // 現在のカウント
        uint64_t fenceValue = m_fenceValue;

        // フェンスにカウントをセット？
        _pCommandQueue->Signal(m_fence.Get(), fenceValue);

        // カウントを増やす
        ++m_fenceValue;

        // 完了したカウントを取得
        uint64_t compValue = m_fence->GetCompletedValue();

        // まだ実行完了してなければ
        if (compValue < fenceValue)
        {   
            // 完了すればイベントをキック
            m_fence->SetEventOnCompletion(fenceValue, m_fenceEvent);

            // イベントがキックされるまで待つ
            WaitForSingleObject(m_fenceEvent, INFINITE);
        }
    }

    void DirectX12_SwapChain::UpdateFrameIndex()
    {
        // 現在のバックバッファのインデックスを取得
        m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
    }
}
