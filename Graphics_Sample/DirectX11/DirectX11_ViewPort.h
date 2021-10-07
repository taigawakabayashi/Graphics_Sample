#pragma once
#ifndef VP_H
#define VP_H

#include	<d3d11.h>
#include	<wrl/client.h>
#include    <Utility/Math.h>

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

}
#endif // !VP_H
