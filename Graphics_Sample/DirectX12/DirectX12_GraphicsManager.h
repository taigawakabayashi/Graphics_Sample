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

        ComPtr<ID3D12Device>                m_device;               // �f�o�C�X
        ComPtr<ID3D12CommandQueue>          m_commandQueue;         // �R�}���h�L���[
        ComPtr<ID3D12CommandAllocator>      m_commandAllocaotr;     // �R�}���h�A���P�[�^
        ComPtr<ID3D12GraphicsCommandList>   m_commandList;          // �R�}���h���X�g
        ComPtr<ID3D12PipelineState>         m_pipeLineState;        // 

        DirectX12_ViewPort                  m_viewPort;             // 
    };

    void BeforRender(float _clearColor[]);

    void AfterEnder();
}

#endif // !DX12_H