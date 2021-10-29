#pragma once
#ifndef DX11_BUFFER_H
#define DX11_BUFFER_H

#include "GHI/GHI_Buffer.h"

namespace DirectX11 
{
	class DX11_Buffer : public GHI::GHI_Buffer
	{
	public:

		void* Get() override { return m_buffer; }

	private:

		ID3D11Buffer* m_buffer;
	};
}

#endif // !DX11_BUFFER_H
