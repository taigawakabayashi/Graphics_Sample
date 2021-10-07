#pragma once
#ifndef DEPTH_H
#define DEPTH_H

#include <d3d11.h>
#include <wrl/client.h>
#include <Utility/Math.h>

namespace DirectX11 {

    using  Microsoft::WRL::ComPtr;

    class DirectX11_DepthStencil {

    public:

        bool CreateZBuffer(ID3D11Device* _pDevice, Vector2Int _size);
        bool CreateDepthStencil(ID3D11Device* _pDevice);

        ID3D11DepthStencilView* GetStencilView();
        ID3D11DepthStencilState* GetStencilState();

    private:

        ComPtr<ID3D11Texture2D>             m_deprhStencilBuffer;   // Ｚバッファ、ステンシルバッファ
        ComPtr<ID3D11DepthStencilState>     m_depthStencilState;    // Ｚバッファ、ステンシルステート
        ComPtr<ID3D11DepthStencilView>      m_depthStencilView;     // Ｚバッファ、ステンシルビュー
    };

}
#endif // !DEPTH_H
