#include <DirectX11/DirectX11_GraphicsManager.h>
#include "Texture.h"

bool Texture::CreateTexture(ID3D11ShaderResourceView** _ppSrv)
{
    ID3D11Device* device = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetDevice();

    uint32_t* Color = new uint32_t[256 * 256];

    for (int x = 0; x < 256; ++x)
    {
        for (int y = 0; y < 256; ++y)
        {
            if (x / 128 != 1) 
            {
                if (y / 128 != 1) 
                {
                    // ABGR
                    Color[x + y * 256] = 0xffff0000;
                }
                else
                {
                    Color[x + y * 256] = 0xffff00ff;
                }
            }
            else 
            {
                if (y / 128 != 1)
                {
                    Color[x + y * 256] = 0xff00ffff;
                }
                else
                {
                    Color[x + y * 256] = 0xff00ff00;
                }
            }

        }
    }

    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));

    textureDesc.Width = 256;
    textureDesc.Height = 256;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DYNAMIC;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData;

    initData.pSysMem = Color;
    initData.SysMemPitch = sizeof(Color[0]) * 256;
    initData.SysMemSlicePitch = sizeof(Color[0]) * 256 * 256;

    HRESULT hr = device->CreateTexture2D(&textureDesc, &initData, &m_texture);

    if(FAILED(hr))
        return false;

    delete[] Color;
    Color = nullptr;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));

    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Format = textureDesc.Format;
    srvDesc.Texture2D.MipLevels = textureDesc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;

    hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, _ppSrv);

    if(FAILED(hr))
        return false;

    return true;
}
