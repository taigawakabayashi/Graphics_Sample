#include "GHI/GHI_Renderer.h"

bool GHI_Renderer::Init(HWND _hWnd, Vector2 _size)
{
	m_device.CreateDevice(&m_immediateContext);

	m_pipelineStateObject.InitStates(&m_device);

	m_immediateContext.SetPipelineStateObject(&m_pipelineStateObject);

	return false;
}
