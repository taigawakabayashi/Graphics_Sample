#include "DirectX12/DirectX12_Renderer.h"
#include <wrl/client.h>

namespace DirectX12 
{
	DX12_Renderer::DX12_Renderer()
	{
		m_device = std::make_unique<DX12_Device>();
		m_commandQueue = std::make_unique<DX12_CommandQueue>();
		m_swapChain = std::make_unique<DX12_SwapChain>();
		m_viewPort = std::make_unique<DX12_ViewPort>();
	}

	bool DX12_Renderer::Init(HWND _hWnd, Vector2 _size)
	{
		HRESULT hr = S_OK;

#ifdef _DEBUG
		{
			Microsoft::WRL::ComPtr<ID3D12Debug> pDebugController;

			// デバッグインターフェイスを取得
			hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController));

			if (FAILED(hr))
				return false;

			// デバッグレイヤーを有効化
			pDebugController->EnableDebugLayer();
		}
#endif // _DEBUG

		ID3D12Device** pTempDevice = reinterpret_cast<ID3D12Device**>(m_device->GetPP());

		// デバイスの作成
		hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(pTempDevice));

		ID3D12Device* tempDevice = reinterpret_cast<ID3D12Device*>(m_device->Get());

		// コマンドキューの初期設定
		D3D12_COMMAND_QUEUE_DESC queueDesc;
		ZeroMemory(&queueDesc, sizeof(queueDesc));

		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		// コマンドキューの作成
		hr = tempDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(reinterpret_cast<ID3D12CommandQueue**>(m_commandQueue->GetPP())));

		m_commandQueue->CreateFence(m_device.get());

		m_commandQueue->CreateCommandBuffer(m_device.get());

		m_commandBuffer = m_commandQueue->GetCommandBuffer(0);

		// ビューポートを作成
		m_viewPort->CreateViewPort(_size, Vector2(0, 0));

		// スワップチェインの作成
		std::unique_ptr<GHI::GHI_SwapChain> tempSC(m_device->CreateSwapChain(_hWnd, _size, m_commandQueue.get()));

		m_swapChain = std::move(tempSC);

		m_swapChain->CreateRenderTargetView(m_device.get());

		// パイプラインステートを作成
		m_device->InitStates();
		
		//m_pipelineState.Init(m_device.Get());

		return true;
	}

	void DX12_Renderer::BeforeRender(float _clearColor[])
	{
		m_commandBuffer->ResetCommand();

		m_commandBuffer->ClearRenderTargetView(m_swapChain.get(), _clearColor);

		m_commandBuffer->SetRenderTargetView(m_swapChain.get(), nullptr);

		m_commandBuffer->SetViewPorrt(m_viewPort.get());
	}

	void DX12_Renderer::AfterRender()
	{
		m_commandBuffer->FinishCommand(m_swapChain.get());

		m_commandQueue->ExecuteCommandBuffers();

		m_commandQueue->Swap(m_swapChain.get());
	}
}
