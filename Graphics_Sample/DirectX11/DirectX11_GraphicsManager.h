#pragma once
#ifndef DX11_H
#define DX11_H

#include <d3d11.h>
#include <wrl/client.h>

#include <DirectX11/DirectX11_DepthStencil.h>
#include <DirectX11/DirectX11_Rasterizer.h>
#include <DirectX11/DirectX11_SwapChain.h>
#include <DirectX11/DirectX11_ViewPort.h>

namespace DirectX11
{
    class DirectX11_GraphicsMng 
    {
    public:

        DirectX11_GraphicsMng(const DirectX11_GraphicsMng&) = delete;
        DirectX11_GraphicsMng& operator = (const DirectX11_GraphicsMng&) = delete;
        DirectX11_GraphicsMng(DirectX11_GraphicsMng&&) = delete;
        DirectX11_GraphicsMng& operator = (DirectX11_GraphicsMng&&) = delete;

        static DirectX11_GraphicsMng* GetInstance() {

            static DirectX11_GraphicsMng instance;

            return &instance;
        }

        bool Init(HWND _hWnd, Vector2Int _size);
        void Uninit();

        void Swap();

        void ClearRenderTargetView(float _clearColor[]);
        void ClearDepthStencilView();
        void SetViewPort();
        void TurnOnZBuffer();
        void TurnOffZBuffer();
        void TurnOnAlphaBlending();
        void TurnOffAlphaBlending();

        ID3D11Device* GetDevice() { return m_Device.Get(); }
        ID3D11DeviceContext* GetImmediateContext() { return m_ImmediateContext.Get(); }

    private:

        ComPtr<ID3D11Device>							m_Device = nullptr;				// デバイス
        ComPtr<ID3D11DeviceContext>						m_ImmediateContext = nullptr;	//デバイスコンテキスト
        DirectX11_SwapChain								m_SwapChain;			        // スワップチェイン
        DirectX11_ViewPort								m_ViewPort;				        // ビューポート
        DirectX11_DepthStencil							m_DepthStencil;
        DirectX11_Rasterizer							m_Rasterizer;
        ComPtr<ID3D11SamplerState>                      m_sampler;

        D3D_DRIVER_TYPE									m_DriverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_NULL;			// ドライバタイプ
        D3D_FEATURE_LEVEL								m_FeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0;			// 機能レベル

        ComPtr<ID3D11BlendState>						m_alphaEnableBlendingState;		// アルファブレンドステート（有効）
        ComPtr<ID3D11BlendState>						m_alphaDisableBlendingState;	// アルファブレンドステート（無効）

        DirectX11_GraphicsMng(){}

    };

    void BeforeRender(float _clearColor[]);
    void AfterRender();

    void TurnOnZBuffer();
    void TurnOffZBuffer();

    void TurnOnAlphaBlend();
    void TurnOffAlphaBlend();
}
#endif // !DX11_H
