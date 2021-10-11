#pragma once
#ifndef PSO_H
#define PSO_H

#include <d3d12.h>
#include <wrl/client.h>

#include "Shader.h"

namespace DirectX12 
{
    using Microsoft::WRL::ComPtr;
    
    class DirectX12_PipeLineState 
    {
    public:

        bool Init(ID3D12Device* _pDevice);

        void SetRootSignature(ID3D12GraphicsCommandList* _pCommandList);

    private:
    
        ComPtr<ID3D12DescriptorHeap>        m_constantHeap;
        ComPtr<ID3D12Resource>              m_constantBuffer;
        ComPtr<ID3D12RootSignature>         m_rootSignature;
        ComPtr<ID3D12PipelineState>         m_pipeLineState;
        ComPtr<ID3D12Resource>              m_vertexBufferPosition;
        D3D12_VERTEX_BUFFER_VIEW            m_vertexBufferView;

    };
}
#endif // !PSO_H
