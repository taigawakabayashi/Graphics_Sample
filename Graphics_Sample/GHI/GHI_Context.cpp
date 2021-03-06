#include "GHI/GHI_Context.h"


#ifdef IS_DIRECTX11

void ImmediateContext::ClearRenderTargetView(RenderTargetView* _renderTargetView, const float _clearColor[])
{
	m_context->ClearRenderTargetView(nullptr, _clearColor);
}

void ImmediateContext::ClearDepthStencilView(DepthStencilView* _depthStencilView, ClearFlags _clearFlags)
{
	m_context->ClearDepthStencilView(nullptr, static_cast<uint32_t>(_clearFlags), 1.0f, 0);
}

void ImmediateContext::SetRenderTargetView(RenderTargetView* _renderTargetView, DepthStencilView* _depthStencilView)
{
	m_context->OMSetRenderTargets(1, nullptr, nullptr);
}

void ImmediateContext::SetViewPorrt(ViewPort* _viewPort)
{
	m_context->RSSetViewports(1, nullptr);
}

void ImmediateContext::SetResourceBuffer(ResourceBuffer* _pBuffer, BufferType _bufferType, uint32_t _setSlot)
{
	if (_pBuffer->isUpdate()) {

		D3D11_MAPPED_SUBRESOURCE pData{};

		HRESULT hr = m_context->Map(_pBuffer->Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);

		if (SUCCEEDED(hr))
		{
			pData.pData = _pBuffer->GetData();

			m_context->Unmap(_pBuffer->Get(), 0);
		}
	}

	switch (_bufferType)
	{
	case BufferType::CONSTANT:

		m_context->VSSetConstantBuffers(_setSlot, 1, _pBuffer->GetAddressOf());

		break;
	}
}

void ImmediateContext::SetIABuffer(IABuffer* _pBuffer, IABufferType _bufferType)
{
	switch (_bufferType)
	{
	case IABufferType::VERTEX:
	{

		uint32_t offsets[] = { 0 };

		uint32_t stride = _pBuffer->GetBufferStride();

		m_context->IASetVertexBuffers(0, 1, _pBuffer->GetAddressOf(), &stride, offsets);

		break;
	}
	case IABufferType::INDEX:

		m_context->IASetIndexBuffer(_pBuffer->Get(), static_cast<DXGI_FORMAT>(_pBuffer->GetBufferFormat()), 0);

		break;
	}
}

void ImmediateContext::SetPrimitiveTopology(PrimitiveTopology _topology)
{
	m_context->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(_topology));
}

void ImmediateContext::SetShaderResourceView(ShaderResourceView* _shaderResourceView)
{

}

void ImmediateContext::SetStates(BlendType _blendType, 
								 RasterType _rasterizerType, 
								 DepthStencilType _depthStencilType, 
								 SamplerType _samplerType)
{
	SetState(m_pipelineStateObject->GetBlendState(_blendType), StateType::BLEND);
	SetState(m_pipelineStateObject->GetRastrizerState(_rasterizerType), StateType::RASTRIZER);
	SetState(m_pipelineStateObject->GetDepthStencilState(_depthStencilType), StateType::DEPTHSTENCIL);
	SetState(m_pipelineStateObject->GetSamplerState(_samplerType), StateType::SAMPLER);
}

void ImmediateContext::SetPipelineStateObject(PipelineState* _pipelineStateObject)
{
	m_pipelineStateObject = _pipelineStateObject;
}

void ImmediateContext::SetState(CommonState* _pCommonState, StateType _stateType)
{
	switch (_stateType)
	{
	case StateType::RASTRIZER:
	{
		m_context->RSSetState(reinterpret_cast<ID3D11RasterizerState*>(_pCommonState->Get()));

		break;
	}
	case StateType::DEPTHSTENCIL:
	{
		m_context->OMSetDepthStencilState(reinterpret_cast<ID3D11DepthStencilState*>(_pCommonState->Get()), 0);

		break;
	}
	case StateType::BLEND:
	{
		float blendFactor[4];

		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;

		m_context->OMSetBlendState(reinterpret_cast<ID3D11BlendState*>(_pCommonState->Get()), blendFactor, 0xffffffff);

		break;
	}
	case StateType::SAMPLER:
	{
		ID3D11SamplerState* samplerState = reinterpret_cast<ID3D11SamplerState*>(_pCommonState->Get());

		m_context->PSSetSamplers(0, 1, &samplerState);

		break;
	}
	}
}

void ImmediateContext::Draw(uint32_t _numVertex, uint32_t _startVertexLocation)
{
	m_context->Draw(_numVertex, _startVertexLocation);
}

void ImmediateContext::DrawIndexed(uint32_t _numIndex, uint32_t _startIndexLocation, uint32_t _baseVertexLocation)
{
	m_context->DrawIndexed(_numIndex, _startIndexLocation, _baseVertexLocation);
}

void ImmediateContext::DrawInstanced(uint32_t _numVertexPerInstance, 
									 uint32_t _numInstance, 
									 uint32_t _startVertexLocation, 
									 uint32_t _startInstanceLocation)
{
	m_context->DrawInstanced(_numVertexPerInstance, _numInstance, _startVertexLocation, _startInstanceLocation);
}

void ImmediateContext::DrawIndexedInstanced(uint32_t _numIndexPerInstance, 
											uint32_t _numInstance, 
											uint32_t _startIndexLocation, 
											uint32_t _baseVertexLocation, 
											uint32_t _startInstanceLocation)
{
	m_context->DrawIndexedInstanced(_numIndexPerInstance, _numInstance, _startIndexLocation, _baseVertexLocation, _startInstanceLocation);
}

void ImmediateContext::Swap()
{

}

#elif defined IS_DIRECTX12

void ImmediateContext::Init(Device* _pDevice)
{


}

void ImmediateContext::ClearRenderTargetView(RenderTargetView* _renderTargetView, const float _clearColor[])
{
	//m_context->ClearRenderTargetView(, _clearColor, 0, nullptr);
}

void ImmediateContext::ClearDepthStencilView(DepthStencilView* _depthStencilView, ClearFlags _clearFlags)
{
	//m_context->ClearDepthStencilView(nullptr, static_cast<D3D12_CLEAR_FLAGS>(_clearFlags), 1.0f, 1, 0, nullptr);
}

void ImmediateContext::SetRenderTargetView(RenderTargetView* _renderTargetView, DepthStencilView* _depthStencilView)
{
	m_context->OMSetRenderTargets(1, nullptr, true, nullptr);
}

void ImmediateContext::SetViewPorrt(ViewPort* _viewPort)
{
	m_context->RSSetViewports(1, nullptr);
}

void ImmediateContext::SetResourceBuffer(ResourceBuffer* _pBuffer, BufferType _bufferType, uint32_t _setSlot)
{
	switch (_bufferType)
	{
	case BufferType::CONSTANT:

		m_context->SetGraphicsRootConstantBufferView(_setSlot, _pBuffer->Get()->GetGPUVirtualAddress());

		break;
	}
}

void ImmediateContext::SetIABuffer(IABuffer* _pBuffer, IABufferType _bufferType) 
{
	switch (_bufferType)
	{
	case IABufferType::VERTEX:
	{
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

		vertexBufferView.BufferLocation = _pBuffer->Get()->GetGPUVirtualAddress();
		vertexBufferView.SizeInBytes = _pBuffer->GetBufferSize();
		vertexBufferView.StrideInBytes = _pBuffer->GetBufferStride();

		m_context->IASetVertexBuffers(0, 1, &vertexBufferView);

		break;
	}
	case IABufferType::INDEX:
	{
		D3D12_INDEX_BUFFER_VIEW indexBufferView{};

		indexBufferView.BufferLocation = _pBuffer->Get()->GetGPUVirtualAddress();
		indexBufferView.SizeInBytes = _pBuffer->GetBufferSize();
		indexBufferView.Format = static_cast<DXGI_FORMAT>( _pBuffer->GetBufferFormat());

		m_context->IASetIndexBuffer(&indexBufferView);

		break;
	}
	}
}

void ImmediateContext::SetPrimitiveTopology(PrimitiveTopology _topology)
{
	m_context->IASetPrimitiveTopology(static_cast<D3D12_PRIMITIVE_TOPOLOGY>(_topology));
}

void ImmediateContext::SetShaderResourceView(ShaderResourceView* _shaderResourceView)
{

}

void ImmediateContext::SetStates(BlendType _blendType,
	RasterType _rasterizerType,
	DepthStencilType _depthStencilType,
	SamplerType _samplerType)
{
	m_pipelineStateObject->SetStates(_blendType, _rasterizerType, _depthStencilType, _samplerType);
}

void ImmediateContext::SetPipelineStateObject(PipelineStateObject* _pipelineStateObject)
{
	m_pipelineStateObject = _pipelineStateObject;
}

void ImmediateContext::DrawInstanced(uint32_t _numVertexPerInstance,
	uint32_t _numInstance,
	uint32_t _startVertexLocation,
	uint32_t _startInstanceLocation)
{
	m_context->DrawInstanced(_numVertexPerInstance, _numInstance, _startVertexLocation, _startInstanceLocation);
}

void ImmediateContext::DrawIndexedInstanced(uint32_t _numIndexPerInstance,
	uint32_t _numInstance,
	uint32_t _startIndexLocation,
	uint32_t _baseVertexLocation,
	uint32_t _startInstanceLocation)
{
	m_context->DrawIndexedInstanced(_numIndexPerInstance, _numInstance, _startIndexLocation, _baseVertexLocation, _startInstanceLocation);
}

void ImmediateContext::Swap()
{

}

#endif
