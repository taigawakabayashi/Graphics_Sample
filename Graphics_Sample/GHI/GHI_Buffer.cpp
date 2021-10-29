#include "GHI/GHI_Buffer.h"
#include "GHI/GHI_Device.h"

namespace GHI
{
	void GHI_Buffer::SetBufferInfo(BufferInfo* _pInfo)
	{
		m_info = *_pInfo;
	}

	BufferInfo* GHI_Buffer::GetBufferInfo()
	{
		return &m_info;
	}
	void GHI_Buffer::UpdateData(void* _pData)
	{
		m_isUpdate = true;

		m_data = _pData;
	}

	void* GHI_Buffer::GetData() 
	{
		m_isUpdate = false;

		return m_data;
	}
} 
