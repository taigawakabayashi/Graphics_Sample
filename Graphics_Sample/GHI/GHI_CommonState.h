#pragma once
#ifndef COMMONSTATE_H
#define COMMONSTATE_H

#include "SwitchingAPI.h"

#include <wrl/client.h>
#include <unordered_map>

enum class StateType
{
	RASTRIZER,
	DEPTHSTENCIL,
	BLEND,
	SAMPLER
};

enum class BlendType : uint32_t
{
	ALPHA_ENABLE = 0,	// アルファブレンドあり
	ALPHA_DISABLE,		// アルファブレンドなし
	MAX,
};

enum class RasterType : uint32_t
{
	CULL_NONE_FILL_SOLID = 0,	// カリングなし
	CULL_FRONT_FILL_SOLID,		// 表面カリング
	CULL_BACK_FILL_SOLID,		// 裏面カリング
	CULL_NONE_FILL_WIREFRAME,	// カリングなしワイヤーフレーム
	CULL_FRONT_FILL_WIREFRAME,	// 表面カリングワイヤーフレーム
	CULL_BACK_FILL_WIREFRAME,	// 裏面カリングワイヤーフレーム
	MAX,
};

enum class DepthStencilType : uint32_t
{
	DEPTH_ENABLE_STENCIL_ENABLE = 0,	// 深度ありステンシルあり
	DEPTH_ENABLE_STENCIL_DISABLE,		// 深度ありステンシルなし
	DEPTH_DISABLE_STENCIL_ENABLE,		// 深度なしステンシルあり
	DEPTH_DISABLE_STENCIL_DISABLE,		// 深度なしステンシルなし
	MAX,
};

enum class SamplerType : uint32_t
{
	CLAMP = 0,	// 0.0f,1.0f Color
	WRAP,		// 繰り返し
	BORDER,		// Border Color
	MIRROR,		// Mirror
	MAX,
};

//
class Device;
class Context;

#ifdef IS_DIRECTX11

class CommonState
{
public:

	virtual void* Get() = 0;
};

class BlendState : public CommonState 
{
public:

	HRESULT CreateState(Device* _pDevice, BlendType _blendType);
	void* Get() override { return m_state.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3D11BlendState> m_state;
};

class RasterizerState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, RasterType _rasterType);
	void* Get() override { return m_state.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_state;
};

class DepthStencilState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, DepthStencilType _depthStencilType);
	void* Get() override { return m_state.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_state;
};

class SamplerState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, SamplerType samplerType);
	void* Get() override { return m_state.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_state;
};

class PipelineStateObject
{
public:

	HRESULT InitStates(Device* _pDevice);

	BlendState* GetBlendState(BlendType _blendType);
	RasterizerState* GetRastrizerState(RasterType _rasterizerType);
	DepthStencilState* GetDepthStencilState(DepthStencilType _depthStencilType);
	SamplerState* GetSamplerState(SamplerType _samplerType);

private:

	std::unordered_map<BlendType, BlendState>				m_blendStates;
	std::unordered_map<RasterType, RasterizerState>			m_rasterizerStates;
	std::unordered_map<DepthStencilType, DepthStencilState> m_depthStencilStates;
	std::unordered_map<SamplerType, SamplerState>			m_samplerStates;
};


#elif defined IS_DIRECTX12

class CommonState
{
public:

	virtual void* Get() = 0;
};

class BlendState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, BlendType _blendType);
	void* Get() override { return &m_state; };

private:

	D3D12_BLEND_DESC m_state;
};

class RasterizerState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, RasterType _rasterType);
	void* Get() override { return &m_state; };

private:

	D3D12_RASTERIZER_DESC m_state;
};

class DepthStencilState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, DepthStencilType _depthStencilType);
	void* Get() override { return &m_state; };

private:

	D3D12_DEPTH_STENCIL_DESC m_state;
};

class SamplerState : public CommonState
{
public:

	HRESULT CreateState(Device* _pDevice, SamplerType samplerType);
	void* Get() override { return &m_state; };

private:

	D3D12_SAMPLER_DESC m_state;
};

class PipelineStateObject
{
public:

	HRESULT InitStates(Device* _pDevice);

	void SetStates(BlendType _blendType,
				   RasterType _rasterizerType,
				   DepthStencilType _depthStencilType,
				   SamplerType _samplerType);

private:

	Device* m_device = nullptr;

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineStateObject = nullptr;

	std::unordered_map<BlendType, BlendState>				m_blendStates;
	std::unordered_map<RasterType, RasterizerState>			m_rasterizerStates;
	std::unordered_map<DepthStencilType, DepthStencilState> m_depthStencilStates;
	std::unordered_map<SamplerType, SamplerState>			m_samplerStates;
};
#endif

#endif // !COMMONSTATE_H
