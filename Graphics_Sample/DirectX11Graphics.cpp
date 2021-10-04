#include "DirectX11Graphics.h"

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"D3DCompiler.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dxguid.lib")

namespace DirectX11 
{
    bool GraphicsMng::Init(HWND hWnd, Vector2Int size)
    {
        HRESULT hr = S_OK;
        IDXGIFactory* pFactory = nullptr;				// factory
        IDXGIAdapter* pAdapter = nullptr;				// videocard
        IDXGIOutput* pAdapterOutput = nullptr;;		    // monitor

        uint32_t numModes = 0;

        DXGI_MODE_DESC* displayModeList = nullptr;
        D3D11_BLEND_DESC blendStateDesc;

        D3D_DRIVER_TYPE driverType[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

        uint32_t numDriverTypes = ARRAYSIZE(driverType);
        uint32_t createDeviceFlag = 0;

        // 機能レベル
        D3D_FEATURE_LEVEL fetureLevels[] = 
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        uint32_t numFetureLevels = ARRAYSIZE(fetureLevels);

        // Create DXGI Factory
        hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
        if(FAILED(hr))
            return false;

        hr = pFactory->EnumAdapters(0, &pAdapter);
        if(FAILED(hr))
            return false;

        hr = pAdapter->EnumOutputs(0, &pAdapterOutput);
        if(FAILED(hr))
            return false;

        hr = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
        if(FAILED(hr))
            return false;

        displayModeList = new DXGI_MODE_DESC[numModes];
        if(!displayModeList)
            return false;

        hr = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

        delete[] displayModeList;
        displayModeList = nullptr;

        pAdapterOutput->Release();
        pAdapterOutput = nullptr;

        pAdapter->Release();
        pAdapter = nullptr;

        pFactory->Release();
        pFactory = nullptr;

        for (uint32_t driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
        {
            m_DriverType = driverType[driverTypeIndex];

            hr=D3D11CreateDevice(nullptr,
                                 m_DriverType,
                                 nullptr,
                                 createDeviceFlag,
                                 fetureLevels,
                                 numFetureLevels,
                                 D3D11_SDK_VERSION,
                                 &m_Device,
                                 &m_FeatureLevel,
                                 &m_ImmediateContext);

            if(SUCCEEDED(hr))
                break;
        }

        if(FAILED(hr))
            return false;

        // ブレンドステート初期化
        ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

        // ブレンドステート設定(アルファブレンド可)
        blendStateDesc.RenderTarget[0].BlendEnable = true;
        blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

        // ブレンドステート作成
        hr = m_Device->CreateBlendState(&blendStateDesc, &m_alphaEnableBlendingState);
        if(FAILED(hr))
            return false;

        // ブレンドステート設定(アルファブレンド不可)
        blendStateDesc.RenderTarget[0].BlendEnable = false;

        // ブレンドステート作成
        hr = m_Device->CreateBlendState(&blendStateDesc, &m_alphaDisableBlendingState);
        if (FAILED(hr))
            return false;

        // スワップチェイン作成
        hr = m_SwapChain.CreateSwapChain(m_Device.Get(), hWnd, size);

        // ビューポートを作成
        m_ViewPort.CreateViewPort(Vector2(static_cast<float>(size.x), static_cast<float>(size.x)), Vector2(0.0f, 0.0f));

        // Zバッファの作成
        m_DepthStencil.CreateZBuffer(m_Device.Get(), size);

        // DepthStencilの作成
        m_DepthStencil.CreateDepthStencil(m_Device.Get());

        // ラスタライザーの作成
        m_Rasterizer.CreateRasterizer(m_Device.Get());

        return true;
    }

    void GraphicsMng::Uninit()
    {
        if (m_ImmediateContext) 
        {
            m_ImmediateContext->ClearState();
        }

        if (m_SwapChain.GetSwapChain()) 
        {
            m_SwapChain.GetSwapChain()->SetFullscreenState(false, nullptr);
        }
    }

    void GraphicsMng::Swap()
    {
        m_SwapChain.GetSwapChain()->Present(0, 0);
    }

    void GraphicsMng::ClearRenderTargetView(float ClearColor[]) 
    {
        m_ImmediateContext->ClearRenderTargetView(m_SwapChain.GetRenderTargetView(), ClearColor);

        ID3D11RenderTargetView* temp = m_SwapChain.GetRenderTargetView();

        m_ImmediateContext->OMSetRenderTargets(1, &temp, m_DepthStencil.GetStencilView());
    }

    void GraphicsMng::ClearDepthStencilView()
    {
        m_ImmediateContext->ClearDepthStencilView(m_DepthStencil.GetStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    void GraphicsMng::SetViewPort()
    {
        m_ViewPort.SetViewPort(m_ImmediateContext.Get());
    }

    void GraphicsMng::TurnOnZBuffer() {

        ID3D11RenderTargetView* rtvtable[1];

        rtvtable[0] = m_SwapChain.GetRenderTargetView();

        m_ImmediateContext->OMSetRenderTargets(
            1,										// ターゲット
            rtvtable,								// ビューテーブル
            m_DepthStencil.GetStencilView()			// 深度バッファあり
        );
    }

    void GraphicsMng::TurnOffZBuffer() {

        ID3D11RenderTargetView* rtvtable[1];

        rtvtable[0] = m_SwapChain.GetRenderTargetView();

        m_ImmediateContext->OMSetRenderTargets(
            1,										// ターゲット
            rtvtable,								// ビューテーブル
            nullptr									// 深度バッファなし
        );
    }

    void GraphicsMng::TurnOnAlphaBlending() {

        float blendFactor[4];

        blendFactor[0] = 0.0f;
        blendFactor[1] = 0.0f;
        blendFactor[2] = 0.0f;
        blendFactor[3] = 0.0f;

        //アルファブレンドをONにする
        m_ImmediateContext->OMSetBlendState(m_alphaEnableBlendingState.Get(), blendFactor, 0xffffffff);
        return;
    }

    void GraphicsMng::TurnOffAlphaBlending() {

        float blendFactor[4];

        blendFactor[0] = 0.0f;
        blendFactor[1] = 0.0f;
        blendFactor[2] = 0.0f;
        blendFactor[3] = 0.0f;

        //アルファブレンドをOFFにする
        m_ImmediateContext->OMSetBlendState(m_alphaDisableBlendingState.Get(), blendFactor, 0xffffffff);
        return;
    }

    void BeforeRender(float ClearColor[]) 
    {
        GraphicsMng::GetInstance()->ClearRenderTargetView(ClearColor);

        GraphicsMng::GetInstance()->ClearDepthStencilView();

        GraphicsMng::GetInstance()->SetViewPort();
    }

    void AfterRender() 
    {
        GraphicsMng::GetInstance()->Swap();
    }

    void TurnOnZBuffer()
    {
        GraphicsMng::GetInstance()->TurnOnZBuffer();
    }

    void TurnOffZBuffer() 
    {
        GraphicsMng::GetInstance()->TurnOffZBuffer();
    }

    void TurnOnAlphaBlend() 
    {
        GraphicsMng::GetInstance()->TurnOnAlphaBlending();
    }

    void TurnOffAlphaBlend() 
    {
        GraphicsMng::GetInstance()->TurnOffAlphaBlending();
    }
}
