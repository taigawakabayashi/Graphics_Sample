#pragma once
#ifndef TEX_H
#define TEX_H
#include <d3d11.h>
#include <d3d12.h>
#include <wrl/client.h>

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
