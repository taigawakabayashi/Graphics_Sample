#include "DepthStencil.h"

namespace DirectX11 {

    bool DepthStencil::CreateZBuffer(ID3D11Device* device, Vector2Int size)
    {
        D3D11_TEXTURE2D_DESC desc;

        ZeroMemory(&desc,sizeof(desc));

        desc.Width = size.x;
        desc.Height = size.y;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        HRESULT hr = device->CreateTexture2D(&desc, nullptr, &m_deprhStencilBuffer);

        if (FAILED(hr)) {

            return false;
        }

        return true;
    }

    bool DepthStencil::CreateDepthStencil(ID3D11Device* device)
    {
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

        // �X�e���V���X�e�[�g�쐬
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
        depthStencilDesc.DepthEnable = true;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

        depthStencilDesc.StencilEnable = true;
        depthStencilDesc.StencilReadMask = 0x01;
        depthStencilDesc.StencilWriteMask = 0xFF;

        // �\�ʂ̐ݒ�
        depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        // ���ʂ̐ݒ�
        depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        HRESULT hr =device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);

        if (FAILED(hr)) {

            return false;
        }

        // DepthStencilView �쐬
        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
        depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0;

        hr = device->CreateDepthStencilView(m_deprhStencilBuffer.Get() ,&depthStencilViewDesc, &m_depthStencilView);

        if (FAILED(hr)) {

            return false;
        }

        return true;
    }

    ID3D11DepthStencilView* DepthStencil::GetStencilView() {

        return m_depthStencilView.Get();
    }

    ID3D11DepthStencilState* DepthStencil::GetStencilState() {

        return m_depthStencilState.Get();
    }
}