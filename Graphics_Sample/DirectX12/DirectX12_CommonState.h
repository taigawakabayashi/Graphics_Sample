#pragma once
#ifndef DX12_COMMONSTATE_H
#define DX12_COMMONSTATE_H

#include <d3d12.h>

#include "GHI/GHI_CommonState.h"

namespace DirectX12 
{
	class DX12_BlendState : public GHI::GHI_BlendState
	{
	public:

		void* Get() override { return &m_state; }

	private:

		D3D12_BLEND_DESC m_state;
	};

	class DX12_RasterizerState : public GHI::GHI_RasterizerState
	{
	public:

		void* Get() override { return &m_state; }

	private:

		D3D12_RASTERIZER_DESC m_state;
	};

	class DX12_DepthStencilState : public GHI::GHI_DepthStencilState
	{
	public:

		void* Get() override { return &m_state; }

	private:

		D3D12_DEPTH_STENCIL_DESC m_state;
	};

	class DX12_PipelineState : public GHI::GHI_PipelineState
	{
	public:

		void* Get(uint32_t hash) override;
		void* GetRootSignature(uint32_t hash) override;

	private:

		std::unordered_map<uint32_t, ID3D12PipelineState*> m_pipelineStates;
		std::unordered_map<uint32_t, ID3D12RootSignature*> m_rootSignature;
	};
}
#endif // !DX12_COMMONSTATE_H
