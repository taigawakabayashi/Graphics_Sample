#pragma once
#ifndef VIEW_H
#define VIEW_H

#include <d3d12.h>

#include <Utility/Math.h>

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
    };
}

#endif // !VIEW_H

