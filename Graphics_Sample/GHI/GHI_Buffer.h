#pragma once
#ifndef GHI_BUFFER_H
#define GHI_BUFFER_H

#include <wrl/client.h>
#include "SwitchingAPI.h"
#include "Texture.h"
#include "Utility/Math.h"

enum class BufferType
{
	VERTEX,
	INDEX,
	CONSTANT,
	STRUCTURED
};

struct BufferInfo 
{
	uint32_t	m_bufferSize = 0;
	uint32_t	m_stride = 0;
	Format		m_format = Format::UNKNOWN;
};

namespace GHI 
{
	class GHI_Buffer 
	{
	public:

		void SetBufferInfo(BufferInfo* _pInfo);
		BufferInfo* GetBufferInfo();

		void UpdateData(void* _pData);
		void* GetData();
		virtual void* Get() = 0;

		virtual ~GHI_Buffer() {}

	private:

		void* m_data = nullptr;
		bool m_isUpdate = false;

		BufferInfo m_info{};
	};
}

#endif // !GHI_BUFFER_H
