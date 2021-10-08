#include "DirectX11/DirectX11_SwapChain.h"

namespace DirectX11 {

    bool DirectX11_SwapChain::CreateSwapChain(ID3D11Device* _pDevice, HWND _hWnd, Vector2Int _size)
    {
        HRESULT hr;

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
        swapChainDesc.BufferCount                           = 1;
        swapChainDesc.BufferDesc.Width                      = _size.x;
        swapChainDesc.BufferDesc.Height                     = _size.y;
        swapChainDesc.BufferDesc.Format                     = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator      = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator    = 1;
        swapChainDesc.BufferDesc.ScanlineOrdering           = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling                    = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.BufferUsage                           = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow                          = _hWnd;
        swapChainDesc.SampleDesc.Count                      = 1;
        swapChainDesc.SampleDesc.Quality                    = 0;
        swapChainDesc.SwapEffect                            = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Windowed                              = true;
        swapChainDesc.Flags                                 = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        IDXGIDevice1* pDXGI = nullptr;
        IDXGIAdapter* pAdapter = nullptr;
        IDXGIFactory* pFactory = nullptr;

        hr = _pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDXGI);
        if (FAILED(hr))
            return false;

        hr = pDXGI->GetAdapter(&pAdapter);
        if (FAILED(hr))
            return false;

        hr = pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);
        if (FAILED(hr))
            return false;

        hr = pFactory->CreateSwapChain(_pDevice, &swapChainDesc, &m_SwapChain);
        if (FAILED(hr))
            return false;

        pDXGI->Release();
        pDXGI = nullptr;
        pAdapter->Release();
        pAdapter = nullptr;
        pFactory->Release();
        pFactory = nullptr;

        ID3D11Texture2D* pBackBuffer = nullptr;

        // スワップチェインの作成
        hr = m_SwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

        if(FAILED(hr))
            return false;

        // レンダーターゲットビューを作成
        hr = _pDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_RenderTargetView.GetAddressOf());
        pBackBuffer->Release();
        pBackBuffer = nullptr;

        if(FAILED(hr))
            return false;

        return true;
    }

    bool DirectX11_SwapChain::CreateRenderTaergetView(ID3D11Device* _pDevice)
    {
        HRESULT hr;

        // レンダリングターゲットを作成
        // バックバッファのポインタを取得
        ID3D11Texture2D* pBackBuffer = NULL;

        hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        if (FAILED(hr))
            return false;

        // バックバッファへのポインタを指定してレンダーターゲットビューを作成
        hr = _pDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_RenderTargetView.GetAddressOf());
        pBackBuffer->Release();
        pBackBuffer = 0;

        if (FAILED(hr))
            return false;

        return true;
    }
}
