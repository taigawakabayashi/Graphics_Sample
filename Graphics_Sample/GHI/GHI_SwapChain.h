#pragma once
#ifndef GHI_SWAPCHAIN_H
#define GHI_SWAPCHAIN_H

#include <dxgi1_6.h>
#include <memory>

#include "GHI/GHI_RenderTargetView.h"

namespace GHI 
{
	class GHI_SwapChain 
	{
	public:

		virtual void CreateRenderTargetView(GHI_Device* _pDevice) = 0;

		void UpdateBackBufferIndex() { m_currentIndex = m_swapChain->GetCurrentBackBufferIndex(); };
		void Present() { m_swapChain->Present(1, 0); }

		IDXGISwapChain3* Get() { return m_swapChain; }
		IDXGISwapChain3** GetPP() { return &m_swapChain; }
		uint32_t GetCurretnIndex() { return m_currentIndex; }

		virtual void* GetCurrentRTV() = 0;
		virtual SIZE_T GetDescriptorHandle() = 0;

		virtual ~GHI_SwapChain() {}

	protected:

		IDXGISwapChain3*						m_swapChain = nullptr;
		std::unique_ptr<GHI_RenderTargetView>	m_renderTagetView = nullptr;

		uint32_t m_currentIndex = 0;
	};
}

#endif // !GHI_SWAPCHAIN_H
