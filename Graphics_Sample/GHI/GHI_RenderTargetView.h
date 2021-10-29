#pragma once
#ifndef GHI_RTV_H
#define GHI_RTV_H

#include <cinttypes>

namespace GHI 
{
	class GHI_Device;
	class GHI_SwapChain;

	class GHI_RenderTargetView 
	{
	public:

		virtual void Create(GHI_Device* _pDevice, GHI_SwapChain* _pSwapChain) = 0;

		virtual void* Get(uint32_t _index) = 0;
		virtual void* GetPP(uint32_t _index) = 0;

		virtual SIZE_T GetDescriptorHandle(uint32_t _index) = 0;

		virtual ~GHI_RenderTargetView() {}

	private:
	};
}

#endif // GHI_RTV_H

