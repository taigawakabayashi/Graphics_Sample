#pragma once
#ifndef GHI_TEXTURE_H
#define GHI_TEXTURE_H

#include "Utility/Math.h"

struct TextureInfo 
{
	uint32_t* colorData;
	Vector2Int size;
};

namespace GHI 
{
	class GHI_Texture 
	{
	public:

		void SetTextureInfo(TextureInfo* _pInfo) { m_textureInfo = *_pInfo; }
		TextureInfo* GetTextureInfo() { return &m_textureInfo; }

		virtual void* Get() = 0;

		virtual ~GHI_Texture() {}

	protected:

		TextureInfo m_textureInfo;
	};
}

#endif // !GHI_TEXTURE_H
