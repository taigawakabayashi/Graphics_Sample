#pragma once
#ifndef DX12_VIEWPORT_H
#define DX12_VIEWPORT_H

#include <d3d12.h>

#include <GHI/GHI_ViewPort.h>

namespace DirectX12 
{
    class DirectX12_ViewPort 
    {
    public:

        void CreateViewPort(Vector2 _size, Vector2 _top);

        D3D12_VIEWPORT* GetViewPort(){ return &m_viewPort; };

        void SetViewPort(ID3D12GraphicsCommandList* _pCommandList);

    private:

        D3D12_VIEWPORT m_viewPort = { 0 };

        D3D12_RECT     m_scissorRect = { 0 };
    };

    class DX12_ViewPort : public GHI::GHI_ViewPort
    {
    public:

        void CreateViewPort(Vector2 _size, Vector2 _topLeft) override;

        void* Get() override { return &m_viewPort; }

    private:

        D3D12_VIEWPORT m_viewPort = { 0 };
    };
}

#endif // !DX12_VIEWPORT_H

