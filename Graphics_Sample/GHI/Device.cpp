#include "GHI/GHI_Device.h"

#ifdef IS_DIRECTX11

HRESULT Device::CreateDevice(ImmediateContext* _pImmediateContext)
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
		// デバイスの作成
		hr = D3D11CreateDevice(nullptr,
			driverType[driverTypeIndex],
			nullptr,
			createDeviceFlag,
			fetureLevels,
			numFetureLevels,
			D3D11_SDK_VERSION,
			&m_device,
			nullptr,
			_pImmediateContext->GetAddressOf());

		if (SUCCEEDED(hr))
			break;
	}

	return S_OK;
}

HRESULT Device::CreateBuffer(uint32_t _byteWidth, void* _initData, BufferType _bufferType, Buffer* _pBuffer)
{
	D3D11_BUFFER_DESC bufferDesc{};

	bufferDesc.ByteWidth = _byteWidth;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	switch (_bufferType)
	{
	case BufferType::VERTEX:

		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;

	case BufferType::INDEX:
		
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		break;

	case BufferType::CONSTANT:
		
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = _initData;

	HRESULT hr = m_device->CreateBuffer(&bufferDesc, &initData, _pBuffer->GetAddressOf());

	return hr;
}

#elif defined IS_DIRECTX12

HRESULT Device::CreateDevice(ImmediateContext* _pImmediateContext) 
{
	HRESULT hr = S_OK;

#ifdef _DEBUG
	{
		Microsoft::WRL::ComPtr<ID3D12Debug> pDebugController;

		// デバッグインターフェイスを取得
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController));

		if (FAILED(hr))
			return false;

		// デバッグレイヤーを有効化
		pDebugController->EnableDebugLayer();
	}
#endif // _DEBUG

	/*ComPtr<IDXGIFactory> pFactory;

	hr = CreateDXGIFactory(IID_PPV_ARGS(&pFactory));*/

	// デバイスの作成
	hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));

}

#endif 
