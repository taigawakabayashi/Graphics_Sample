#pragma once
#ifndef VP_H
#define VP_H

#include	<d3d11.h>
#include	<wrl/client.h>
#include    "Math.h"

namespace DirectX11 
{
    class ViewPort 
    {
    public:

        void CreateViewPort(Vector2 size, Vector2 top);

        D3D11_VIEWPORT* GetViewPort();

        void SetViewPort(ID3D11DeviceContext* devcontext);

    private:

        D3D11_VIEWPORT m_viewPort = { 0 };
    };

}
#endif // !VP_H