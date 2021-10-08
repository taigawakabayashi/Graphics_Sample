#include "DirectX12/DirectX12_SwapChain.h"

namespace DirectX12{

    bool DirectX12_SwapChain::CreateSwapChain(ID3D12CommandQueue* _pCommandQueue, HWND _hWnd, Vector2Int _size)
    {
        HRESULT hr;

        // �X���b�v�`�F�C���̏����ݒ�
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

        // �X���b�v�`�F�C���̍쐬
        hr = pFactory->CreateSwapChain(_pCommandQueue, &swapChainDesc, &pTempSwap);
        if (FAILED(hr))
            return false;

        // GetCurrentBackBufferIndex���g�����߂�IDXGISwapChain3�ɂ���
        hr = pTempSwap->QueryInterface(IID_PPV_ARGS(&m_swapChain));
        if (FAILED(hr))
            return false;

        // ���݂̃o�b�N�o�b�t�@�̃C���f�b�N�X���擾
        m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

        // �������
        pFactory->Release();
        pFactory = nullptr;

        pTempSwap->Release();
        pTempSwap = nullptr;

        return true;
    }

    bool DirectX12_SwapChain::CreateDescriptorHeap(ID3D12Device* _pDevice)
    {
        HRESULT hr = S_OK;

        // DescriptorHeap�̏����ݒ�
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
        ZeroMemory(&heapDesc, sizeof(heapDesc));

        heapDesc.NumDescriptors = 2;                        // �o�b�N�o�b�t�@�̐�
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;     // �����_�[�^�[�Q�b�g�r���[�̂��߂̃q�[�v
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;   // �f�t�H���g
        heapDesc.NodeMask = 0;                              // �f�t�H���g

        // DescriptorHeap�̍쐬
        hr = _pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_descriptorHeap));
        if(FAILED(hr))
            return false;

        // RenderTargetView�̃I�t�Z�b�g���擾
        m_rtvDescriptorSize = _pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        // Heap���̊J�n�A�h���X���擾
        D3D12_CPU_DESCRIPTOR_HANDLE handle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

        // �o�b�N�o�b�t�@�̐�����RTV���쐬
        for (int i = 0; i < 2; ++i) 
        {
            // �o�b�N�o�b�t�@���擾
            hr = m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargetView[i]));
            if(FAILED(hr))
                return false;

            // �o�b�N�o�b�t�@�����Ƃ�RenderTargetView���쐬
            _pDevice->CreateRenderTargetView(m_renderTargetView[i].Get(), nullptr, handle);

            // ���̃A�h���X�Ɉȍ~
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

        // �t�F���X�̍쐬
        hr = _pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
        if(FAILED(hr))
            return false;

        // �J�E���g
        m_fenceValue = 1;

        // �t�F���X�p�̃C�x���g���쐬
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
        // �o���A�����ݒ�
        D3D12_RESOURCE_BARRIER barrier;

        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // Resource�̏�ԑJ�ڂɑ΂��ăo���A��ݒ�
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // ���ɐݒ肵�Ȃ���΂���ł���
        barrier.Transition.pResource = m_renderTargetView[m_frameIndex].Get();      // �o���A�𒣂�Resource��ݒ�
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;              // ��ԑJ�ڑO��State
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;         // ��ԑJ�ڌ��State
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // �ǂ̃T�u���\�[�X�ɑ΂��ăo���A�𒣂邩

        // �o���A��ݒ�
        _pCommandList->ResourceBarrier(1, &barrier);

        // Heap���̊J�n�A�h���X���擾
        D3D12_CPU_DESCRIPTOR_HANDLE handle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();

        // ���݂�RenderTargetView�̃A�h���X�Ɉړ�
        handle.ptr += (m_frameIndex * m_rtvDescriptorSize);

        // RendrTargetView���Z�b�g
        _pCommandList->OMSetRenderTargets(1, &handle, false, nullptr);

        // RenderTargetView���w��F�ŃN���A
        _pCommandList->ClearRenderTargetView(handle, _clearColor, 0, nullptr);
    }

    void DirectX12_SwapChain::WaitFenceEvent(ID3D12CommandQueue* _pCommandQueue, ID3D12GraphicsCommandList* _pCommandList)
    {
        // �o���A�����ݒ� 
        D3D12_RESOURCE_BARRIER barrier;

        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // Resource�̏�ԑJ�ڂɑ΂��ăo���A��ݒ�
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // ���ɐݒ肵�Ȃ���΂���ł���
        barrier.Transition.pResource = m_renderTargetView[m_frameIndex].Get();      // �o���A�𒣂�Resource��ݒ�
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;        // ��ԑJ�ڑO��State
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;               // ��ԑJ�ڌ��State
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // �ǂ̃T�u���\�[�X�ɑ΂��ăo���A�𒣂邩

        // �o���A��ݒ�
        _pCommandList->ResourceBarrier(1, &barrier);

        // ���݂̃J�E���g
        uint64_t fenceValue = m_fenceValue;

        // �t�F���X�ɃJ�E���g���Z�b�g�H
        _pCommandQueue->Signal(m_fence.Get(), fenceValue);

        // �J�E���g�𑝂₷
        ++m_fenceValue;

        // ���������J�E���g���擾
        uint64_t compValue = m_fence->GetCompletedValue();

        // �܂����s�������ĂȂ����
        if (compValue < fenceValue)
        {   
            // ��������΃C�x���g���L�b�N
            m_fence->SetEventOnCompletion(fenceValue, m_fenceEvent);

            // �C�x���g���L�b�N�����܂ő҂�
            WaitForSingleObject(m_fenceEvent, INFINITE);
        }
    }

    void DirectX12_SwapChain::UpdateFrameIndex()
    {
        // ���݂̃o�b�N�o�b�t�@�̃C���f�b�N�X���擾
        m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
    }
}