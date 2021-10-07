#include "Object.h"
#include "Texture.h"

Texture g_tex;

bool Object::Init()
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

    g_tex.CreateTexture(&m_texSrv);

    return true;
}

void Object::Update(uint64_t)
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

void Object::Draw(uint64_t)
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

void Object::Uninit()
{

}
