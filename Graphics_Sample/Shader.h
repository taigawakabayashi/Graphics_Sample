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

    static Shader* GetInstance() 
    {
        static Shader instance;

        return &instance;
    }

    Shader(const Shader&) = delete;
    Shader& operator = (const Shader&) = delete;
    Shader(Shader&&) = delete;
    Shader& operator = (Shader&&) = delete;

    ID3D11VertexShader* GetVS(){ return m_vertexShader.Get(); };
    ID3D11InputLayout* GetIL(){ return m_inputLayout.Get(); };
    ID3D11PixelShader* GetPS(){ return m_pixelShader.Get(); };

private:
    
    Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

    Shader(){}

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

