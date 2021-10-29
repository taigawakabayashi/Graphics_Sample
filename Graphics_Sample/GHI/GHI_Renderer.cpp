#include "GHI/GHI_Renderer.h"
#include "DirectX12/DirectX12_Device.h"

namespace GHI
{
	bool GHI_Renderer::Init(HWND _hWnd, Vector2 _size)
	{
		m_device = std::make_unique<DirectX12::DX12_Device>();

		m_device->InitStates();

		return false;
	}
}
