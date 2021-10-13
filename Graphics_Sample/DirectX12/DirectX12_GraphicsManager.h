#pragma once
#ifndef DX12_H
#define DX12_H

#include <d3d12.h>
#include <wrl/client.h>

#include <DirectX12/DirectX12_ViewPort.h>
#include <DirectX12/DirectX12_SwapChain.h>
#include <DirectX12/DirectX12_PipeLineStateObject.h>

namespace DirectX12 
{
	using Microsoft::WRL::ComPtr;

	class DirectX12_GraphicsMng
	{
	public:

		static DirectX12_GraphicsMng* GetInstance()
		{
			static DirectX12_GraphicsMng instance;

			return &instance;
		}
		
		bool Init(HWND _hWnd, Vector2Int _size);

		void Uninit();

		void ResetCommand();
		void SetViewPort();
		void SetPipelineState();
		void ClearRenderTargetView(float _clearColor[]);

		void WaitDrawFinised();

		void WaitForCommandQueue();

		ID3D12Device* GetDevice(){ return m_device.Get(); }
		ID3D12GraphicsCommandList* GetCommandList(){ return m_commandList.Get(); }
		
	private:

		DirectX12_GraphicsMng(){}

		DirectX12_GraphicsMng(const DirectX12_GraphicsMng&) = delete;
		DirectX12_GraphicsMng& operator = (const DirectX12_GraphicsMng&) = delete;
		DirectX12_GraphicsMng(DirectX12_GraphicsMng&&) = delete;
		DirectX12_GraphicsMng& operator = (DirectX12_GraphicsMng&&) = delete;

		ComPtr<ID3D12Device>                m_device = nullptr;               // デバイス
		ComPtr<ID3D12CommandQueue>          m_commandQueue = nullptr;         // コマンドキュー
		ComPtr<ID3D12Fence>                 m_fence = nullptr;
		ComPtr<ID3D12GraphicsCommandList>   m_commandList = nullptr;          // コマンドリスト
		ComPtr<ID3D12CommandAllocator>      m_commandAllocaotr = nullptr;     // コマンドアロケータ

		DirectX12_SwapChain                 m_swapChain;
		DirectX12_ViewPort                  m_viewPort;             // ビューポート
		DirectX12_PipeLineState             m_pipelineState;
		HANDLE                              m_fenceEvent = nullptr;
	};

	void BeforeRender(float _clearColor[]);

	void AfterRender();
}

#endif // !DX12_H
