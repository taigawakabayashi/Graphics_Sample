#pragma once
#ifndef GHI_VIEWPORT_H
#define GHI_VIEWPORT_H

#include "Utility//Math.h"

namespace GHI
{
	class GHI_ViewPort
	{
	public:

		virtual void CreateViewPort(Vector2 _size, Vector2 _topLeft) = 0;

		virtual void* Get() = 0;

		virtual ~GHI_ViewPort() {}
	};
}

#endif // !GHI_VIEWPORT_H
