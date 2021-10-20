#include "DirectX11/DirectX11_GraphicsManager.h"

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"D3DCompiler.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dxguid.lib")

namespace DirectX11
{
	bool DirectX11_GraphicsMng::Init(HWND _hWnd, Vector2Int _size)
	{
		HRESULT hr = S_OK;

		// ドライバータイプ
		D3D_DRIVER_TYPE driverType[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
		};

		uint32_t numDriverTypes = ARRAYSIZE(driverType);
		uint32_t createDeviceFlag = 0;

#ifdef _DEBUG

		createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;

#endif // _DEBUG


		// 機能レベル
		D3D_FEATURE_LEVEL fetureLevels[] = 
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		uint32_t numFetureLevels = ARRAYSIZE(fetureLevels);

		for (uint32_t driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
		{
			m_DriverType = driverType[driverTypeIndex];

			// デバイスの作成
			hr = D3D11CreateDevice(nullptr,
								   m_DriverType,
								   nullptr,
								   createDeviceFlag,
								   fetureLevels,
								   numFetureLevels,
								   D3D11_SDK_VERSION,
								   &m_Device,
								   nullptr,
								   &m_ImmediateContext);

			if(SUCCEEDED(hr))
				break;
		}

		if(FAILED(hr))
			return false;

		D3D11_BLEND_DESC blendStateDesc;
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
		m_SwapChain.CreateSwapChain(m_Device.Get(), _hWnd, _size);

		// ビューポートを作成
		m_ViewPort.CreateViewPort(Vector2(static_cast<float>(_size.x), static_cast<float>(_size.y)), Vector2(0.0f, 0.0f));

		// Zバッファの作成
		m_DepthStencil.CreateZBuffer(m_Device.Get(), _size);

		// DepthStencilの作成
		m_DepthStencil.CreateDepthStencil(m_Device.Get());

		// ラスタライザーの作成
		m_Rasterizer.CreateRasterizer(m_Device.Get());

		// サンプラーの設定
		D3D11_SAMPLER_DESC smpDesc;
		ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));

		smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		hr = m_Device->CreateSamplerState(&smpDesc, &m_sampler);
		if (FAILED(hr)) 
			return false;

		m_ImmediateContext->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

		return true;
	}

	void DirectX11_GraphicsMng::Uninit()
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

	void DirectX11_GraphicsMng::Swap()
	{
		m_SwapChain.GetSwapChain()->Present(0, 0);
	}

	void DirectX11_GraphicsMng::ClearRenderTargetView(float _clearColor[]) 
	{
		m_ImmediateContext->ClearRenderTargetView(m_SwapChain.GetRenderTargetView(), _clearColor);

		ID3D11RenderTargetView* temp = m_SwapChain.GetRenderTargetView();

		m_ImmediateContext->OMSetRenderTargets(1, &temp, m_DepthStencil.GetStencilView());
	}

	void DirectX11_GraphicsMng::ClearDepthStencilView()
	{
		m_ImmediateContext->ClearDepthStencilView(m_DepthStencil.GetStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DirectX11_GraphicsMng::SetViewPort()
	{
		m_ViewPort.SetViewPort(m_ImmediateContext.Get());
	}

	void DirectX11_GraphicsMng::TurnOnZBuffer() 
	{
		ID3D11RenderTargetView* rtvtable[1];

		rtvtable[0] = m_SwapChain.GetRenderTargetView();

		m_ImmediateContext->OMSetRenderTargets(
			1,										// ターゲット
			rtvtable,								// ビューテーブル
			m_DepthStencil.GetStencilView()			// 深度バッファあり
		);
	}

	void DirectX11_GraphicsMng::TurnOffZBuffer() 
	{
		ID3D11RenderTargetView* rtvtable[1];

		rtvtable[0] = m_SwapChain.GetRenderTargetView();

		m_ImmediateContext->OMSetRenderTargets(
			1,										// ターゲット
			rtvtable,								// ビューテーブル
			nullptr									// 深度バッファなし
		);
	}

	void DirectX11_GraphicsMng::TurnOnAlphaBlending() 
	{
		float blendFactor[4];

		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;

		//アルファブレンドをONにする
		m_ImmediateContext->OMSetBlendState(m_alphaEnableBlendingState.Get(), blendFactor, 0xffffffff);
		return;
	}

	void DirectX11_GraphicsMng::TurnOffAlphaBlending() 
	{
		float blendFactor[4];

		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;

		//アルファブレンドをOFFにする
		m_ImmediateContext->OMSetBlendState(m_alphaDisableBlendingState.Get(), blendFactor, 0xffffffff);
		return;
	}

	void BeforeRender(float _clearColor[]) 
	{
		DirectX11_GraphicsMng::GetInstance()->ClearRenderTargetView(_clearColor);

		DirectX11_GraphicsMng::GetInstance()->ClearDepthStencilView();

		DirectX11_GraphicsMng::GetInstance()->SetViewPort();
	}

	void AfterRender() 
	{
		DirectX11_GraphicsMng::GetInstance()->Swap();
	}

	void TurnOnZBuffer()
	{
		DirectX11_GraphicsMng::GetInstance()->TurnOnZBuffer();
	}

	void TurnOffZBuffer() 
	{
		DirectX11_GraphicsMng::GetInstance()->TurnOffZBuffer();
	}

	void TurnOnAlphaBlend() 
	{
		DirectX11_GraphicsMng::GetInstance()->TurnOnAlphaBlending();
	}

	void TurnOffAlphaBlend() 
	{
		DirectX11_GraphicsMng::GetInstance()->TurnOffAlphaBlending();
	}
}
