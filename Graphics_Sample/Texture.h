#pragma once
#ifndef TEX_H
#define TEX_H
#include <d3d11.h>
#include <wrl/client.h>

class Texture   
{
public:

    bool CreateTexture(ID3D11ShaderResourceView** _ppSrv);

    ID3D11ShaderResourceView* GetSrv(){ return m_texSrv.Get(); }

private:

    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texSrv;
};


#endif // !TEX_H
