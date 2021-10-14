#include <DirectX11/DirectX11_GraphicsManager.h>
#include <DirectX12/DirectX12_GraphicsManager.h>
#include "Texture.h"

bool Texture::CreateTexture(ID3D11ShaderResourceView** _ppSrv)
{
    ID3D11Device* device = DirectX11::DirectX11_GraphicsMng::GetInstance()->GetDevice();

    uint32_t* Color = new uint32_t[256 * 256];

    for (int x = 0; x < 256; ++x)
    {
        for (int y = 0; y < 256; ++y)
        {
            if (x / 128 != 1) 
            {
                if (y / 128 != 1) 
                {
                    // ABGR
                    Color[x + y * 256] = 0xffff0000;
                }
                else
                {
                    Color[x + y * 256] = 0xffff00ff;
                }
            }
            else 
            {
                if (y / 128 != 1)
                {
                    Color[x + y * 256] = 0xff00ffff;
                }
                else
                {
                    Color[x + y * 256] = 0xff00ff00;
                }
            }

        }
    }

    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));

    textureDesc.Width = 256;
    textureDesc.Height = 256;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DYNAMIC;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData;

    initData.pSysMem = Color;
    initData.SysMemPitch = sizeof(Color[0]) * 256;
    initData.SysMemSlicePitch = sizeof(Color[0]) * 256 * 256;

    HRESULT hr = device->CreateTexture2D(&textureDesc, &initData, &m_texture);

    if(FAILED(hr))
        return false;

    delete[] Color;
    Color = nullptr;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));

    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Format = textureDesc.Format;
    srvDesc.Texture2D.MipLevels = textureDesc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;

    hr = device->CreateShaderResourceView(m_texture.Get(), &srvDesc, _ppSrv);

    if(FAILED(hr))
        return false;

    return true;
}

bool Texture::CreateTexture12()
{
    HRESULT hr = S_OK;

    ID3D12Device* pDevice = DirectX12::DirectX12_GraphicsMng::GetInstance()->GetDevice();

    uint32_t* Color = new uint32_t[256 * 256];

    for (int x = 0; x < 256; ++x)
    {
        for (int y = 0; y < 256; ++y)
        {
            if (x / 128 != 1)
            {
                if (y / 128 != 1)
                {
                    // ABGR
                    Color[x + y * 256] = 0xffff0000;
                }
                else
                {
                    Color[x + y * 256] = 0xffff00ff;
                }
            }
            else
            {
                if (y / 128 != 1)
                {
                    Color[x + y * 256] = 0xff00ffff;
                }
                else
                {
                    Color[x + y * 256] = 0xff00ff00;
                }
            }

        }
    }

    //テクスチャ用のデスクリプタヒープの作成
    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{};
    srvHeapDesc.NumDescriptors = 1;
    srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    srvHeapDesc.NodeMask = 0;
    hr = pDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_texSrvDescriptorHeap));
    if (FAILED(hr)) {
        return false;
    }

    //テクスチャ用リソースの作成
    D3D12_HEAP_PROPERTIES heapProp{};
    D3D12_RESOURCE_DESC resourceDesc{};

    heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
    heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
    heapProp.CreationNodeMask = 1;
    heapProp.VisibleNodeMask = 1;

    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resourceDesc.Width = 256;
    resourceDesc.Height = 256;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    resourceDesc.SampleDesc = { 1, 0 };
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

    hr = pDevice->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_texture12));
    if (FAILED(hr)) {
        return false;
    }

    // ShaderResourceViewを作成
    D3D12_CPU_DESCRIPTOR_HANDLE srvHandle{};
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

    srvDesc.Format                          = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension                   = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels             = 1;
    srvDesc.Texture2D.MostDetailedMip       = 0;
    srvDesc.Texture2D.PlaneSlice            = 0;
    srvDesc.Texture2D.ResourceMinLODClamp   = 0.0f;
    srvDesc.Shader4ComponentMapping         = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

    srvHandle = m_texSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
    pDevice->CreateShaderResourceView(m_texture12.Get(), &srvDesc, srvHandle);

    D3D12_BOX box = { 0, 0, 0, 256, 256, 1 };

    if (FAILED(m_texture12->WriteToSubresource(0, &box, Color, sizeof(uint32_t) * 256, sizeof(uint32_t) * 256))) 
    {
        return false;
    }

    delete[] Color;
    Color = nullptr;

    return false;
}

void Texture::SetTexture(ID3D12GraphicsCommandList* _pCommandList)
{
    ID3D12DescriptorHeap* pHeaps[] = { m_texSrvDescriptorHeap.Get() };

    _pCommandList->SetDescriptorHeaps(1, pHeaps);

    _pCommandList->SetGraphicsRootDescriptorTable(2, m_texSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
}
