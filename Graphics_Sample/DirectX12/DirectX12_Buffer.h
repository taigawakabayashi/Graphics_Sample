#pragma once
#ifndef DX12_BUFFER_H
#define DX12_BUFFER_H

#include "GHI/GHI_Buffer.h"

namespace DirectX12 
{
	class DX12_Buffer : public GHI::GHI_Buffer
	{
	public:

		void* Get() override { return m_buffer; }

	private:

		ID3D12Resource* m_buffer;
	};
}

#endif // !DX12_BUFFER_H
