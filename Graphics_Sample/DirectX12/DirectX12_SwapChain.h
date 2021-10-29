#pragma once
#ifndef DX12_SWAP_H
#define DX12_SWAP_H

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

#include "GHI/GHI_SwapChain.h"

#include <Utility/Math.h>

namespace DirectX12 
{
	class DX12_SwapChain : public  GHI::GHI_SwapChain 
	{
	public:

		void CreateRenderTargetView(GHI::GHI_Device* _pDevice) override;

		void* GetCurrentRTV() override { return m_renderTagetView->Get(m_currentIndex); }

		SIZE_T GetDescriptorHandle() override { return m_renderTagetView->GetDescriptorHandle(m_currentIndex); }

	private:
	};

	using Microsoft::WRL::ComPtr;

	class DirectX12_SwapChain 
	{
	public:

		bool CreateSwapChain(ID3D12CommandQueue* _pCommandQueue, HWND _hWnd, Vector2Int _size);

		bool CreateDescriptorHeap(ID3D12Device* _pDevice);

		bool CreateRenderTaergetView(ID3D12Device* _pDevice);

		bool CreateDepthStencilView(ID3D12Device* _pDevice, Vector2Int _size);

		void SetRenderTargetView(ID3D12GraphicsCommandList* _pCommandList);

		void ClearRenderTargetView(ID3D12GraphicsCommandList* _pCommandList, float _clearColor[]);

		void SetResourceBarrier(ID3D12GraphicsCommandList* _pCommandList);

		void UpdateFrameIndex();

		IDXGISwapChain3* GetSwapChain() { return m_swapChain.Get(); }

	private:

		ComPtr<IDXGISwapChain3>				m_swapChain = nullptr;
		ComPtr<ID3D12DescriptorHeap>        m_rtvDescriptorHeap = nullptr;
		ComPtr<ID3D12Resource>				m_renderTargetView[2] = { nullptr, nullptr };

		ComPtr<ID3D12DescriptorHeap>        m_dsvDescriptorHeap = nullptr;
		ComPtr<ID3D12Resource>				m_depthStencilView = nullptr;

		uint64_t							m_frameIndex = 0;
		uint64_t							m_rtvDescriptorSize = 0;
	};
}

#endif // !DX12_SWAP_H
