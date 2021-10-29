#pragma once
#ifndef GHI_DSV_H
#define GHI_DSV_H

enum class ClearFlag 
{
	DEPTH = 0x1,
	STENCIL = 0x2,
};

namespace GHI 
{
	class GHI_DepthStencilView 
	{
	public:

		virtual void* Get() = 0;

		virtual ~GHI_DepthStencilView() {}

	private:
	};
}

#endif // !GHI_DSV_H
