#pragma once
#ifndef TEX_H
#define TEX_H
#include <d3d11.h>
#include <d3d12.h>
#include <wrl/client.h>

enum class Format 
{
    UNKNOWN = 0,

    R32G32B32A32_TYPELESS,
    R32G32B32A32_FLOAT,
    R32G32B32A32_UINT,
    R32G32B32A32_SINT,

    R32G32B32_TYPELESS,
    R32G32B32_FLOAT,
    R32G32B32_UINT,
    R32G32B32_SINT,

    R16G16B16A16_TYPELESS,
    R16G16B16A16_FLOAT,
    R16G16B16A16_UNORM,
    R16G16B16A16_UINT,
    R16G16B16A16_SNORM,
    R16G16B16A16_SINT,

    R32G32_TYPELESS,
    R32G32_FLOAT,
    R32G32_UINT,
    R32G32_SINT,

    R11G11B10_FLOAT = 26,

    R8G8B8A8_TYPELESS,
    R8G8B8A8_UNORM,
    R8G8B8A8_UNORM_SRGB,
    R8G8B8A8_UINT,
    R8G8B8A8_SNORM,
    R8G8B8A8_SINT,

    R16G16_TYPELESS,
    R16G16_FLOAT,
    R16G16_UNORM,
    R16G16_UINT,
    R16G16_SNORM,
    R16G16_SINT,

    R32_TYPELESS,
    D32_FLOAT,
    R32_FLOAT,
    R32_UINT,
    R32_SINT,

    R24G8_TYPELESS,

    D24_UNORM_S8_UINT,
    R24_UNORM_X8_TYPELESS,
    X24_TYPELESS_G8_UINT,

    R8G8_TYPELESS,
    R8G8_UNORM,
    R8G8_UINT,
    R8G8_SNORM,
    R8G8_SINT,

    R16_TYPELESS,
    R16_FLOAT,
    D16_UNORM,
    R16_UNORM,
    R16_UINT,
    R16_SNORM,
    R16_SINT,

    R8_TYPELESS,
    R8_UNORM,
    R8_UINT,
    R8_SNORM,
    R8_SINT,

    MAX,
};

class Texture   
{
public:

    bool CreateTexture(ID3D11ShaderResourceView** _ppSrv);
    bool CreateTexture12();

    void SetTexture(ID3D12GraphicsCommandList* _pCommandList);

    ID3D11ShaderResourceView* GetSrv(){ return m_texSrv.Get(); }

private:

    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texSrv;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    m_texSrvDescriptorHeap;
    Microsoft::WRL::ComPtr<ID3D12Resource>          m_texture12;
};


#endif // !TEX_H
