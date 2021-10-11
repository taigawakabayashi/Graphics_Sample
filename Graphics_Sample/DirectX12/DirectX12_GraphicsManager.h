#pragma once
#ifndef DX12_H
#define DX12_H

#include <d3d12.h>
#include <wrl/client.h>

#include <DirectX12/DirectX12_ViewPort.h>
#include <DirectX12/DirectX12_SwapChain.h>

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

        void ResetCommand();

        void SetViewPort();

        void ClearRenderTargetView(float _clearColor[]);

        void WaitDrawFinised();

        void WaitForCommandQueue();
        
    private:

        DirectX12_GraphicsMng(){}

        DirectX12_GraphicsMng(const DirectX12_GraphicsMng&) = delete;
        DirectX12_GraphicsMng& operator = (const DirectX12_GraphicsMng&) = delete;
        DirectX12_GraphicsMng(DirectX12_GraphicsMng&&) = delete;
        DirectX12_GraphicsMng& operator = (DirectX12_GraphicsMng&&) = delete;

        ComPtr<ID3D12Device>                m_device = nullptr;               // デバイス
        ComPtr<ID3D12CommandQueue>          m_commandQueue = nullptr;         // コマンドキュー
        ComPtr<ID3D12CommandAllocator>      m_commandAllocaotr = nullptr;     // コマンドアロケータ
        ComPtr<ID3D12GraphicsCommandList>   m_commandList = nullptr;          // コマンドリスト
        ComPtr<ID3D12PipelineState>         m_pipeLineState = nullptr;        // 

        ComPtr<ID3D12Fence>                 m_fence = nullptr;
        HANDLE                              m_fenceEvent = nullptr;

        DirectX12_ViewPort                  m_viewPort;             // ビューポート
        DirectX12_SwapChain                 m_swapChain;
    };

    void BeforeRender(float _clearColor[]);

    void AfterRender();
}

#endif // !DX12_H
