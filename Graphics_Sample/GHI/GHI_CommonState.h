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
	ALPHA_ENABLE = 0,	// �A���t�@�u�����h����
	ALPHA_DISABLE,		// �A���t�@�u�����h�Ȃ�
	MAX,
};

enum class RasterType : uint32_t
{
	CULL_NONE_FILL_SOLID = 0,	// �J�����O�Ȃ�
	CULL_FRONT_FILL_SOLID,		// �\�ʃJ�����O
	CULL_BACK_FILL_SOLID,		// ���ʃJ�����O
	CULL_NONE_FILL_WIREFRAME,	// �J�����O�Ȃ����C���[�t���[��
	CULL_FRONT_FILL_WIREFRAME,	// �\�ʃJ�����O���C���[�t���[��
	CULL_BACK_FILL_WIREFRAME,	// ���ʃJ�����O���C���[�t���[��
	MAX,
};

enum class DepthStencilType : uint32_t
{
	DEPTH_ENABLE_STENCIL_ENABLE = 0,	// �[�x����X�e���V������
	DEPTH_ENABLE_STENCIL_DISABLE,		// �[�x����X�e���V���Ȃ�
	DEPTH_DISABLE_STENCIL_ENABLE,		// �[�x�Ȃ��X�e���V������
	DEPTH_DISABLE_STENCIL_DISABLE,		// �[�x�Ȃ��X�e���V���Ȃ�
	MAX,
};

enum class SamplerType : uint32_t
{
	CLAMP = 0,	// 0.0f,1.0f Color
	WRAP,		// �J��Ԃ�
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