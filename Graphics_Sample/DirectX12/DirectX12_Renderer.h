#pragma once
#ifndef DX12_RENDERER_H
#define DX12_RENDERER_H

#include "GHI/GHI_Renderer.h"

#include "DirectX12_Device.h"
#include "DirectX12_Context.h"
#include "DirectX12_ViewPort.h"

namespace DirectX12 
{
	class DX12_Renderer : public GHI::GHI_Renderer
	{
	public:

		DX12_Renderer();

		bool Init(HWND _hWnd, Vector2 _size) override;

		void BeforeRender(float _clearColor[]) override;

		void AfterRender() override;

	private:


	};
}

#endif // !DX12_RENDERER_H
