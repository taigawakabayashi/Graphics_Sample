#include "ViewPort.h"

namespace DirectX11 
{
    void ViewPort::CreateViewPort(Vector2 size, Vector2 top)
    {
        m_viewPort.Width = size.x;
        m_viewPort.Height = size.y;
        m_viewPort.TopLeftX = top.x;
        m_viewPort.TopLeftY = top.y;
        m_viewPort.MinDepth = 0.0f;
        m_viewPort.MaxDepth =1.0f;
    }

    D3D11_VIEWPORT* ViewPort::GetViewPort()
    {
        return &m_viewPort;
    }

    void ViewPort::SetViewPort(ID3D11DeviceContext* devcontext)
    {
        devcontext->RSSetViewports(1, &m_viewPort);
    }
}
