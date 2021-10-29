#pragma once
#ifndef DX12_DEVICE_H
#define DX12_DEVICE_H

#include "GHI/GHI_Device.h"

#include "DirectX12/DirectX12_CommonState.h"
#include "DirectX12/DirectX12_Buffer.h"
#include "DirectX12/DirectX12_SwapChain.h"

namespace DirectX12 
{
	class DX12_Device : public GHI::GHI_Device 
	{
	public:

		void InitDevice() override {};

		void InitStates() override;

		GHI::GHI_SwapChain* CreateSwapChain(HWND _hWnd, Vector2 _size, GHI::GHI_CommandQueue* _pCommandQueue) override;
		GHI::GHI_Shader* CreateShader(GraphicsShaderDesc* _pDesc) override;
		GHI::GHI_Buffer* CreateBuffer(BufferType _bufferType, BufferInfo* _pBufferInfo, void* _pInitData) override;
		GHI::GHI_PipelineState* CreatePipelineState(GHI::GHI_Shader* _pShader,
													BlendType _blendType,
													RasterizerType _rasterizerType,
													DepthStencilType _depthStencilType) override;

		void* Get() override { return m_device; };
		void* GetPP() override { return &m_device; };

	private:

		std::unique_ptr<GHI::GHI_BlendState> CreateBlendState(BlendType _blendType) override;
		std::unique_ptr<GHI::GHI_RasterizerState> CreateRasterizerState(RasterizerType _rasterizerType) override;
		std::unique_ptr<GHI::GHI_DepthStencilState> CreateDepthStencilState(DepthStencilType _depthStencilType) override;

		ID3D12Device* m_device;
	};
}

#endif // !DX12_DEVICE_H
