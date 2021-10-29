#pragma once
#ifndef COMMONSTATE_H
#define COMMONSTATE_H

#include "SwitchingAPI.h"

#include <wrl/client.h>
#include <unordered_map>
#include <memory>

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

enum class RasterizerType : uint32_t
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

namespace GHI 
{
	class GHI_BlendState 
	{
	public:

		virtual void* Get() = 0;

		virtual ~GHI_BlendState() {}
	};

	class GHI_RasterizerState 
	{
	public:

		virtual void* Get() = 0;

		virtual ~GHI_RasterizerState() {}
	};

	class GHI_DepthStencilState
	{
	public:

		virtual void* Get() = 0;

		virtual ~GHI_DepthStencilState() {}
	};

	class GHI_PipelineState
	{
	public:

		void SetBlendState(BlendType _blendType, std::unique_ptr<GHI_BlendState> _pBlendState);
		void SetRasterizerState(RasterizerType _rasterizerType, std::unique_ptr<GHI_RasterizerState> _pRasterizerState);
		void SetDepthStencilState(DepthStencilType _depthStencilType, std::unique_ptr<GHI_DepthStencilState> _pDepthStencilState);

		virtual void* Get(uint32_t hash) = 0;
		virtual void* GetRootSignature(uint32_t hash) = 0;

		GHI_BlendState* GetBlendState(BlendType _blendType) { return m_blendStates[_blendType].get(); };
		GHI_RasterizerState* GetRasterizerState(RasterizerType _rasterizerType) { return m_rasterizerStates[_rasterizerType].get(); };
		GHI_DepthStencilState* GetDepthStencilState(DepthStencilType _depthStencilType) { return m_depthStencilStates[_depthStencilType].get(); };

		virtual ~GHI_PipelineState() {}

	protected:

		std::unordered_map<BlendType, std::unique_ptr<GHI_BlendState>> m_blendStates;
		std::unordered_map<RasterizerType, std::unique_ptr<GHI_RasterizerState>> m_rasterizerStates;
		std::unordered_map<DepthStencilType, std::unique_ptr<GHI_DepthStencilState>> m_depthStencilStates;
	};
}

#endif // !COMMONSTATE_H
