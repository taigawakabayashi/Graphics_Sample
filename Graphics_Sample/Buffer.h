#pragma once
#ifndef BUFFER_H
#define BUFFER_H
#include "Game.h"

#ifdef IS_DIRECTX11

#include <d3d11.h>

#elif defined IS_DIRECTX12

#include <d3d12.h>

#endif

#include <wrl/client.h>

enum class BufferType 
{
	VERTEX,
	INDEX,
	CONSTANT,
	BACK,
	DEPTH,
	STRUCTURED
};

class Buffer 
{
public:

	void CreateBuffer();

private:

#ifdef IS_DIRECTX11

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

#elif defined IS_DIRECTX12

	Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;

#endif
};


#endif // !BUFFER_H
