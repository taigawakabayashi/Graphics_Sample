#pragma once
#ifndef GHI_RENDERER_H
#define GHI_RENDERER_H

#include "GHI/GHI_Device.h"
#include "Utility/Math.h"

class GHI_Renderer 
{
public:

	bool Init(HWND _hWnd, Vector2 _size);

	Device* GetDevice() { return &m_device; }
	ImmediateContext* GetImmidiateContext() { return &m_immediateContext; }

private:

	Device				m_device;
	ImmediateContext	m_immediateContext;
	PipelineStateObject m_pipelineStateObject;
};

#endif // !GHI_RENDERER_H
