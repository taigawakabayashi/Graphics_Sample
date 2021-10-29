#pragma once
#ifndef CONTEXT_H
#define CONTEXT_H

#include <wrl/client.h>

#include "SwitchingAPI.h"

#include "GHI/GHI_Device.h"
#include "GHI/GHI_ViewPort.h"

#include "Texture.h"

enum class PrimitiveTopology
{
	UNDEFINED = 0,
	POINTLIST = 1,
	LINELIST = 2,
	LINESTRIP = 3,
	TRIANGLELIST = 4,
	TRIANGLESTRIP = 5,
	LINELIST_ADJ = 10,
	LINESTRIP_ADJ = 11,
	TRIANGLELIST_ADJ = 12,
	TRIANGLESTRIP_ADJ = 13,
};

class GHI_ShaderResourceView;

namespace GHI
{
	class GHI_CommandBuffer
	{
	public:

		virtual void Init(GHI_Device* _pDevice) = 0;

		virtual void ResetCommand() = 0;

		virtual void ClearRenderTargetView(GHI_SwapChain* _swapChain, const float _clearColor[]) = 0;
		virtual void ClearDepthStencilView(GHI_DepthStencilView* _depthStencilView, ClearFlag _clearFlags) = 0;

		virtual void SetRenderTargetView(GHI_SwapChain* _swapChain, GHI_DepthStencilView* _depthStencilView) = 0;
		virtual void SetViewPorrt(GHI_ViewPort* _viewPort) = 0;

		virtual void SetIABuffer(BufferType _bufferType, GHI_Buffer* _pBuffer) = 0;
		virtual void SetConstantBuffer(uint32_t _rootParamerterIndex, GHI::GHI_Buffer* _pBuffer) = 0;

		virtual void SetPrimitiveTopology(PrimitiveTopology _topology) = 0;
		virtual void SetStates(GHI_PipelineState* _pPipelineState,
							   BlendType _blendType,
							   RasterizerType _rasterizerType,
							   DepthStencilType _depthStencilType,
							   SamplerType _samplerType) = 0;

		// Draw Call
		virtual void DrawInstanced(uint32_t _numVertexPerInstance,
								   uint32_t _numInstance,
								   uint32_t _startVertexLocation,
								   uint32_t _startInstanceLocation) = 0;

		virtual void DrawIndexedInstanced(uint32_t _numIndexPerInstance,
										  uint32_t _numInstance,
										  uint32_t _startIndexLocation,
										  uint32_t _baseVertexLocation,
										  uint32_t _startInstanceLocation) = 0;

		virtual void FinishCommand(GHI_SwapChain* _swapChain) = 0;

		virtual void* Get() = 0;

		virtual ~GHI_CommandBuffer() {}

	private:
		
	};

	class GHI_CommandQueue 
	{
	public:

		virtual void CreateFence(GHI_Device* _pDevice) = 0;
		virtual void CreateCommandBuffer(GHI_Device* _pDevice) = 0;
		GHI_CommandBuffer* GetCommandBuffer(uint32_t _index) { return m_commandBuffers[_index].get(); }

		virtual void ExecuteCommandBuffers() = 0;

		virtual void* Get() = 0;
		virtual void* GetPP() = 0;

		virtual void Swap(GHI_SwapChain* _swapChain) = 0;

		virtual ~GHI_CommandQueue() {}

	protected:

		std::vector<std::unique_ptr<GHI_CommandBuffer>> m_commandBuffers;
	};
}
#endif // !CONTEXT_H
