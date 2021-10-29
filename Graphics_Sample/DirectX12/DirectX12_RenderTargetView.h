#pragma once
#ifndef DX12_RTV_H
#define DX12_RTV_H

#include <d3d12.h>

#include "GHI/GHI_RenderTargetView.h"

namespace DirectX12 
{
	class DX12_RenderTaergetView : public GHI::GHI_RenderTargetView
	{
	public:

		void Create(GHI::GHI_Device* _pDevice, GHI::GHI_SwapChain* _pSwapChain) override;

		void* Get(uint32_t _index) override { return m_renderTargetView[_index]; }
		void* GetPP(uint32_t _index) override { return &m_renderTargetView[_index]; }

		SIZE_T GetDescriptorHandle(uint32_t _index) override;

	private:

		ID3D12DescriptorHeap*	m_rtvDescriptorHeap = nullptr;
		ID3D12Resource*			m_renderTargetView[2] = { nullptr, nullptr };

		uint32_t				m_rtvDescriptorSize = 0;
	};
}

#endif // !DX12_RTV_H
