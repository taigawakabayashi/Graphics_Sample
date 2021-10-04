#pragma once
#ifndef DEPTH_H
#define DEPTH_H

#include <d3d11.h>
#include <wrl/client.h>
#include "Math.h"

namespace DirectX11 {

    using  Microsoft::WRL::ComPtr;

    class DepthStencil {

    public:

        bool CreateZBuffer(ID3D11Device* device, Vector2Int size);
        bool CreateDepthStencil(ID3D11Device* device);

        ID3D11DepthStencilView* GetStencilView();
        ID3D11DepthStencilState* GetStencilState();

    private:

        ComPtr<ID3D11Texture2D>             m_deprhStencilBuffer;   // �y�o�b�t�@�A�X�e���V���o�b�t�@
        ComPtr<ID3D11DepthStencilState>     m_depthStencilState;    // �y�o�b�t�@�A�X�e���V���X�e�[�g
        ComPtr<ID3D11DepthStencilView>      m_depthStencilView;     // �y�o�b�t�@�A�X�e���V���r���[
    };

}
#endif // !DEPTH_H