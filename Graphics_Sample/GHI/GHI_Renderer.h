#pragma once
#ifndef GHI_RENDERER_H
#define GHI_RENDERER_H

#include "GHI/GHI_Device.h"
#include "GHI/GHI_Context.h"
#include "Utility/Math.h"

namespace GHI
{
	class GHI_Renderer
	{
	public:

		virtual bool Init(HWND _hWnd, Vector2 _size);

		virtual void BeforeRender(float _clearColor[]) = 0;

		virtual void AfterRender() = 0;

		GHI_Device* GetDevice() { return m_device.get(); }

	protected:

		std::unique_ptr<GHI_Device> m_device;
		std::unique_ptr<GHI_CommandQueue> m_commandQueue;
		std::unique_ptr<GHI_SwapChain> m_swapChain;
		std::unique_ptr<GHI_ViewPort> m_viewPort;

		GHI_CommandBuffer* m_commandBuffer;

		std::unique_ptr<GHI_Buffer> m_vertexBuffer;
		std::unique_ptr<GHI_Buffer> m_indexBuffer;
		std::unique_ptr<GHI_Buffer> m_constantBuffer;

	};
}

#endif // !GHI_RENDERER_H
