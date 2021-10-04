#include "Rasterizer.h"

namespace DirectX11 
{
    bool Rasterizer::CreateRasterizer(ID3D11Device* device)
    {
        D3D11_RASTERIZER_DESC rasterDesc;
        ZeroMemory(&rasterDesc, sizeof(rasterDesc));

        rasterDesc.AntialiasedLineEnable = false;
        rasterDesc.CullMode = D3D11_CULL_BACK;
        rasterDesc.DepthBias = 0;
        rasterDesc.DepthBiasClamp = 0.0f;
        rasterDesc.DepthClipEnable = true;
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.MultisampleEnable = false;
        rasterDesc.ScissorEnable = false;
        rasterDesc.SlopeScaledDepthBias = 0.0f;

        HRESULT hr = device->CreateRasterizerState(&rasterDesc, &m_rasterState);

        if (FAILED(hr))
            return false;

        return true;
    }

    void Rasterizer::SetRasterizer(ID3D11DeviceContext* devcontext)
    {
        devcontext->RSSetState(m_rasterState.Get());
    }

}
