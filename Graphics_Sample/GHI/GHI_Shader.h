#pragma once
#ifndef GHI_SHADER_H
#define GHI_SHADER_H

#include <d3dcompiler.h>
#include <d3d11.h>
#include <d3d12.h>
#include <filesystem>

enum class ShaderStage
{
	VS,
	HS,
	DS,
	GS,
	PS,
	MAX
};

struct GraphicsShaderDesc
{
	struct Desc
	{
		std::filesystem::path path;
		LPCSTR entryPoint;
		LPCSTR shaderModel;
	}vertexShader,
		hulShader,
		domainShader,
		geometryShader,
		pixelShader;
};

namespace GHI
{
	class GHI_Shader 
	{
	public:

		//virtual void CreateShader(ShaderStage _shaderStage, GraphicsShaderDesc::Desc* _desc) = 0;

		virtual void* GetVS() = 0;
		virtual void* GetPS() = 0;
		virtual void* GetInputLayout() = 0;
		virtual void* Get() = 0;

		virtual ~GHI_Shader() {}

	private:

	};
}

#endif // !GHI_SHADER_H
