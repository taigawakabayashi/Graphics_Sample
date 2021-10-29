#pragma once
#ifndef DX11_VP_H
#define DX11_VP_H

#include	<d3d11.h>
#include	<wrl/client.h>
#include    <GHI/GHI_ViewPort.h>

namespace DirectX11 
{
    class DirectX11_ViewPort 
    {
    public:

        void CreateViewPort(Vector2 _size, Vector2 _top);

        D3D11_VIEWPORT* GetViewPort(){ return &m_viewPort; };

        void SetViewPort(ID3D11DeviceContext* _pDeviceContext);

    private:

        D3D11_VIEWPORT m_viewPort = { 0 };
    };


    class DX11_ViewPort : public GHI::GHI_ViewPort
    {
    public:

        void CreateViewPort(Vector2 _size, Vector2 _topLeft) override;

        void* Get() override { return &m_viewPort; }

    private:

        D3D11_VIEWPORT m_viewPort = { 0 };
    };
}
#endif // !DX11_VP_H
