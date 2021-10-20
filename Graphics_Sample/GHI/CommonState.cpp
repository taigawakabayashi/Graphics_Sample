#include "GHI/GHI_CommonState.h"
#include "GHI/GHI_Device.h"
#include "Shader.h"

#ifdef IS_DIRECTX11

HRESULT BlendState::CreateState(Device* _pDevice, BlendType _blendType)
{
	D3D11_BLEND_DESC blendStateDesc{};

	switch (_blendType)
	{
	case BlendType::ALPHA_ENABLE:

		// ブレンドステート設定(アルファブレンド可)
		blendStateDesc.RenderTarget[0].BlendEnable = true;
		blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		break;

	case BlendType::ALPHA_DISABLE:

		// ブレンドステート設定(アルファブレンド不可)
		blendStateDesc.RenderTarget[0].BlendEnable = false;
		blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		break;

	default:

		return E_NOTIMPL;
	}

	HRESULT hr = _pDevice->Get()->CreateBlendState(&blendStateDesc, &m_state);

	return hr;
}

HRESULT RasterizerState::CreateState(Device* _pDevice, RasterType _rasterType)
{
	D3D11_RASTERIZER_DESC rasterDesc{};

	switch (_rasterType)
	{
	case RasterType::CULL_NONE_FILL_SOLID:

		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		break;

	case RasterType::CULL_FRONT_FILL_SOLID:

		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_FRONT;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		break;

	case RasterType::CULL_BACK_FILL_SOLID:

		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		break;

	case RasterType::CULL_NONE_FILL_WIREFRAME:

		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		break;

	case RasterType::CULL_FRONT_FILL_WIREFRAME:

		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_FRONT;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		break;

	case RasterType::CULL_BACK_FILL_WIREFRAME:

		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		break;

	default:
		return E_NOTIMPL;
	}

	HRESULT hr = _pDevice->Get()->CreateRasterizerState(&rasterDesc, &m_state);

	return hr;
}

HRESULT DepthStencilState::CreateState(Device* _pDevice, DepthStencilType _depthStencilType)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};

	switch (_depthStencilType)
	{
	case DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE:

		// ステンシルステート作成
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0x01;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// 表面の設定
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// 裏面の設定
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		break;

	case DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE:

		// ステンシルステート作成
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = false;
		depthStencilDesc.StencilReadMask = 0x01;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// 表面の設定
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// 裏面の設定
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		break;

	case DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE:

		// ステンシルステート作成
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0x01;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// 表面の設定
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// 裏面の設定
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		break;

	case DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE:

		// ステンシルステート作成
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = false;
		depthStencilDesc.StencilReadMask = 0x01;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// 表面の設定
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// 裏面の設定
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		break;
	
	default:

		return E_NOTIMPL;
	}

	HRESULT hr = _pDevice->Get()->CreateDepthStencilState(&depthStencilDesc, &m_state);

	return hr;
}

HRESULT SamplerState::CreateState(Device* _pDevice, SamplerType _samplerType) 
{
	D3D11_SAMPLER_DESC samplerDesc{};

	switch (_samplerType)
	{
	case SamplerType::CLAMP:

		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		break;

	case SamplerType::WRAP:

		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		break;

	case SamplerType::BORDER:

		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		break;

	case SamplerType::MIRROR:

		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		break;
	
	default:

		return E_NOTIMPL;
	}

	HRESULT hr = _pDevice->Get()->CreateSamplerState(&samplerDesc, &m_state);

	return hr;
}

HRESULT PipelineStateObject::InitStates(Device* _pDevice)
{
	HRESULT hr = S_OK;

	// BlendState
	{
		BlendState tempBlendState{};

		hr = tempBlendState.CreateState(_pDevice, BlendType::ALPHA_ENABLE);
		if (FAILED(hr))
			return hr;

		m_blendStates[BlendType::ALPHA_ENABLE] = tempBlendState;

		hr = tempBlendState.CreateState(_pDevice, BlendType::ALPHA_DISABLE);
		if (FAILED(hr))
			return hr;

		m_blendStates[BlendType::ALPHA_DISABLE] = tempBlendState;
	}

	// RasterizerState
	{
		RasterizerState tempRasterizeState{};

		hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_NONE_FILL_SOLID);
		if (FAILED(hr))
			return hr;

		m_rasterizerStates[RasterType::CULL_NONE_FILL_SOLID] = tempRasterizeState;

		hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_FRONT_FILL_SOLID);
		if (FAILED(hr))
			return hr;

		m_rasterizerStates[RasterType::CULL_FRONT_FILL_SOLID] = tempRasterizeState;

		hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_BACK_FILL_SOLID);
		if (FAILED(hr))
			return hr;

		m_rasterizerStates[RasterType::CULL_BACK_FILL_SOLID] = tempRasterizeState;

		hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_NONE_FILL_WIREFRAME);
		if (FAILED(hr))
			return hr;

		m_rasterizerStates[RasterType::CULL_NONE_FILL_WIREFRAME] = tempRasterizeState;

		hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_FRONT_FILL_WIREFRAME);
		if (FAILED(hr))
			return hr;

		m_rasterizerStates[RasterType::CULL_FRONT_FILL_WIREFRAME] = tempRasterizeState;

		hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_BACK_FILL_WIREFRAME);
		if (FAILED(hr))
			return hr;

		m_rasterizerStates[RasterType::CULL_BACK_FILL_WIREFRAME] = tempRasterizeState;
	}

	// DepthStencilState
	{
		DepthStencilState depthStencilState{};

		hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE);
		if (FAILED(hr))
			return hr;

		m_depthStencilStates[DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE] = depthStencilState;

		hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE);
		if (FAILED(hr))
			return hr;

		m_depthStencilStates[DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE] = depthStencilState;

		hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE);
		if (FAILED(hr))
			return hr;

		m_depthStencilStates[DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE] = depthStencilState;

		hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE);
		if (FAILED(hr))
			return hr;

		m_depthStencilStates[DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE] = depthStencilState;
	}

	// SamplerState
	{
		SamplerState samplerState{};

		hr = samplerState.CreateState(_pDevice, SamplerType::CLAMP);
		if (FAILED(hr))
			return hr;

		m_samplerStates[SamplerType::CLAMP] = samplerState;

		hr = samplerState.CreateState(_pDevice, SamplerType::WRAP);
		if (FAILED(hr))
			return hr;

		m_samplerStates[SamplerType::WRAP] = samplerState;

		hr = samplerState.CreateState(_pDevice, SamplerType::BORDER);
		if (FAILED(hr))
			return hr;

		m_samplerStates[SamplerType::BORDER] = samplerState;

		hr = samplerState.CreateState(_pDevice, SamplerType::MIRROR);
		if (FAILED(hr))
			return hr;

		m_samplerStates[SamplerType::MIRROR] = samplerState;
	}

	return hr;
}

BlendState* PipelineStateObject::GetBlendState(BlendType _blendType) 
{
	return &(m_blendStates[_blendType]);
}

RasterizerState* PipelineStateObject::GetRastrizerState(RasterType _rasterizerType) 
{
	return &(m_rasterizerStates[_rasterizerType]);
}

DepthStencilState* PipelineStateObject::GetDepthStencilState(DepthStencilType _depthStencilType) 
{
	return &(m_depthStencilStates[_depthStencilType]);
}

SamplerState* PipelineStateObject::GetSamplerState(SamplerType _samplerType) 
{
	return &(m_samplerStates[_samplerType]);
}

#elif defined IS_DIRECTX12

HRESULT PipelineStateObject::InitStates(Device* _pDevice)
{
	HRESULT hr = S_OK;

	//// BlendState
	//{
	//	BlendState tempBlendState{};

	//	hr = tempBlendState.CreateState(_pDevice, BlendType::ALPHA_ENABLE);
	//	if (FAILED(hr))
	//		return hr;

	//	m_blendStates[BlendType::ALPHA_ENABLE] = tempBlendState;

	//	hr = tempBlendState.CreateState(_pDevice, BlendType::ALPHA_DISABLE);
	//	if (FAILED(hr))
	//		return hr;

	//	m_blendStates[BlendType::ALPHA_DISABLE] = tempBlendState;
	//}

	//// RasterizerState
	//{
	//	RasterizerState tempRasterizeState{};

	//	hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_NONE_FILL_SOLID);
	//	if (FAILED(hr))
	//		return hr;

	//	m_rasterizerStates[RasterType::CULL_NONE_FILL_SOLID] = tempRasterizeState;

	//	hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_FRONT_FILL_SOLID);
	//	if (FAILED(hr))
	//		return hr;

	//	m_rasterizerStates[RasterType::CULL_FRONT_FILL_SOLID] = tempRasterizeState;

	//	hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_BACK_FILL_SOLID);
	//	if (FAILED(hr))
	//		return hr;

	//	m_rasterizerStates[RasterType::CULL_BACK_FILL_SOLID] = tempRasterizeState;

	//	hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_NONE_FILL_WIREFRAME);
	//	if (FAILED(hr))
	//		return hr;

	//	m_rasterizerStates[RasterType::CULL_NONE_FILL_WIREFRAME] = tempRasterizeState;

	//	hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_FRONT_FILL_WIREFRAME);
	//	if (FAILED(hr))
	//		return hr;

	//	m_rasterizerStates[RasterType::CULL_FRONT_FILL_WIREFRAME] = tempRasterizeState;

	//	hr = tempRasterizeState.CreateState(_pDevice, RasterType::CULL_BACK_FILL_WIREFRAME);
	//	if (FAILED(hr))
	//		return hr;

	//	m_rasterizerStates[RasterType::CULL_BACK_FILL_WIREFRAME] = tempRasterizeState;
	//}

	//// DepthStencilState
	//{
	//	DepthStencilState depthStencilState{};

	//	hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE);
	//	if (FAILED(hr))
	//		return hr;

	//	m_depthStencilStates[DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE] = depthStencilState;

	//	hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE);
	//	if (FAILED(hr))
	//		return hr;

	//	m_depthStencilStates[DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE] = depthStencilState;

	//	hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE);
	//	if (FAILED(hr))
	//		return hr;

	//	m_depthStencilStates[DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE] = depthStencilState;

	//	hr = depthStencilState.CreateState(_pDevice, DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE);
	//	if (FAILED(hr))
	//		return hr;

	//	m_depthStencilStates[DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE] = depthStencilState;
	//}

	//// SamplerState
	//{
	//	SamplerState samplerState{};

	//	hr = samplerState.CreateState(_pDevice, SamplerType::CLAMP);
	//	if (FAILED(hr))
	//		return hr;

	//	m_samplerStates[SamplerType::CLAMP] = samplerState;

	//	hr = samplerState.CreateState(_pDevice, SamplerType::WRAP);
	//	if (FAILED(hr))
	//		return hr;

	//	m_samplerStates[SamplerType::WRAP] = samplerState;

	//	hr = samplerState.CreateState(_pDevice, SamplerType::BORDER);
	//	if (FAILED(hr))
	//		return hr;

	//	m_samplerStates[SamplerType::BORDER] = samplerState;

	//	hr = samplerState.CreateState(_pDevice, SamplerType::MIRROR);
	//	if (FAILED(hr))
	//		return hr;

	//	m_samplerStates[SamplerType::MIRROR] = samplerState;
	//}

	m_device = _pDevice;

	return hr;
}

void PipelineStateObject::SetStates(BlendType _blendType, RasterType _rasterizerType, DepthStencilType _depthStencilType, SamplerType _samplerType)
{
	if (m_pipelineStateObject != nullptr) 
	{
		m_pipelineStateObject->Release();
		m_pipelineStateObject = nullptr;
	}

	// 頂点レイアウトの作成
	D3D12_INPUT_ELEMENT_DESC elementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	D3D12_RASTERIZER_DESC rasterDesc = *(reinterpret_cast<D3D12_RASTERIZER_DESC*>(m_rasterizerStates[_rasterizerType].Get()));
	D3D12_BLEND_DESC blendDesc = *(reinterpret_cast<D3D12_BLEND_DESC*>(m_blendStates[_blendType].Get()));
	D3D12_DEPTH_STENCIL_DESC depthDesc = *(reinterpret_cast<D3D12_DEPTH_STENCIL_DESC*>(m_depthStencilStates[_depthStencilType].Get()));

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeLineDesc = {};

	pipeLineDesc.InputLayout = { elementDesc, _countof(elementDesc) };
	pipeLineDesc.pRootSignature = nullptr;
	pipeLineDesc.VS = Shader::GetInstance()->GetShaderByte(Shaders::VS);	// 頂点シェーダーの設定
	pipeLineDesc.PS = Shader::GetInstance()->GetShaderByte(Shaders::PS);	// ピクセルシェーダーの設定
	pipeLineDesc.RasterizerState = rasterDesc;
	pipeLineDesc.BlendState = blendDesc;
	pipeLineDesc.DepthStencilState = depthDesc;
	pipeLineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	pipeLineDesc.SampleMask = UINT_MAX;
	pipeLineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;	// 三角形に設定(描画方法とは別)
	pipeLineDesc.NumRenderTargets = 1;
	pipeLineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pipeLineDesc.SampleDesc = { 1, 0 };

	HRESULT hr = m_device->Get()->CreateGraphicsPipelineState(&pipeLineDesc, IID_PPV_ARGS(&m_pipelineStateObject));
}

#endif