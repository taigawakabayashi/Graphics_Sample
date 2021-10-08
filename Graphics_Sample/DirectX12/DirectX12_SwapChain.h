#pragma once
#ifndef DX12_SWAP_H
#define DX12_SWAP_H

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

#include <Utility/Math.h>

namespace DirectX12 
{
    using Microsoft::WRL::ComPtr;

    class DirectX12_SwapChain 
    {
    public:

        bool CreateSwapChain(ID3D12CommandQueue* _pCommandQueue, HWND _hWnd, Vector2Int _size);

        bool CreateDescriptorHeap(ID3D12Device* _pDevice);

        bool CreateRenderTaergetView(ID3D12Device* _pDevice);

        bool CreateFence(ID3D12Device* _pDevice);

        void SetRenderTargetView(ID3D12GraphicsCommandList* _pCommandList);

        void ClearRenderTargetView(ID3D12GraphicsCommandList* _pCommandList, float _clearColor[]);

        void WaitFenceEvent(ID3D12CommandQueue* _pCommandQueue, ID3D12GraphicsCommandList* _pCommandList);

        void UpdateFrameIndex();

        IDXGISwapChain3* GetSwapChain() { return m_swapChain.Get(); }
        //ID3D12RenderTargetView* GetRenderTargetView() { return m_RenderTargetView.Get(); }

    private:

        ComPtr<IDXGISwapChain3>             m_swapChain = nullptr;
        ComPtr<ID3D12DescriptorHeap>        m_descriptorHeap = nullptr;
        ComPtr<ID3D12Resource>              m_renderTargetView[2] = { nullptr, nullptr };

        ComPtr<ID3D12Fence>                 m_fence = nullptr;
        uint64_t                            m_fenceValue = 0;
        HANDLE                              m_fenceEvent = nullptr;

        uint32_t m_frameIndex = 0;
        uint32_t m_rtvDescriptorSize = 0;
        //ComPtr<ID3D11RenderTargetView>  m_RenderTargetView;
    };
}

#endif // !DX12_SWAP_H
