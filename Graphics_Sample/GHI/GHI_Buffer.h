#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include <wrl/client.h>
#include "SwitchingAPI.h"

enum class BufferType 
{
	VERTEX,
	INDEX,
	CONSTANT,
	STRUCTURED
};

class Context;

#ifdef IS_DIRECTX11

class Buffer 
{
public:

	HRESULT Map(Context* _pContext,void* _pData);
	void Unmap(Context* _pContext);

	ID3D11Buffer* Get() { return m_buffer.Get(); }
	ID3D11Buffer** GetAddressOf() { return m_buffer.GetAddressOf(); }

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
};

#elif defined IS_DIRECTX12

class Buffer
{
public:


private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;

};
#endif

#endif // !BUFFER_H
