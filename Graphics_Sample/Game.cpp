#include "Game.h"

namespace Render
{
	Renderer* renderer = nullptr;

	bool Init(HWND _hWnd, Vector2Int _size, GraphicsAPI _api)
	{
		switch (_api) 
		{
		case GraphicsAPI::DIRECTX11:

			renderer = new DirectX11_Renderer;

			break;

		case GraphicsAPI::DIRECTX12:

			renderer = new DirectX12_Renderer;

			break;

		case GraphicsAPI::OPENGL:

			renderer = nullptr;

			return false;

		case GraphicsAPI::VULKAN:

			renderer = nullptr;

			return false;

		default:

			return false;
		}

		return renderer->Init(_hWnd, _size);
	}

	void Input(uint64_t) 
	{

	}

	void Update(uint64_t _deltaTime)
	{
		renderer->Update(_deltaTime);
	}

	void Draw(uint64_t _deltaTime)
	{
		float col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		renderer->BeforeRender(col);

		renderer->Draw(_deltaTime);

		renderer->AfterRender();
	}

	void Uninit()
	{
		renderer->Uninit();

		delete renderer;
		renderer = nullptr;
	}

#pragma region DirectX11_Renderer

	bool DirectX11_Renderer::Init(HWND _hWnd, Vector2Int _size)
	{
		HRESULT hr = S_OK;

		bool sts = DirectX11::DirectX11_GraphicsMng::GetInstance()->Init(_hWnd, _size);

		DirectX11::TurnOnZBuffer();
		DirectX11::TurnOnAlphaBlend();

		sts = Shader::GetInstance()->Init();

		ID3D11Device* device = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetDevice();

		m_obj = new DirectX11_Object;

		m_obj->Init();

		D3D11_BUFFER_DESC cameraBufferDesc;
		ZeroMemory(&cameraBufferDesc, sizeof(cameraBufferDesc));

		cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cameraBufferDesc.ByteWidth = sizeof(CameraMatrix);

		hr = device->CreateBuffer(&cameraBufferDesc, nullptr, &m_cameraBuffer);
		if (FAILED(hr))
			return false;

		return sts;
	}

	void DirectX11_Renderer::Update(uint64_t _deltaTime)
	{
		if (_deltaTime >= 0) {

			CameraMatrix cMatrix{};

			cMatrix.view.View(m_eye, m_lookat, m_up).Transpose();
			cMatrix.projection.Perspective(45.0f, 960.0f / 540.0f, 0.1f, 1000.0f).Transpose();

			ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

			D3D11_MAPPED_SUBRESOURCE data;

			devcontext->Map(m_cameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

			memcpy_s(data.pData, data.RowPitch, &cMatrix, sizeof(CameraMatrix));

			devcontext->Unmap(m_cameraBuffer.Get(), 0);

			m_obj->Update(_deltaTime);
		}
	}

	void DirectX11_Renderer::Draw(uint64_t _deltaTime)
	{
		float col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

		devcontext->VSSetConstantBuffers(1, 1, m_cameraBuffer.GetAddressOf());

		m_obj->Draw(_deltaTime);
	}

	void DirectX11_Renderer::Uninit()
	{
		m_obj->Uninit();

		delete m_obj;
		m_obj = nullptr;

		DirectX11::DirectX11_GraphicsMng::GetInstance()->Uninit();
	}

	void DirectX11_Renderer::BeforeRender(float _clearColor[])
	{
		DirectX11::BeforeRender(_clearColor);
	}

	void DirectX11_Renderer::AfterRender()
	{
		DirectX11::AfterRender();
	}

#pragma endregion

#pragma region DirectX12_Renderer

	bool DirectX12_Renderer::Init(HWND _hWnd, Vector2Int _size)
	{
		HRESULT hr = S_OK;

		Shader::GetInstance()->InitDirectX12();

		bool sts = DirectX12::DirectX12_GraphicsMng::GetInstance()->Init(_hWnd, _size);

		ID3D12Device* pDevice = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetDevice();

		m_obj = new DirectX12_Object;

		m_obj->Init();

		// 定数バッファの作成
		{
			// 定数バッファ用のDescriptorを作成
			D3D12_HEAP_PROPERTIES constantProp = {};

			constantProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			constantProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			constantProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			constantProp.CreationNodeMask = 0;
			constantProp.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC constantDesc = {};

			constantDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			constantDesc.Alignment = 0;
			constantDesc.Width = 256;
			constantDesc.Height = 1;
			constantDesc.DepthOrArraySize = 1;
			constantDesc.MipLevels = 1;
			constantDesc.Format = DXGI_FORMAT_UNKNOWN;
			constantDesc.SampleDesc = { 1, 0 };
			constantDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			constantDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

			hr = pDevice->CreateCommittedResource(&constantProp,
				D3D12_HEAP_FLAG_NONE,
				&constantDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_cameraBuffer));
			if (FAILED(hr))
				return false;

			CameraMatrix* data;

			hr = m_cameraBuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));

			data->view.View(m_eye, m_lookat, m_up).Transpose();
			data->projection.Perspective(45.0f, 960.0f / 540.0f, 0.1f, 1000.0f).Transpose();

			m_cameraBuffer->Unmap(0, nullptr);

			data = nullptr;
		}

		return sts;
	}

	void DirectX12_Renderer::Update(uint64_t _deltaTime)
	{
		m_obj->Update(_deltaTime);
	}

	void DirectX12_Renderer::Draw(uint64_t _deltaTime)
	{
		ID3D12GraphicsCommandList* pCommandList = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetCommandList();

		pCommandList->SetGraphicsRootConstantBufferView(1, m_cameraBuffer->GetGPUVirtualAddress());

		m_obj->Draw(_deltaTime);
	}

	void DirectX12_Renderer::Uninit()
	{
		m_obj->Uninit();

		delete m_obj;
		m_obj = nullptr;

		DirectX12::DirectX12_GraphicsMng::GetInstance()->Uninit();

		ID3D12DebugDevice* debug = nullptr;

		ID3D12Device* device = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetDevice();

		device->QueryInterface(&debug);

		debug->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL);

		debug->Release();
		device->Release();
	}

	void DirectX12_Renderer::BeforeRender(float _clearColor[])
	{
		DirectX12::BeforeRender(_clearColor);
	}

	void DirectX12_Renderer::AfterRender()
	{
		DirectX12::AfterRender();
	}

#pragma endregion
}
