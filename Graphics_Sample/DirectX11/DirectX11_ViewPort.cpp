#include "DirectX11/DirectX11_ViewPort.h"

namespace DirectX11 
{
    void DirectX11_ViewPort::CreateViewPort(Vector2 _size, Vector2 _top)
    {
        m_viewPort.Width = _size.x;
        m_viewPort.Height = _size.y;
        m_viewPort.TopLeftX = _top.x;
        m_viewPort.TopLeftY = _top.y;
        m_viewPort.MinDepth = 0.0f;
        m_viewPort.MaxDepth = 1.0f;
    }

    void DirectX11_ViewPort::SetViewPort(ID3D11DeviceContext* _pDeviceContext)
    {
        _pDeviceContext->RSSetViewports(1, &m_viewPort);
    }


    
    void DX11_ViewPort::CreateViewPort(Vector2 _size, Vector2 _topLeft)
    {
        m_viewPort.Width = _size.x;
        m_viewPort.Height = _size.y;
        m_viewPort.TopLeftX = _topLeft.x;
        m_viewPort.TopLeftY = _topLeft.y;
        m_viewPort.MinDepth = 0.0f;
        m_viewPort.MaxDepth = 1.0f;
    }

}
