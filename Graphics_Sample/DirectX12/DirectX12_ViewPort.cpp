#include <DirectX12/DirectX12_ViewPort.h>

namespace DirectX12
{
	void DirectX12_ViewPort::CreateViewPort(Vector2 _size, Vector2 _top)
	{
		m_viewPort.Width = _size.x;
		m_viewPort.Height = _size.y;
		m_viewPort.TopLeftX = _top.x;
		m_viewPort.TopLeftY = _top.y;
		m_viewPort.MinDepth = 0.0f;
		m_viewPort.MaxDepth = 1.0f;

		m_scissorRect.top = static_cast<LONG>(_top.y);
		m_scissorRect.left = static_cast<LONG>(_top.y);
		m_scissorRect.bottom = static_cast<LONG>(_size.y);
		m_scissorRect.right = static_cast<LONG>(_size.x);
	}

	void DirectX12_ViewPort::SetViewPort(ID3D12GraphicsCommandList* _pCommandList)
	{
		_pCommandList->RSSetViewports(1, &m_viewPort);

		_pCommandList->RSSetScissorRects(1, &m_scissorRect);
	}


	void DX12_ViewPort::CreateViewPort(Vector2 _size, Vector2 _topLeft) 
	{
		m_viewPort.Width = _size.x;
		m_viewPort.Height = _size.y;
		m_viewPort.TopLeftX = _topLeft.x;
		m_viewPort.TopLeftY = _topLeft.y;
		m_viewPort.MinDepth = 0.0f;
		m_viewPort.MaxDepth = 1.0f;
	}
}
