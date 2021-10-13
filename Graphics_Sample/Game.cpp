#include "Game.h"
#include "Object.h"

namespace Rnderer 
{
	Object g_obj;
	Object_DirectX12 g_obj12;

	Vector3 g_eye = Vector3(0.0f, 2.0f, -5.0f);
	Vector3 g_up = Vector3::up();
	Vector3 g_lookat = Vector3::zero();

	struct CameraMatrix
	{
		XMMATRIX view;
		XMMATRIX projection;
	};

	static Microsoft::WRL::ComPtr<ID3D11Buffer> g_cameraBuffer = nullptr;
	static Microsoft::WRL::ComPtr<ID3D12Resource> g_cameraBuffer12 = nullptr;

	bool Init(HWND _hWnd, Vector2Int _size)
	{
		HRESULT hr = S_OK;

		/*bool sts = DirectX11::DirectX11_GraphicsMng::GetInstance()->Init(_hWnd, _size);

		DirectX11::TurnOnZBuffer();
		DirectX11::TurnOnAlphaBlend();

		sts = Shader::GetInstance()->Init();

		ID3D11Device* device = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetDevice();

		g_obj.Init();

		D3D11_BUFFER_DESC cameraBufferDesc;
		ZeroMemory(&cameraBufferDesc, sizeof(cameraBufferDesc));

		cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cameraBufferDesc.ByteWidth = sizeof(CameraMatrix);

		hr = device->CreateBuffer(&cameraBufferDesc, nullptr, &g_cameraBuffer);
		if (FAILED(hr))
			return false;*/

		Shader::GetInstance()->InitDirectX12();

		bool sts = DirectX12::DirectX12_GraphicsMng::GetInstance()->Init(_hWnd, _size);

		ID3D12Device* pDevice = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetDevice();

		g_obj12.Init();

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
				IID_PPV_ARGS(&g_cameraBuffer12));
			if (FAILED(hr))
				return false;

			CameraMatrix* data;

			hr = g_cameraBuffer12->Map(0, nullptr, reinterpret_cast<void**>(&data));

			data->view = XMMatrixLookAtLH(g_eye, g_lookat, g_up);
			data->projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f);

			data->view = XMMatrixTranspose(data->view);
			data->projection = XMMatrixTranspose(data->projection);

			g_cameraBuffer12->Unmap(0, nullptr);

			data = nullptr;
		}

		return sts;
	}

	void Input(uint64_t _deltaTime)
	{
		if (_deltaTime >= 0) {


		}
	}

	void Update(uint64_t _deltaTime)
	{
		if (_deltaTime < 0) {

			CameraMatrix cMatrix;

			cMatrix.view = XMMatrixLookAtLH(g_eye, g_lookat, g_up);
			cMatrix.projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f);

			cMatrix.view = XMMatrixTranspose(cMatrix.view);
			cMatrix.projection = XMMatrixTranspose(cMatrix.projection);

			ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

			D3D11_MAPPED_SUBRESOURCE data;

			devcontext->Map(g_cameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

			memcpy_s(data.pData, data.RowPitch, &cMatrix, sizeof(CameraMatrix));

			devcontext->Unmap(g_cameraBuffer.Get(), 0);

			g_obj.Update(_deltaTime);
		}
		else 
		{
			g_obj12.Update(_deltaTime);
		}
	}

	void Draw(uint64_t _deltaTime)
	{
		if (_deltaTime < 0) {

			float col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			DirectX11::BeforeRender(col);

			ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

			devcontext->VSSetConstantBuffers(1, 1, g_cameraBuffer.GetAddressOf());

			g_obj.Draw(_deltaTime);

			DirectX11::AfterRender();
		}
		else 
		{
			float col[4] = { 0.0f, 1.0f, 1.0f, 1.0f };

			DirectX12::BeforeRender(col);

			ID3D12GraphicsCommandList* pCommandList = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetCommandList();

			pCommandList->SetGraphicsRootConstantBufferView(1, g_cameraBuffer12->GetGPUVirtualAddress());

			g_obj12.Draw(_deltaTime);

			DirectX12::AfterRender();
		}
	}

	void Uninit()
	{
		g_obj.Uninit();
		g_obj12.Uninit();

		DirectX12::DirectX12_GraphicsMng::GetInstance()->Uninit();

		ID3D12DebugDevice* debug = nullptr;

		ID3D12Device* device = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetDevice();

		device->QueryInterface(&debug);

		debug->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL);

		debug->Release();
		device->Release();

		//DirectX11::DirectX11_GraphicsMng::GetInstance()->Uninit();
	}
}
