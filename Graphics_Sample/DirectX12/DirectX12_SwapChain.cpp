#include "DirectX12/DirectX12_SwapChain.h"
#include "DirectX12_GraphicsManager.h"
#include "DirectX12//DirectX12_RenderTargetView.h"

namespace DirectX12 
{
	void DX12_SwapChain::CreateRenderTargetView(GHI::GHI_Device* _pDevice)
	{
		m_renderTagetView = std::make_unique<DX12_RenderTaergetView>();

		m_renderTagetView->Create(_pDevice, this);
	}

	bool DirectX12_SwapChain::CreateSwapChain(ID3D12CommandQueue* _pCommandQueue, HWND _hWnd, Vector2Int _size)
	{
		HRESULT hr;

		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.Width = _size.x;
		desc.Height = _size.y;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Stereo = false;                                // フルスクリーン指定
		desc.SampleDesc = DXGI_SAMPLE_DESC{ 1,0 };
		desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;            // バッファ識別
		desc.BufferCount = 2;								// バックバッファ数
		desc.Scaling = DXGI_SCALING_STRETCH;                // バックバッファのスケーリング指定
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;    // スワップ時のバッファの扱い
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;        // アルファモード??
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;// 動作オプション (フルスクリーン切り替え可)

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

		IDXGIFactory4* pFactory = nullptr;

		IDXGISwapChain1* pTempSwap = nullptr;

		hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));

		// スワップチェインの作成
		hr = pFactory->CreateSwapChainForHwnd(
			_pCommandQueue,
			_hWnd,
			&desc,
			nullptr,
			nullptr,
			&pTempSwap);
		if (FAILED(hr))
			return false;

		// GetCurrentBackBufferIndexを使うためにIDXGISwapChain3にする
		hr = pTempSwap->QueryInterface(IID_PPV_ARGS(&m_swapChain));
		if (FAILED(hr))
			return false;

		// 現在のバックバッファのインデックスを取得
		m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

		m_swapChain->AddRef();

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
		hr = _pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_rtvDescriptorHeap));
		if (FAILED(hr))
			return false;

		m_rtvDescriptorHeap->SetName(L"SwapChain_Heap");

		// RenderTargetViewのオフセットを取得
		m_rtvDescriptorSize = _pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		// Heap内の開始アドレスを取得
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		// バックバッファの数だけRTVを作成
		for (int i = 0; i < 2; ++i)
		{
			// バックバッファを取得
			hr = m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargetView[i]));
			if (FAILED(hr))
				return false;

			// バックバッファをもとにRenderTargetViewを作成
			_pDevice->CreateRenderTargetView(m_renderTargetView[i].Get(), nullptr, handle);

			// 次のアドレスに以降
			handle.ptr += m_rtvDescriptorSize;
		}

		m_renderTargetView[0]->SetName(L"SwapChain_RTV_0");
		m_renderTargetView[1]->SetName(L"SwapChain_RTV_1");

		return true;
	}

	bool DirectX12_SwapChain::CreateRenderTaergetView(ID3D12Device*)
	{
		return false;
	}

	bool DirectX12_SwapChain::CreateDepthStencilView(ID3D12Device* _pDevice, Vector2Int _size)
	{
		HRESULT hr = S_OK;

		//深度バッファ用のデスクリプタヒープの作成
		D3D12_DESCRIPTOR_HEAP_DESC depthDesc{};
		depthDesc.NumDescriptors		= 1;
		depthDesc.Type					= D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		depthDesc.Flags					= D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		depthDesc.NodeMask				= 0;
		hr = _pDevice->CreateDescriptorHeap(&depthDesc, IID_PPV_ARGS(&m_dsvDescriptorHeap));
		if (FAILED(hr)) 
			return false;
		

		//深度バッファの作成
		D3D12_HEAP_PROPERTIES heapProp{};
		D3D12_RESOURCE_DESC resourceDesc{};
		D3D12_CLEAR_VALUE clearValue{};

		heapProp.Type					= D3D12_HEAP_TYPE_DEFAULT;
		heapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		heapProp.CreationNodeMask		= 0;
		heapProp.VisibleNodeMask		= 0;

		resourceDesc.Dimension			= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Width				= _size.x;
		resourceDesc.Height				= _size.y;
		resourceDesc.DepthOrArraySize	= 1;
		resourceDesc.MipLevels			= 0;
		resourceDesc.Format				= DXGI_FORMAT_R32_TYPELESS;
		resourceDesc.Layout				= D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.SampleDesc.Count	= 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Flags				= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		clearValue.Format				= DXGI_FORMAT_D32_FLOAT;
		clearValue.DepthStencil.Depth	= 1.0f;
		clearValue.DepthStencil.Stencil = 0;

		hr = _pDevice->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clearValue, IID_PPV_ARGS(&m_depthStencilView));
		if (FAILED(hr))
			return false;


		//深度バッファのビューの作成
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};

		dsvDesc.ViewDimension			= D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Format					= DXGI_FORMAT_D32_FLOAT;
		dsvDesc.Texture2D.MipSlice		= 0;
		dsvDesc.Flags					= D3D12_DSV_FLAG_NONE;

		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		_pDevice->CreateDepthStencilView(m_depthStencilView.Get(), &dsvDesc, handle);

		return true;
	}

	void DirectX12_SwapChain::SetRenderTargetView(ID3D12GraphicsCommandList* _pCommandList)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		handle.ptr += static_cast<SIZE_T>(m_frameIndex * m_rtvDescriptorSize);

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
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		// 現在のRenderTargetViewのアドレスに移動
		rtvHandle.ptr += static_cast<SIZE_T>(m_frameIndex * m_rtvDescriptorSize);

		// RenderTargetViewを指定色でクリア
		_pCommandList->ClearRenderTargetView(rtvHandle, _clearColor, 0, nullptr);

		// 
		_pCommandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		// RendrTargetViewをセット
		_pCommandList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);
	}

	void DirectX12_SwapChain::SetResourceBarrier(ID3D12GraphicsCommandList* _pCommandList)
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
	}

	void DirectX12_SwapChain::UpdateFrameIndex()
	{
		// 現在のバックバッファのインデックスを取得
		m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
	}
	
}
