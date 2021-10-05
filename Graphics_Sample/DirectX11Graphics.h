#pragma once
#ifndef DX11_H
#define DX11_H

#include <d3d11.h>
#include <wrl/client.h>
#include "DepthStencil.h"
#include "Rasterizer.h"
#include "SwapChain.h"
#include "ViewPort.h"

namespace DirectX11
{
    class GraphicsMng 
    {
    public:

        GraphicsMng(const GraphicsMng&) = delete;
        GraphicsMng& operator = (const GraphicsMng&) = delete;
        GraphicsMng(GraphicsMng&&) = delete;
        GraphicsMng& operator = (GraphicsMng&&) = delete;

        static GraphicsMng* GetInstance() {

            static GraphicsMng instance;

            return &instance;
        }

        bool Init(HWND hWnd, Vector2Int size);
        void Uninit();

        void Swap();

        void ClearRenderTargetView(float ClearColor[]);
        void ClearDepthStencilView();
        void SetViewPort();
        void TurnOnZBuffer();
        void TurnOffZBuffer();
        void TurnOnAlphaBlending();
        void TurnOffAlphaBlending();

        ID3D11Device* GetDevice() { return m_Device.Get(); }
        ID3D11DeviceContext* GetImmediateContext() { return m_ImmediateContext.Get(); }

    private:

        ComPtr<ID3D11Device>							m_Device;				// デバイス
        ComPtr<ID3D11DeviceContext>						m_ImmediateContext;		// デバイスコンテキスト
        std::vector<ComPtr<ID3D11DeviceContext>>		m_DeferredContext;		// 遅延コンテキスト
        SwapChain										m_SwapChain;			// スワップチェイン
        ViewPort										m_ViewPort;				// ビューポート
        DepthStencil									m_DepthStencil;
        Rasterizer										m_Rasterizer;
        ComPtr<ID3D11SamplerState>                      m_sampler;

        D3D_DRIVER_TYPE									m_DriverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_NULL;			// ドライバタイプ
        D3D_FEATURE_LEVEL								m_FeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0;			// 機能レベル

        ComPtr<ID3D11BlendState>						m_alphaEnableBlendingState;		// アルファブレンドステート（有効）
        ComPtr<ID3D11BlendState>						m_alphaDisableBlendingState;	// アルファブレンドステート（無効）

        GraphicsMng(){}

    };

    void BeforeRender(float ClearColor[]);
    void AfterRender();

    void TurnOnZBuffer();
    void TurnOffZBuffer();

    void TurnOnAlphaBlend();
    void TurnOffAlphaBlend();
}
#endif // !DX11_H
