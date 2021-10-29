#pragma once
#ifndef DX12_DSV_H
#define DX12_DSV_H

#include <d3d12.h>

#include "GHI/GHI_DepthStencilView.h"

namespace DirectX12 
{
	class DX12_DepthStencilView : public GHI::GHI_DepthStencilView
	{
	public:

		void* Get() override { return m_depthStencilView; }

	protected:

		ID3D12DescriptorHeap* m_dsvDescriptorHeap = nullptr;
		ID3D12Resource* m_depthStencilView = nullptr;
	};
}

#endif // !DX12_DSV_H
