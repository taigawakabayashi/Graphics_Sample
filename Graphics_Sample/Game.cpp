#include "Game.h"
#include "Object.h"

namespace Game 
{
    Object g_obj;

    Vector3 g_eye = Vector3(0.0f, 2.0f, -5.0f);
    Vector3 g_up = Vector3::up();
    Vector3 g_lookat = Vector3::zero();

    struct CameraMatrix
    {
        XMMATRIX view;
        XMMATRIX projection;
    };

    static Microsoft::WRL::ComPtr<ID3D11Buffer> g_cameraBuffer = nullptr;

    bool Init(HWND _hWnd, Vector2Int _size)
    {
        bool sts = DirectX11::DirectX11_GraphicsMng::GetInstance()->Init(_hWnd, _size);

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

        HRESULT hr = device->CreateBuffer(&cameraBufferDesc, nullptr, &g_cameraBuffer);

        if (FAILED(hr))
            return false;

        return sts;
    }

    void Input(uint64_t _deltaTime)
    {
        if (_deltaTime >= 0) {


        }
    }

    void Update(uint64_t _deltaTime)
    {
        if (_deltaTime >= 0) {

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
    }

    void Draw(uint64_t _deltaTime)
    {
        if (_deltaTime >= 0) {

            float col[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

            DirectX11::BeforeRender(col);

            ID3D11DeviceContext* devcontext = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetImmediateContext();

            devcontext->VSSetConstantBuffers(1, 1, g_cameraBuffer.GetAddressOf());

            g_obj.Draw(_deltaTime);

            DirectX11::AfterRender();
        }
    }

    void Uninit()
    {
        g_obj.Uninit();

        DirectX11::DirectX11_GraphicsMng::GetInstance()->Uninit();
    }
}
