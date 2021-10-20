#include "GHI/GHI_Buffer.h"
#include "GHI/GHI_Device.h"

#ifdef IS_DIRECTX11

HRESULT Buffer::Map(Context* _pContext,void* _pData)
{
	HRESULT hr = _pContext->Get()->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0,reinterpret_cast<D3D11_MAPPED_SUBRESOURCE*>(_pData));

	return hr;
}

void Buffer::Unmap(Context* _pContext)
{
	_pContext->Get()->Unmap(m_buffer.Get(), 0);
}

#elif defined IS_DIRECTX12



#endif 

