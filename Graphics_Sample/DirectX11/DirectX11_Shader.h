#pragma once
#ifndef DX11_SHADER_H
#define DX11_SHADER_H

#include "GHI/GHI_Shader.h"

namespace DirectX11
{
	class DX11_Shader : public GHI::GHI_Shader
	{
	public:

		//void CreateShader(ShaderStage _shaderStage, GraphicsShaderDesc::Desc* _desc) override;

		void* GetVS() override { return m_vertexShader; };
		void* GetPS() override { return m_pixelShader; };
		void* GetInputLayout() override { return m_inputLayout; }

		void* Get() override { return nullptr; }

	private:

		ID3D11VertexShader* m_vertexShader = nullptr;
		ID3D11PixelShader* m_pixelShader = nullptr;
		ID3D11InputLayout* m_inputLayout = nullptr;
	};
}

#endif // !DX11_SHADER_H
