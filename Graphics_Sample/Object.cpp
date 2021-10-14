#include "Object.h"

bool DirectX11_Object::Init()
{
	ID3D11Device* device = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetDevice();

	HRESULT hr = S_OK;

	// 頂点構造体の初期化
	Vertex v[] = 
	{
		// 正面
		{Vector3(-0.5f, 0.5f,-0.5f), Vector2(0.0f, 0.0f)},
		{Vector3( 0.5f, 0.5f,-0.5f), Vector2(1.0f, 0.0f)},
		{Vector3(-0.5f,-0.5f,-0.5f), Vector2(0.0f, 1.0f)},
		{Vector3( 0.5f,-0.5f,-0.5f), Vector2(1.0f, 1.0f)},

		// 左側面
		{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
		{Vector3(-0.5f, 0.5f,-0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector2(1.0f, 1.0f)},
		{Vector3(-0.5f,-0.5f,-0.5f), Vector2(0.0f, 1.0f)},

		// 右側面
		{Vector3( 0.5f, 0.5f,-0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
		{Vector3( 0.5f,-0.5f,-0.5f), Vector2(1.0f, 1.0f)},
		{Vector3( 0.5f,-0.5f, 0.5f), Vector2(0.0f, 1.0f)},
		
		// 上面
		{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f, 0.5f,-0.5f), Vector2(1.0f, 1.0f)},
		{Vector3( 0.5f, 0.5f,-0.5f), Vector2(0.0f, 1.0f)},

		// 下面
		{Vector3(-0.5f,-0.5f,-0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f,-0.5f,-0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector2(1.0f, 1.0f)},
		{Vector3( 0.5f,-0.5f, 0.5f), Vector2(0.0f, 1.0f)},

		// 裏面
		{Vector3( 0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f,-0.5f, 0.5f), Vector2(0.0f, 1.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector2(1.0f, 1.0f)},
	};

	m_numVertex = ARRAYSIZE(v);

	// 頂点バッファの作成
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_numVertex;

	D3D11_SUBRESOURCE_DATA vertexInitData;
	ZeroMemory(&vertexInitData, sizeof(vertexInitData));
	vertexInitData.pSysMem = v;

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexInitData, &m_vertexBuffer);

	if(FAILED(hr))
		return false;

	// 定数バッファの作成
	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.ByteWidth = sizeof(XMMATRIX);

	hr = device->CreateBuffer(&constantBufferDesc, nullptr, &m_constantBuffer);

	if(FAILED(hr))
		return false;

	// インデックス構造体の初期化
	Index index[] = 
	{
		// 正面
		{0, 1, 2},
		{3, 2, 1},

		// 左側面
		{4, 5, 6},
		{7, 6, 5},

		// 右側面
		{ 8,  9, 10},
		{11, 10,  9},

		// 上面
		{12, 13, 14},
		{15, 14, 13},

		// 下面
		{16, 17, 18},
		{19, 18, 17},
		
		// 裏面
		{20, 21, 22},
		{23, 22, 21},
	};

	m_numIndex = ARRAYSIZE(index) * 3;

	// インデックスバッファの作成
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.ByteWidth = sizeof(uint32_t) * m_numIndex;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexInitData;
	ZeroMemory(&indexInitData, sizeof(indexInitData));
	indexInitData.pSysMem = index;

	hr = device->CreateBuffer(&indexBufferDesc, &indexInitData, &m_indexBuffer);

	if(FAILED(hr))
		return false;

	m_tex.CreateTexture(&m_texSrv);

	return true;
}

void DirectX11_Object::Update(uint64_t)
{
	m_angle.y += 0.05f;
	//m_angle.x += 0.05f;

	ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

	HRESULT hr = S_OK;

	XMMATRIX mtxTransration = XMMatrixIdentity();
	XMMATRIX mtxRotation = XMMatrixIdentity();
	XMMATRIX mtxScale = XMMatrixIdentity();

	mtxTransration = XMMatrixTranslationFromVector(m_pos);

	mtxRotation = XMMatrixRotationRollPitchYawFromVector(m_angle);

	mtxScale = XMMatrixScalingFromVector(m_scale);

	m_worldMtx = XMMatrixTranspose(mtxScale * mtxRotation * mtxTransration);

	D3D11_MAPPED_SUBRESOURCE data;

	hr = devcontext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	if (SUCCEEDED(hr)) 
	{
		memcpy_s(data.pData, data.RowPitch, &m_worldMtx, sizeof(XMMATRIX));
	}

	devcontext->Unmap(m_constantBuffer.Get(), 0);
}

void DirectX11_Object::Draw(uint64_t)
{
	ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

	// 定数バッファをセット
	devcontext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

	UINT stride[] = { sizeof(Vertex) };
	UINT offset[] = { 0 };
	ID3D11Buffer* pBuf[] = { m_vertexBuffer.Get() };

	// 頂点バッファをセット
	devcontext->IASetVertexBuffers(0, 1, pBuf, stride, offset);

	// インデックスバッファをセット
	devcontext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	// トポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	devcontext->PSSetShaderResources(0, 1, m_texSrv.GetAddressOf());
	
	// 頂点レイアウトをセット
	devcontext->IASetInputLayout(Shader::GetInstance()->GetIL());

	devcontext->VSSetShader(Shader::GetInstance()->GetVS(), nullptr, 0);    // 頂点シェーダーをセット
	devcontext->PSSetShader(Shader::GetInstance()->GetPS(), nullptr, 0);    // ピクセルシェーダーをセット

	devcontext->DrawIndexed(m_numIndex, 0, 0);
}

void DirectX11_Object::Uninit()
{
	
}

bool DirectX12_Object::Init()
{
	ID3D12Device* pDevice = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetDevice();

	HRESULT hr = S_OK;

	// 頂点構造体の初期化
	Vertex v[] =
	{
		// 正面
		{Vector3(-0.5f, 0.5f,-0.5f), Vector2(0.0f, 0.0f)},
		{Vector3( 0.5f, 0.5f,-0.5f), Vector2(1.0f, 0.0f)},
		{Vector3(-0.5f,-0.5f,-0.5f), Vector2(0.0f, 1.0f)},
		{Vector3( 0.5f,-0.5f,-0.5f), Vector2(1.0f, 1.0f)},

		// 左側面
		{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
		{Vector3(-0.5f, 0.5f,-0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector2(1.0f, 1.0f)},
		{Vector3(-0.5f,-0.5f,-0.5f), Vector2(0.0f, 1.0f)},

		// 右側面
		{Vector3(0.5f, 0.5f,-0.5f), Vector2(1.0f, 0.0f)},
		{Vector3(0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(0.5f,-0.5f,-0.5f), Vector2(1.0f, 1.0f)},
		{Vector3(0.5f,-0.5f, 0.5f), Vector2(0.0f, 1.0f)},

		// 上面
		{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f, 0.5f,-0.5f), Vector2(1.0f, 1.0f)},
		{Vector3( 0.5f, 0.5f,-0.5f), Vector2(0.0f, 1.0f)},

		// 下面
		{Vector3(-0.5f,-0.5f,-0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f,-0.5f,-0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector2(1.0f, 1.0f)},
		{Vector3( 0.5f,-0.5f, 0.5f), Vector2(0.0f, 1.0f)},

		// 裏面
		{Vector3( 0.5f, 0.5f, 0.5f), Vector2(0.0f, 0.0f)},
		{Vector3(-0.5f, 0.5f, 0.5f), Vector2(1.0f, 0.0f)},
		{Vector3( 0.5f,-0.5f, 0.5f), Vector2(0.0f, 1.0f)},
		{Vector3(-0.5f,-0.5f, 0.5f), Vector2(1.0f, 1.0f)},
	};

	m_numVertex = ARRAYSIZE(v);

	// 頂点バッファの作成
	D3D12_HEAP_PROPERTIES prop = {};

	prop.Type = D3D12_HEAP_TYPE_UPLOAD;
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	prop.CreationNodeMask = 0;
	prop.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC desc = {};

	desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Alignment = 0;
	desc.Width = 512;
	desc.Height = 1;
	desc.DepthOrArraySize = 1;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_UNKNOWN;
	desc.SampleDesc = { 1, 0 };
	desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	hr = pDevice->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_vertexBuffer));
	if (FAILED(hr))
		return false;

	// 頂点情報を送信
	Vertex* p = nullptr;

	hr = m_vertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&p));
	if (FAILED(hr))
		return false;

	memcpy(p, v, sizeof(Vertex) * m_numVertex);

	m_vertexBuffer->Unmap(0, nullptr);

	// VertexBufferViewを作成
	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.SizeInBytes = sizeof(Vertex) * m_numVertex;
	m_vertexBufferView.StrideInBytes = sizeof(Vertex);

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

		// 一枚目の定数バッファを作成
		hr = pDevice->CreateCommittedResource(&constantProp,
			D3D12_HEAP_FLAG_NONE,
			&constantDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_constantBuffer[0]));
		if (FAILED(hr))
			return false;

		// 二枚目の定数バッファを作成
		hr = pDevice->CreateCommittedResource(&constantProp,
			D3D12_HEAP_FLAG_NONE,
			&constantDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_constantBuffer[1]));
		if (FAILED(hr))
			return false;

		// 最初にMapしておく
		hr = m_constantBuffer[0]->Map(0, nullptr, reinterpret_cast<void**>(&m_constantBufferMatrix[0]));
		if (FAILED(hr))
			return false;

		hr = m_constantBuffer[1]->Map(0, nullptr, reinterpret_cast<void**>(&m_constantBufferMatrix[1]));
		if (FAILED(hr))
			return false;

		// 初期値を代入
		*m_constantBufferMatrix[0] = XMMatrixIdentity();
		 
		*m_constantBufferMatrix[1] = XMMatrixIdentity();
	}

	if (FAILED(hr))
		return false;

	// インデックス構造体の初期化
	Index index[] =
	{
		// 正面
		{0, 1, 2},
		{3, 2, 1},

		// 左側面
		{4, 5, 6},
		{7, 6, 5},

		// 右側面
		{ 8,  9, 10},
		{11, 10,  9},

		// 上面
		{12, 13, 14},
		{15, 14, 13},

		// 下面
		{16, 17, 18},
		{19, 18, 17},

		// 裏面
		{20, 21, 22},
		{23, 22, 21},
	};

	m_numIndex = ARRAYSIZE(index) * 3;

	// インデックスバッファの作成
	D3D12_HEAP_PROPERTIES indexProp = {};

	indexProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	indexProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	indexProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	indexProp.CreationNodeMask = 0;
	indexProp.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC indexDesc = {};

	indexDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	indexDesc.Alignment = 0;
	indexDesc.Width = 256;
	indexDesc.Height = 1;
	indexDesc.DepthOrArraySize = 1;
	indexDesc.MipLevels = 1;
	indexDesc.Format = DXGI_FORMAT_UNKNOWN;
	indexDesc.SampleDesc = { 1, 0 };
	indexDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	indexDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	// インデックスバッファを作成
	hr = pDevice->CreateCommittedResource(&indexProp, D3D12_HEAP_FLAG_NONE, &indexDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_indexBuffer));
	if (FAILED(hr))
		return false;

	Index* data = nullptr;

	// インデックスデータを送信
	hr = m_indexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(hr))
		return false;

	memcpy(data, index, sizeof(Index) * ARRAYSIZE(index));

	m_indexBuffer->Unmap(0, nullptr);

	// IndexBufferViewを作成
	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	m_indexBufferView.SizeInBytes = sizeof(Index) * ARRAYSIZE(index);
	m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;

	m_tex.CreateTexture12();

	return true;
}

void DirectX12_Object::Update(uint64_t)
{
	m_angle.y += 0.05f;
	//m_angle.x += 0.05f;

	XMMATRIX mtxTransration = XMMatrixIdentity();
	XMMATRIX mtxRotation = XMMatrixIdentity();
	XMMATRIX mtxScale = XMMatrixIdentity();

	mtxTransration = XMMatrixTranslationFromVector(m_pos);

	mtxRotation = XMMatrixRotationRollPitchYawFromVector(m_angle);

	mtxScale = XMMatrixScalingFromVector(m_scale);

	m_worldMtx = (mtxScale * mtxRotation * mtxTransration);

	m_worldMtx = XMMatrixTranspose(m_worldMtx);

	// 定数バッファ内を更新
	*m_constantBufferMatrix[m_constantBufferIndex] = m_worldMtx;

	// 更新するバッファと送信するバッファを切り替える
	m_constantBufferIndex = (m_constantBufferIndex + 1) % 2;
}

void DirectX12_Object::Draw(uint64_t)
{
	ID3D12GraphicsCommandList* pCommandList = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetCommandList();

	// 頂点バッファをセット
	D3D12_VERTEX_BUFFER_VIEW vertexViews[] = { m_vertexBufferView };

	pCommandList->IASetVertexBuffers(0, _countof(vertexViews), vertexViews);

	// インデックスバッファをセット
	pCommandList->IASetIndexBuffer(&m_indexBufferView);

	// 定数バッファをセット
	pCommandList->SetGraphicsRootConstantBufferView(0, m_constantBuffer[m_constantBufferIndex]->GetGPUVirtualAddress());

	// トポロジーをセット
	pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// テクスチャのセット
	m_tex.SetTexture(pCommandList);

	// Draw
	pCommandList->DrawIndexedInstanced(m_numIndex, 1, 0, 0, 0);
}

void DirectX12_Object::Uninit()
{
	// Unmap
	m_constantBuffer[0]->Unmap(0, nullptr);
	m_constantBuffer[1]->Unmap(0, nullptr);

	m_constantBufferMatrix[0] = nullptr;
	m_constantBufferMatrix[1] = nullptr;
}
