#pragma once
#ifndef CONTEXT_H
#define CONTEXT_H

#include <wrl/client.h>

#include "SwitchingAPI.h"
#include "GHI/GHI_Buffer.h"
#include "GHI/GHI_CommonState.h"

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

class Device;

class RenderTargetView;
class DepthStencilView;
class ShaderResourceView;
class ViewPort;

enum class ClearFlags;

// Context Class
#ifdef IS_DIRECTX11

class Context
{
public:

	virtual void ClearRenderTargetView(RenderTargetView* _renderTargetView, const float _clearColor[]) = 0;
	virtual void ClearDepthStencilView(DepthStencilView* _depthStencilView, ClearFlags _clearFlags) = 0;

	virtual void SetRenderTargetView(RenderTargetView* _renderTargetView, DepthStencilView* _depthStencilView) = 0;
	virtual void SetViewPorrt(ViewPort* _viewPort) = 0;
	virtual void SetConstantBuffer(uint32_t _setSlot, Buffer* _pConstantBuffer) = 0;
	virtual void SetVertextBuffer(uint32_t _numBuffer, Buffer* _pVertexBuffers, uint32_t* _strides) = 0;
	virtual void SetIndexBuffer(Buffer* _pIndexBuffer) = 0;
	virtual void SetPrimitiveTopology(PrimitiveTopology _topology) = 0;
	virtual void SetShaderResourceView(ShaderResourceView* _shaderResourceView)= 0;
	virtual void SetStates(BlendType _blendType, 
						   RasterType _rasterizerType,
						   DepthStencilType _depthStencilType,
						   SamplerType _samplerType) = 0;
	virtual void SetPipelineStateObject(PipelineStateObject* _pipelineStateObject) = 0;

	// Draw Call
	virtual void Draw(uint32_t _numVertex, uint32_t _startVertexLocation) = 0;
	virtual void DrawIndexed(uint32_t _numIndex, 
							 uint32_t _startIndexLocation, 
							 uint32_t _baseVertexLocation) = 0;

	virtual void DrawInstanced(uint32_t _numVertexPerInstance, 
							   uint32_t _numInstance, 
							   uint32_t _startVertexLocation, 
							   uint32_t _startInstanceLocation) = 0;

	virtual void DrawIndexedInstanced(uint32_t _numIndexPerInstance,
									  uint32_t _numInstance,
									  uint32_t _startIndexLocation,
									  uint32_t _baseVertexLocation,
									  uint32_t _startInstanceLocation) = 0;

	virtual void Swap() = 0;

	ID3D11DeviceContext* Get() { return m_context.Get(); }
	ID3D11DeviceContext** GetAddressOf() { return m_context.GetAddressOf(); }

protected:

	virtual void SetState(CommonState* _pCommonState, StateType _statType) = 0;

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context = nullptr;
	PipelineStateObject*						m_pipelineStateObject = nullptr;
};

class ImmediateContext : public Context
{
public:
	
	void ClearRenderTargetView(RenderTargetView* _renderTargetView, const float _clearColor[]) override;
	void ClearDepthStencilView(DepthStencilView* _depthStencilView, ClearFlags _clearFlags) override;

	void SetRenderTargetView(RenderTargetView* _renderTargetView, DepthStencilView* _depthStencilView) override;
	void SetViewPorrt(ViewPort* _viewPort) override;
	void SetConstantBuffer(uint32_t _setSlot, Buffer* _pConstantBuffer) override;
	void SetVertextBuffer(uint32_t _numBuffer, Buffer* _pVertexBuffers, uint32_t* _strides) override;
	void SetIndexBuffer(Buffer* _pIndexBuffer) override;
	void SetPrimitiveTopology(PrimitiveTopology _topology) override;
	void SetShaderResourceView(ShaderResourceView* _shaderResourceView) override;
	void SetStates(BlendType _blendType,
				   RasterType _rasterizerType,
				   DepthStencilType _depthStencilType,
				   SamplerType _samplerType) override;
	void SetPipelineStateObject(PipelineStateObject* _pipelineStateObject) override;

	// Draw Call
	void Draw(uint32_t _numVertex, uint32_t _startVertexLocation) override;
	void DrawIndexed(uint32_t _numIndex,
					 uint32_t _startIndexLocation,
					 uint32_t _baseVertexLocation) override;

	void DrawInstanced(uint32_t _numVertexPerInstance,
					   uint32_t _numInstance,
					   uint32_t _startVertexLocation,
					   uint32_t _startInstanceLocation) override;

	void DrawIndexedInstanced(uint32_t _numIndexPerInstance,
							  uint32_t _numInstance,
							  uint32_t _startIndexLocation,
							  uint32_t _baseVertexLocation,
							  uint32_t _startInstanceLocation) override;

	void Swap() override;

private:

	void SetState(CommonState* _pCommonState, StateType _statType) override;

};

class DeferredContext : public Context
{
public:

	void Create(Device* _pDevice);

private:
};

#elif defined IS_DIRECTX12

class Context
{
public:

	virtual void Init(Device* _pDevice) = 0;

	virtual void ClearRenderTargetView(RenderTargetView* _renderTargetView, const float _clearColor[]) = 0;
	virtual void ClearDepthStencilView(DepthStencilView* _depthStencilView, ClearFlags _clearFlags) = 0;

	virtual void SetRenderTargetView(RenderTargetView* _renderTargetView, DepthStencilView* _depthStencilView) = 0;
	virtual void SetViewPorrt(ViewPort* _viewPort) = 0;
	virtual void SetConstantBuffer(uint32_t _rootParameterIndex, Buffer* _pConstantBuffer) = 0;
	virtual void SetVertextBuffer(uint32_t _numBuffer, Buffer* _pVertexBuffers, uint32_t* _strides, uint32_t* _sizes) = 0;
	virtual void SetIndexBuffer(Buffer* _pIndexBuffer) = 0;
	virtual void SetPrimitiveTopology(PrimitiveTopology _topology) = 0;
	virtual void SetShaderResourceView(ShaderResourceView* _shaderResourceView) = 0;
	virtual void SetStates(BlendType _blendType,
						   RasterType _rasterizerType,
						   DepthStencilType _depthStencilType,
						   SamplerType _samplerType) = 0;
	virtual void SetPipelineStateObject(PipelineStateObject* _pipelineStateObject) = 0;

	//Draw Call
	virtual void DrawInstanced(uint32_t _numVertexPerInstance,
							   uint32_t _numInstance,
							   uint32_t _startVertexLocation,
							   uint32_t _startInstanceLocation) = 0;

	virtual void DrawIndexedInstanced(uint32_t _numIndexPerInstance,
									  uint32_t _numInstance,
									  uint32_t _startIndexLocation,
									  uint32_t _baseVertexLocation,
									  uint32_t _startInstanceLocation) = 0;
	virtual void Swap() = 0;

	ID3D12GraphicsCommandList* Get(){ return m_context.Get(); }
	ID3D12GraphicsCommandList** GetAddressOf(){ return m_context.GetAddressOf(); }
	ID3D12CommandAllocator** GetAllocator() { return m_commandAllocator.GetAddressOf(); }

protected:

	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_context;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	PipelineStateObject* m_pipelineStateObject = nullptr;
};

class ImmediateContext : public Context
{
public:

	void Init(Device* _pDevice) override;

	void ClearRenderTargetView(RenderTargetView* _renderTargetView, const float _clearColor[]) override;
	void ClearDepthStencilView(DepthStencilView* _depthStencilView, ClearFlags _clearFlags) override;

	void SetRenderTargetView(RenderTargetView* _renderTargetView, DepthStencilView* _depthStencilView) override;
	void SetViewPorrt(ViewPort* _viewPort) override;
	void SetConstantBuffer(uint32_t _setSlot, Buffer* _pConstantBuffer) override;
	void SetVertextBuffer(uint32_t _numBuffer, Buffer* _pVertexBuffers, uint32_t* _strides, uint32_t* _sizes) override;
	void SetIndexBuffer(Buffer* _pIndexBuffer) override;
	void SetPrimitiveTopology(PrimitiveTopology _topology) override;
	void SetShaderResourceView(ShaderResourceView* _shaderResourceView) override;
	void SetStates(BlendType _blendType,
				   RasterType _rasterizerType,
				   DepthStencilType _depthStencilType,
				   SamplerType _samplerType) override;
	void SetPipelineStateObject(PipelineStateObject* _pipelineStateObject) override;

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

	void Swap() override;

private:

	Microsoft::WRL::ComPtr<ID3D12CommandQueue>	m_commandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Fence>			m_fence = nullptr;
	HANDLE										m_fenceEvent = nullptr;
};

class DeferredContext : public Context
{
public:

	void Create(Device* _pDevice);

private:
};

#endif

#endif // !CONTEXT_H
