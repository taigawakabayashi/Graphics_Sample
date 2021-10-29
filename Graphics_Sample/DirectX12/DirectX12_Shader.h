#pragma once
#ifndef DX12_SHADER_H
#define DX12_SHADER_H

#include "GHI/GHI_Shader.h"

namespace DirectX12 
{
	class DX12_Shader : public GHI::GHI_Shader 
	{
	public:

		//void CreateShader(ShaderStage _shaderStage, GraphicsShaderDesc::Desc* _desc) override;

		void* GetVS() override { return &m_vertexShader; }
		void* GetPS() override { return &m_pixelShader; }
		void* GetInputLayout() override { return &m_inputLayout; }

		void* Get() override { return m_rootSignature; }

	private:

		D3D12_SHADER_BYTECODE m_vertexShader{};
		D3D12_SHADER_BYTECODE m_pixelShader{};

		D3D12_INPUT_LAYOUT_DESC m_inputLayout{};

		ID3D12RootSignature* m_rootSignature = nullptr;
	};
}

#endif // !DX12_SHADER_H
