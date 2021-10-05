#include "Game.h"
#include "Object.h"

Object g_obj;

Vector3 Game::m_eye = Vector3(0.0f, 2.0f, -5.0f);
Vector3 Game::m_up = Vector3::up();
Vector3 Game::m_lookat = Vector3::zero();

Microsoft::WRL::ComPtr<ID3D11Buffer> Game::m_cameraBuffer = nullptr;

bool Game::Init(HWND hWnd, Vector2Int size)
{
    bool sts = DirectX11::GraphicsMng::GetInstance()->Init(hWnd, size);

    DirectX11::TurnOnZBuffer();
    DirectX11::TurnOnAlphaBlend();

    sts = Shader::GetInstance()->Init();

    ID3D11Device* device = DirectX11::GraphicsMng::GetInstance()->GetDevice();

    g_obj.Init();

    D3D11_BUFFER_DESC cameraBufferDesc;
    ZeroMemory(&cameraBufferDesc, sizeof(cameraBufferDesc));

    cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cameraBufferDesc.ByteWidth = sizeof(CameraMatrix);

    HRESULT hr = device->CreateBuffer(&cameraBufferDesc, nullptr, &m_cameraBuffer);

    if(FAILED(hr))
        return false;

    return sts;
}

void Game::Input(uint64_t deltaTime)
{
    if (deltaTime > 60) {


    }
}

void Game::Update(uint64_t deltaTime)
{
    if (deltaTime > 0) {
        
        CameraMatrix cMatrix;

        cMatrix.view = XMMatrixLookAtLH(m_eye, m_lookat, m_up);
        cMatrix.projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f);

        cMatrix.view = XMMatrixTranspose(cMatrix.view);
        cMatrix.projection = XMMatrixTranspose(cMatrix.projection);

        ID3D11DeviceContext* devcontext = DirectX11::GraphicsMng::GetInstance()->GetImmediateContext();

        D3D11_MAPPED_SUBRESOURCE data;

        devcontext->Map(m_cameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

        memcpy_s(data.pData, data.RowPitch, &cMatrix, sizeof(CameraMatrix));

        devcontext->Unmap(m_cameraBuffer.Get(), 0);

        g_obj.Update(deltaTime);
    }
}

void Game::Draw(uint64_t deltaTime)
{
    if (deltaTime > 0) {
    
        float col[4] = { 0.0f, 1.0f, 1.0f, 1.0f };

        DirectX11::BeforeRender(col);

        ID3D11DeviceContext* devcontext = DirectX11::GraphicsMng::GetInstance()->GetImmediateContext();

        devcontext->VSSetConstantBuffers(1, 1, m_cameraBuffer.GetAddressOf());

        g_obj.Draw(deltaTime);

        DirectX11::AfterRender();
    }
}

void Game::Uninit()
{
    g_obj.Uninit();

    DirectX11::GraphicsMng::GetInstance()->Uninit();
}
