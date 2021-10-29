#pragma once
#ifndef DEVICE_H
#define DEVICE_H

#include <wrl/client.h>
#include "SwitchingAPI.h"

#include "GHI/GHI_CommonState.h"
#include "GHI/GHI_Shader.h"
#include "GHI/GHI_Buffer.h"
#include "GHI/GHI_SwapChain.h"
#include "GHI/GHI_DepthStencilView.h"

namespace GHI 
{
	class GHI_CommandQueue;
	
	class GHI_Device 
	{
	public:

		virtual void InitDevice() = 0;

		virtual void InitStates() = 0;

		virtual GHI_SwapChain* CreateSwapChain(HWND _hWnd, Vector2 _size, GHI_CommandQueue* _pCommandQueue) = 0;
		virtual GHI_Shader* CreateShader(GraphicsShaderDesc* _pDesc) = 0;
		virtual GHI_Buffer* CreateBuffer(BufferType _bufferType, BufferInfo* _pBufferInfo, void* _pInitData) = 0;
		virtual GHI_PipelineState* CreatePipelineState(GHI_Shader* _pShader, 
													   BlendType _blendType, 
													   RasterizerType _rasterizerType, 
													   DepthStencilType _depthStencilType) = 0;

		virtual void* Get() = 0;
		virtual void* GetPP() = 0;

		GHI_Shader* GetShader() { return m_shader.get(); }
		GHI_PipelineState* GetPipelineState() { return m_pipelineState.get(); }

		virtual ~GHI_Device(){}

	protected:

		virtual std::unique_ptr<GHI_BlendState> CreateBlendState(BlendType _blendType) = 0;
		virtual std::unique_ptr<GHI_RasterizerState> CreateRasterizerState(RasterizerType _rasterizerType) = 0;
		virtual std::unique_ptr<GHI_DepthStencilState> CreateDepthStencilState(DepthStencilType _depthStencilType) = 0;

		std::unique_ptr<GHI_Shader> m_shader;
		std::unique_ptr<GHI_PipelineState> m_pipelineState;
	};
}
#ifdef IS_DIRECTX11

class Device 
{
public:

	HRESULT CreateDevice(ImmediateContext* _pImmediateContext);

	HRESULT CreateBuffer(uint32_t _byteWidth, void* _initData, BufferType _bufferType, Buffer* _pBuffer);
	HRESULT CreateIABuffer(uint32_t _byteWidth, void* _initData, IABufferType _bufferType, IABuffer* _pBuffer);
	HRESULT CreateTexture();
	HRESULT CreateRenderTargetView();
	HRESULT CreateDepthStencilView();

	ID3D11Device* Get() { return m_device.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
};

#elif defined IS_DIRECTX12

class Device
{
public:

	HRESULT CreateDevice(ImmediateContext* _pImmediateContext);

	HRESULT CreateBuffer(uint32_t _byteWidth, void* _initData, BufferType _bufferType, Buffer* _pBuffer);
	HRESULT CreateIABuffer(uint32_t _byteWidth, void* _initData, IABufferType _bufferType, IABuffer* _pBuffer);
	HRESULT CreateTexture();
	HRESULT CreateRenderTargetView();
	HRESULT CreateDepthStencilView();

	ID3D12Device* Get() { return m_device.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12Device> m_device;
};

#endif

#endif // !DEVICE_H
