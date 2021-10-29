#pragma once
#ifndef DX12_CONTEXT_H
#define DX12_CONTEXT_H

#include "GHI/GHI_Context.h"

namespace DirectX12 
{
	class DX12_CommandBuffer : public GHI::GHI_CommandBuffer 
	{
	public:

		void Init(GHI::GHI_Device* _pDevice) override;

		void ResetCommand() override;

		void ClearRenderTargetView(GHI::GHI_SwapChain* _swapChain, const float _clearColor[]) override;
		void ClearDepthStencilView(GHI::GHI_DepthStencilView* _depthStencilView, ClearFlag _clearFlags) override {};

		void SetRenderTargetView(GHI::GHI_SwapChain* _swapChain, GHI::GHI_DepthStencilView* _depthStencilView) override;
		void SetViewPorrt(GHI::GHI_ViewPort* _viewPort) override;

		void SetIABuffer(BufferType _bufferType, GHI::GHI_Buffer* _pBuffer) override;
		void SetConstantBuffer(uint32_t _rootParamerterIndex, GHI::GHI_Buffer* _pBuffer) override;

		void SetPrimitiveTopology(PrimitiveTopology _topology) override;
		void SetStates(GHI::GHI_PipelineState* _pPipelineState,
					   BlendType _blendType,
					   RasterizerType _rasterizerType,
					   DepthStencilType _depthStencilType,
					   SamplerType _samplerType) override;

		// Draw Call
		void DrawInstanced(uint32_t _numVertexPerInstance,
						   uint32_t _numInstance,
						   uint32_t _startVertexLocation,
						   uint32_t _startInstanceLocation) override;

		void DrawIndexedInstanced(uint32_t _numIndexPerInstance,
								  uint32_t _numInstance,
								  uint32_t _startIndexLocation,
								  uint32_t _baseVertexLocation,
								  uint32_t _startInstanceLocation) override;

		void FinishCommand(GHI::GHI_SwapChain* _swapChain) override;

		void* Get() override { return m_commandList; }

	private:

		ID3D12CommandAllocator*		m_commandAllocator = nullptr;
		ID3D12GraphicsCommandList*	m_commandList = nullptr;
	};

	class DX12_CommandQueue : public GHI::GHI_CommandQueue 
	{
	public:

		void CreateFence(GHI::GHI_Device* _pDevice) override;
		void CreateCommandBuffer(GHI::GHI_Device* _pDevice) override;

		void ExecuteCommandBuffers();

		void* Get() override { return m_commandQueue; }
		void* GetPP() override { return &m_commandQueue; }

		void Swap(GHI::GHI_SwapChain* _swapChain) override;

	private:

		HANDLE				m_fenceEvent;
		ID3D12Fence*		m_fence = nullptr;
		ID3D12CommandQueue* m_commandQueue = nullptr;
	};
}

#endif // !DX12_CONTEXT_H
