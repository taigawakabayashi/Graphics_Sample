#pragma once
#ifndef DX12_H
#define DX12_H

#include <d3d12.h>
#include <wrl/client.h>

#include <DirectX12/DirectX12_ViewPort.h>

namespace DirectX12 
{
    using Microsoft::WRL::ComPtr;

    class DirectX12_GraphicsMng 
    {
    public:

        bool Init(HWND _hWnd, Vector2Int _size);

        void ResetCommand();
        
    private:

        ComPtr<ID3D12Device>                m_device;               // デバイス
        ComPtr<ID3D12CommandQueue>          m_commandQueue;         // コマンドキュー
        ComPtr<ID3D12CommandAllocator>      m_commandAllocaotr;     // コマンドアロケータ
        ComPtr<ID3D12GraphicsCommandList>   m_commandList;          // コマンドリスト
        ComPtr<ID3D12PipelineState>         m_pipeLineState;        // 

        DirectX12_ViewPort                  m_viewPort;             // 
    };

    void BeforRender(float _clearColor[]);

    void AfterEnder();
}

#endif // !DX12_H
