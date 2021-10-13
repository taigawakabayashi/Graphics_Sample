#include <dxgi.h>

#include <DirectX12/DirectX12_GraphicsManager.h>

#pragma comment (lib,"d3d12.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"D3DCompiler.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dxguid.lib")

namespace DirectX12 {

	bool DirectX12_GraphicsMng::Init(HWND _hWnd, Vector2Int _size)
	{
		HRESULT hr = S_OK;
	
#ifdef _DEBUG
		{
			ComPtr<ID3D12Debug> pDebugController;

			// デバッグインターフェイスを取得
			hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController));
	
			if(FAILED(hr))
				return false;
			
			// デバッグレイヤーを有効化
			pDebugController->EnableDebugLayer();
		}
#endif // _DEBUG
	
		/*ComPtr<IDXGIFactory> pFactory;

		hr = CreateDXGIFactory(IID_PPV_ARGS(&pFactory));*/

		// デバイスの作成
		hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));
	
		// コマンドキューの初期設定
		D3D12_COMMAND_QUEUE_DESC queueDesc;
		ZeroMemory(&queueDesc, sizeof(queueDesc));
	
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	
		// コマンドキューの作成
		hr = m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf()));
		
		if(FAILED(hr))
			return false;

		m_commandQueue->SetName(L"GM_CommandQueue");

		// コマンドキュー用のフェンスイベント
		m_fenceEvent = CreateEvent(nullptr, FALSE, false, nullptr);

		// コマンドキュー用のフェンスを作成
		hr = m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
		if(FAILED(hr))
			return false;

		m_fence->SetName(L"GM_Queue_Fence");

		// キューとアロケータのTypeを合わせる
		D3D12_COMMAND_LIST_TYPE type = queueDesc.Type;

		// コマンドアロケータの作成
		hr = m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&m_commandAllocaotr));

		if(FAILED(hr))
			return false;

		m_commandAllocaotr->SetName(L"GM_CommandAllocator");

		// コマンドリストの作成
		hr = m_device->CreateCommandList(0, type, m_commandAllocaotr.Get(), nullptr, IID_PPV_ARGS(&m_commandList));

		if (SUCCEEDED(hr)) 
		{
			// 初期化時には一旦Closeする
			m_commandList->Close();

			m_commandList->SetName(L"GM_CommandList");
		}
		else if (FAILED(hr)) 
		{
			return false;
		}

		// ビューポートを作成
		m_viewPort.CreateViewPort(_size, Vector2(0,0));

		// スワップチェインの作成
		m_swapChain.CreateSwapChain(m_commandQueue.Get(), _hWnd, _size);

		// スワップチェイン用のDescriptorHeapを作成
		m_swapChain.CreateDescriptorHeap(m_device.Get());

		m_swapChain.CreateDepthStencilView(m_device.Get(), _size);

		// パイプラインステートを作成
		m_pipelineState.Init(m_device.Get());

		return true;
	}

	void DirectX12_GraphicsMng::Uninit()
	{
		// コマンドアロケータをリセット
		m_commandAllocaotr->Reset();

		// コマンドリストをリセット
		m_commandList->Reset(m_commandAllocaotr.Get(), nullptr);

		m_commandQueue->Release();
		m_commandQueue->Release();
		m_commandQueue->Release();
		m_commandQueue->Release();
		m_commandQueue->Release();
	}

	void DirectX12_GraphicsMng::ResetCommand()
	{
		// コマンドアロケータをリセット
		m_commandAllocaotr->Reset();

		// コマンドリストをリセット
		m_commandList->Reset(m_commandAllocaotr.Get(), nullptr);

		// 現在のバックバッファのインデックスを取得
		m_swapChain.UpdateFrameIndex();
	}

	void DirectX12_GraphicsMng::SetViewPort()
	{
		// ビューポートをセット
		m_viewPort.SetViewPort(m_commandList.Get());
	}

	void DirectX12_GraphicsMng::SetPipelineState()
	{
		// パイプラインステートをセット
		m_pipelineState.SetPipelineState(m_commandList.Get());
	}

	void DirectX12_GraphicsMng::ClearRenderTargetView(float _clearColor[])
	{
		// レンダーターゲットビューを指定色でクリア
		m_swapChain.ClearRenderTargetView(m_commandList.Get(), _clearColor);
	}

	void DirectX12_GraphicsMng::WaitDrawFinised()
	{
		// バリアの設置
		m_swapChain.SetResourceBarrier(m_commandList.Get());

		// コマンドの受付を終了する
		m_commandList->Close();

		// コマンドをまとめる
		ID3D12CommandList* pCommandList[] = { m_commandList.Get() };

		// コマンドキューで実行
		m_commandQueue->ExecuteCommandLists(1, pCommandList);

		// コマンドキューが実行し終えるまで待つ
		WaitForCommandQueue();

		// Swap
		m_swapChain.GetSwapChain()->Present(1, 0);
	}

	void DirectX12_GraphicsMng::WaitForCommandQueue()
	{
		static uint64_t flame = 0;

		// flameの値になったらイベントをキック
		m_fence->SetEventOnCompletion(flame, m_fenceEvent);

		m_commandQueue->Signal(m_fence.Get(), flame);

		// イベントがキックされるまで待機
		WaitForSingleObject(m_fenceEvent, INFINITE);

		++flame;
	}

	void BeforeRender(float _clearColor[])
	{
		// コマンドをリセット
		DirectX12_GraphicsMng::GetInstance()->ResetCommand();

		// レンダーターゲットビューのクリア
		DirectX12_GraphicsMng::GetInstance()->ClearRenderTargetView(_clearColor);

		// ビューポートをセット
		DirectX12_GraphicsMng::GetInstance()->SetViewPort();

		// パイプラインステートをセット
		DirectX12_GraphicsMng::GetInstance()->SetPipelineState();
	}

	void AfterRender()
	{
		// 描画終了まで待機
		DirectX12_GraphicsMng::GetInstance()->WaitDrawFinised();
	}
}
