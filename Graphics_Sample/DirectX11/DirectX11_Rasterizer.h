#pragma once
#ifndef RASTER_H
#define RASTER_H

#include <d3d11.h>
#include <wrl/client.h>

namespace DirectX11 
{
    using Microsoft::WRL::ComPtr;

    class DirectX11_Rasterizer 
    {
    public:
        
        bool CreateRasterizer(ID3D11Device* _pDevice);

        ID3D11RasterizerState* GetRasterizer(){ return m_rasterState.Get(); }

        void SetRasterizer(ID3D11DeviceContext* _pDeviceContext);

    private:

        ComPtr<ID3D11RasterizerState> m_rasterState;
    };
}
#endif // !RASTER_H
