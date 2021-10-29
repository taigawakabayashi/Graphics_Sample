#pragma once
#ifndef DX11_DEVICE_H
#define DX11_DEVICE_H

// GHI Interface
#include "GHI/GHI_Device.h"

// DirectX11 Interfaces
#include "DirectX11/DirectX11_Shader.h"
#include "DirectX11/DirectX11_Buffer.h"
#include "DirectX11/DirectX11_CommonState.h"

namespace DirectX11
{
	class DX11_Device : public GHI::GHI_Device
	{
	public:

		void InitDevice() override {}

		void InitStates() override;

		GHI::GHI_Shader* CreateShader(GraphicsShaderDesc* _pDesc) override;
		GHI::GHI_Buffer* CreateBuffer(BufferType _bufferType, BufferInfo* _pBufferInfo, void* _pInitData) override;
		GHI::GHI_PipelineState* CreatePipelineState(GHI::GHI_Shader* _pShader,
													BlendType _blendType,
													RasterizerType _rasterizerType,
													DepthStencilType _depthStencilType) override {};

		void* Get() override { return m_device; }

	private:

		std::unique_ptr<GHI::GHI_BlendState> CreateBlendState(BlendType _blendType) override;
		std::unique_ptr<GHI::GHI_RasterizerState> CreateRasterizerState(RasterizerType _rasterizerType) override;
		std::unique_ptr<GHI::GHI_DepthStencilState> CreateDepthStencilState(DepthStencilType _depthStencilType) override;

		ID3D11Device* m_device;
	};
}

#endif // !DX11_DEVICE_H
