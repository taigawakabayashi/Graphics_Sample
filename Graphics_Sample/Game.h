#pragma once
#ifndef GAME_H
#define GAME_H

#include <DirectX11/DirectX11_GraphicsManager.h>
#include <DirectX12/DirectX12_GraphicsManager.h>
#include "Object.h"

enum class GraphicsAPI
{
	DIRECTX11,
	DIRECTX12,
	OPENGL,
	VULKAN,
};

namespace Render 
{
	bool Init(HWND _hWnd, Vector2Int _size, GraphicsAPI _api);

	void Input(uint64_t);
	void Update(uint64_t _deltaTime);
	void Draw(uint64_t _deltaTime);

	void Uninit();

	class Renderer 
	{
	public:

		virtual bool Init(HWND _hWnd, Vector2Int _size) = 0;
		virtual void Input(uint64_t _deltaTime) = 0;
		virtual void Update(uint64_t _deltaTime) = 0;
		virtual void Draw(uint64_t _deltaTime) = 0;
		virtual void Uninit() = 0;

		virtual void BeforeRender(float _clearColor[]) = 0;
		virtual void AfterRender() = 0;

		virtual ~Renderer(){}

	protected:

		Object* m_obj = nullptr;

		// Camera
		Vector3 m_eye = Vector3(0.0f, 2.0f, -5.0f);
		Vector3 m_up = Vector3::up();
		Vector3 m_lookat = Vector3::zero();

		struct CameraMatrix
		{
			XMMATRIX view;
			XMMATRIX projection;
		};
	};

	class DirectX11_Renderer : public Renderer
	{
	public:

		bool Init(HWND _hWnd, Vector2Int _size) override;
		void Input(uint64_t) override {};
		void Update(uint64_t _deltaTime) override;
		void Draw(uint64_t _deltaTime) override;
		void Uninit() override;

		virtual void BeforeRender(float _clearColor[]) override;
		virtual void AfterRender() override;

	private:

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_cameraBuffer = nullptr;
	};

	class DirectX12_Renderer : public Renderer
	{
	public:

		bool Init(HWND _hWnd, Vector2Int _size) override;
		void Input(uint64_t) override {};
		void Update(uint64_t _deltaTime) override;
		void Draw(uint64_t _deltaTime) override;
		void Uninit() override;

		virtual void BeforeRender(float _clearColor[]) override;
		virtual void AfterRender() override;

	private:

		Microsoft::WRL::ComPtr<ID3D12Resource> m_cameraBuffer = nullptr;
	};
}
#endif // !GAME_H
