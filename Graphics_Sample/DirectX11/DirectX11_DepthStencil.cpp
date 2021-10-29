#include "DirectX11/DirectX11_DepthStencil.h"

namespace DirectX11 {

    bool DirectX11_DepthStencil::CreateZBuffer(ID3D11Device* _pDevice, Vector2Int _size)
    {
        D3D11_TEXTURE2D_DESC desc;

        ZeroMemory(&desc,sizeof(desc));

        desc.Width = _size.x;
        desc.Height = _size.y;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        HRESULT hr = _pDevice->CreateTexture2D(&desc, nullptr, &m_deprhStencilBuffer);

        if (FAILED(hr)) {

            return false;
        }

        return true;
    }

    bool DirectX11_DepthStencil::CreateDepthStencil(ID3D11Device* _pDevice)
    {
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

        // ステンシルステート作成
        depthStencilDesc.DepthEnable = true;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

        depthStencilDesc.StencilEnable = true;
        depthStencilDesc.StencilReadMask = 0x01;
        depthStencilDesc.StencilWriteMask = 0xFF;

        // 表面の設定
        depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        // 裏面の設定
        depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        HRESULT hr =_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);

        if (FAILED(hr)) {

            return false;
        }

        // DepthStencilView 作成
        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
        depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0;

        hr = _pDevice->CreateDepthStencilView(m_deprhStencilBuffer.Get() ,&depthStencilViewDesc, &m_depthStencilView);

        if (FAILED(hr)) {

            return false;
        }

        return true;
    }

    ID3D11DepthStencilView* DirectX11_DepthStencil::GetStencilView() {

        return m_depthStencilView.Get();
    }

    ID3D11DepthStencilState* DirectX11_DepthStencil::GetStencilState() {

        return m_depthStencilState.Get();
    }
}
