#pragma once
#ifndef DX11_COMMONSTATE_H
#define DX11_COMMONSTATE_H

#include "GHI/GHI_CommonState.h"

namespace DirectX11 
{
	class DX11_BlendState : public GHI::GHI_BlendState 
	{
	public:

		void* Get() override { return m_state; }

	private:

		ID3D11BlendState* m_state;
	};

	class DX11_RasterizerState : public GHI::GHI_RasterizerState
	{
	public:

		void* Get() override { return m_state; }

	private:

		ID3D11RasterizerState* m_state;
	};

	class DX11_DepthStencilState : public GHI::GHI_DepthStencilState
	{
	public:

		void* Get() override { return m_state; }

	private:

		ID3D11DepthStencilState* m_state;
	};

	class DX11_PipelineState : public GHI::GHI_PipelineState 
	{
	public:

		void* Get(uint32_t) override { return nullptr; };
		void* GetRootSignature(uint32_t) override { return nullptr; };
	};
}

#endif // !DX11_COMMONSTATE_H
