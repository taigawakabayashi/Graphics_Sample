#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <d3dcompiler.h>
#include <d3d11.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <locale>
#include <wrl/client.h>

class Shader 
{
public:
    
    bool Init();

    ID3D11VertexShader* GetVS(){ return m_vertexShader.Get(); };
    ID3D11InputLayout* GetIL(){ return m_inputLayout.Get(); };
    ID3D11PixelShader* GetPS(){ return m_pixelShader.Get(); };

private:
    
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    bool CreateVertexShader(ID3D11Device* device, 
                            const char* fileName,
                            LPCSTR entryPoint,
                            LPCSTR shaderModel,
                            D3D11_INPUT_ELEMENT_DESC* layout,
                            uint32_t numElements,
                            ID3D11ClassLinkage* pClassLinkage,
                            ID3D11VertexShader** ppVertexShader,
                            ID3D11InputLayout ** ppInputLayout);

    bool CreatePixelShader(ID3D11Device* device,
                           const char* fileName,
                           LPCSTR entryPoint,
                           LPCSTR shaderModel,
                           ID3D11ClassLinkage* pClassLinkage,
                           ID3D11PixelShader** ppPixelShader);

    // Shaderをコンパイル
    HRESULT CompileShader(const char* szFileName, 
                          LPCSTR szEntryPoint, 
                          LPCSTR szShaderModel, 
                          void** ShaderObject, 
                          size_t& ShaderObjectSize, 
                          ID3DBlob** ppBlobOut);

    // ファイル名を所得
    std::string ExtractFileName(std::string fullpath, char split);

    // ファイルの拡張子を取得する
    std::string GetFileExt(const char* filename);

    // コンパイル済みシェーダーファイルを読み込む
    bool readShader(const char* csoName, std::vector<unsigned char>& byteArray);

    HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

};

#endif // !SHADER_H

