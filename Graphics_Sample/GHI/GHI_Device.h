#pragma once
#ifndef DEVICE_H
#define DEVICE_H

#include <wrl/client.h>
#include "SwitchingAPI.h"
#include "GHI/GHI_Context.h"
#include "GHI/GHI_CommonState.h"

#ifdef IS_DIRECTX11

class Device 
{
public:

	HRESULT CreateDevice(ImmediateContext* _pImmediateContext);

	HRESULT CreateBuffer(uint32_t _byteWidth, void* _initData, BufferType _bufferType, Buffer* _pBuffer);
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
	HRESULT CreateTexture();
	HRESULT CreateRenderTargetView();
	HRESULT CreateDepthStencilView();

	ID3D12Device* Get() { return m_device.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12Device> m_device;
};

#endif

#endif // !DEVICE_H
