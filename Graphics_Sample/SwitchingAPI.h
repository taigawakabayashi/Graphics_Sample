#pragma once
#ifndef SWITCHINGAPI_H
#define SWITCHINGAPI_H
#include <cinttypes>

enum class GraphicsAPI
{
	DIRECTX11,
	DIRECTX12,
	OPENGL,
	VULKAN,
};

// Graphics API
#define USE_DIRECTX11 0
#define USE_DIRECTX12 1
#define USE_OPENGL 2
#define USE_VULKAN 3

// Using Graphics API
#define USINGAPI USE_DIRECTX12

// DirectX11
#if (USINGAPI == USE_DIRECTX11)

#include <d3d11.h>

#define IS_DIRECTX11

// DirectX12
#elif USINGAPI == USE_DIRECTX12

#include <d3d12.h>

#define IS_DIRECTX12

// OpenGL
#elif USINGAPI == USE_OPENGL

#define IS_OPENGL

// Vulkan
#elif USINGAPI == USE_VULKAN

#define IS_VULKAN

#endif

#endif // !SWITCHINGAPI_H
