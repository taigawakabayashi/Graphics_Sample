#include "GHI/GHI_CommonState.h"
#include "GHI/GHI_Device.h"
#include "Shader.h"

namespace GHI
{
	void GHI_PipelineState::SetBlendState(BlendType _blendType, std::unique_ptr <GHI::GHI_BlendState> _pBlendState)
	{
		m_blendStates[_blendType] = std::move(_pBlendState);
	}

	void GHI_PipelineState::SetRasterizerState(RasterizerType _rasterizerType, std::unique_ptr <GHI::GHI_RasterizerState> _pRasterizerState)
	{
		m_rasterizerStates[_rasterizerType] = std::move(_pRasterizerState);
	}

	void GHI_PipelineState::SetDepthStencilState(DepthStencilType _depthStencilType, std::unique_ptr <GHI::GHI_DepthStencilState> _pDepthStencilState)
	{
		m_depthStencilStates[_depthStencilType] = std::move(_pDepthStencilState);
	}
}
