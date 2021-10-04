#pragma once
#ifndef SWAP_H
#define SWAP_H

#include <d3d11.h>
#include <wrl/client.h>
#include "Math.h"

namespace DirectX11 {

    using Microsoft::WRL::ComPtr;

    class SwapChain {

    public:

        bool CreateSwapChain(ID3D11Device* device, HWND hWnd, Vector2Int size);

        bool CreateRenderTaergetView(ID3D11Device* device);

        IDXGISwapChain* GetSwapChain(){ return m_SwapChain.Get(); }

        ID3D11RenderTargetView* GetRenderTargetView(){ return m_RenderTargetView.Get(); }

    private:

        ComPtr<IDXGISwapChain>          m_SwapChain;
        ComPtr<ID3D11RenderTargetView>  m_RenderTargetView;
    };
}
#endif // !SWAP_H
