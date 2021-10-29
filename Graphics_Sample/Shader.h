#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <d3dcompiler.h>
#include <d3d11.h>
#include <d3d12.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <locale>
#include <filesystem>
#include <wrl/client.h>

enum class ShadersStage
{
	VS,
	HS,
	DS,
	GS,
	PS,
	MAX
};

class Shader 
{
public:
	
	static Shader* GetInstance() 
	{
		static Shader instance;

		return &instance;
	}

	bool Init();
	bool InitDirectX12();

	// 11
	ID3D11VertexShader* GetVS(){ return m_vertexShader.Get(); };
	ID3D11InputLayout* GetIL(){ return m_inputLayout.Get(); };
	ID3D11PixelShader* GetPS(){ return m_pixelShader.Get(); };

	// 12
	D3D12_SHADER_BYTECODE m_shaders[static_cast<int>(ShadersStage::MAX)]{};
	D3D12_SHADER_BYTECODE GetShaderByte(ShadersStage _shaders){ return m_shaders[static_cast<int>(_shaders)]; };

private:
	
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout = nullptr;

	Shader(){}
	Shader(const Shader&) = delete;
	Shader& operator = (const Shader&) = delete;
	Shader(Shader&&) = delete;
	Shader& operator = (Shader&&) = delete;

	bool CreateVertexShader(ID3D11Device* _pDevice, 
							const char* _pFileName,
							LPCSTR _entryPoint,
							LPCSTR _shaderModel,
							D3D11_INPUT_ELEMENT_DESC* _pLayout,
							uint32_t _numElements,
							ID3D11ClassLinkage* _pClassLinkage,
							ID3D11VertexShader** _ppVertexShader,
							ID3D11InputLayout ** _ppInputLayout);

	bool CreatePixelShader(ID3D11Device* _pDevice,
						   const char* _pFileName,
						   LPCSTR _entryPoint,
						   LPCSTR _shaderModel,
						   ID3D11ClassLinkage* _pClassLinkage,
						   ID3D11PixelShader** _ppPixelShader);
	
	bool LoadShaderFile(LPCWSTR _pFileName, LPCSTR _entryPoint, LPCSTR _shaderModel, ShadersStage _shaders);

	// Shaderをコンパイル
	HRESULT CompileShader(const char* _pFileName, 
						  LPCSTR _entryPoint, 
						  LPCSTR _shaderModel, 
						  void** _ppShaderObject, 
						  size_t& _shaderObjectSize, 
						  ID3DBlob** _ppBlobOut);

	// ファイル名を所得
	std::string ExtractFileName(std::string _fullPath, char _split);

	// ファイルの拡張子を取得する
	std::string GetFileExt(const char* _pFileName);

	// コンパイル済みシェーダーファイルを読み込む
	bool readShader(const char* _pCsoName, std::vector<unsigned char>& _byteArray);

	// ファイルからシェーダーを読み込みコンパイルする
	HRESULT CompileShaderFromFile(const char* _pFileName, LPCSTR _pEntryPoint, LPCSTR _shaderModel, ID3DBlob** _ppBlobOut);

};

#endif // !SHADER_H

