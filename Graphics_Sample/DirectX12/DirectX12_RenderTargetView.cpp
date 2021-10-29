#include "DirectX12/DirectX12_RenderTargetView.h"
#include "GHI/GHI_Device.h"
#include "GHI/GHI_SwapChain.h"

namespace DirectX12 
{
	void DX12_RenderTaergetView::Create(GHI::GHI_Device* _pDevice, GHI::GHI_SwapChain* _pSwapChain)
	{
		ID3D12Device* pDevice = reinterpret_cast<ID3D12Device*>(_pDevice->Get());

		// DescriptorHeapの初期設定
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
		ZeroMemory(&heapDesc, sizeof(heapDesc));

		heapDesc.NumDescriptors = 2;                        // バックバッファの数
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;     // レンダーターゲットビューのためのヒープ
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;   // デフォルト
		heapDesc.NodeMask = 0;                              // デフォルト

		// DescriptorHeapの作成
		pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_rtvDescriptorHeap));

		m_rtvDescriptorHeap->SetName(L"SwapChain_Heap");

		// RenderTargetViewのオフセットを取得
		m_rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		// Heap内の開始アドレスを取得
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		IDXGISwapChain3* swapChain = reinterpret_cast<IDXGISwapChain3*>(_pSwapChain->Get());

		// バックバッファの数だけRTVを作成
		for (int i = 0; i < 2; ++i)
		{
			// バックバッファを取得
			swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargetView[i]));

			// バックバッファをもとにRenderTargetViewを作成
			pDevice->CreateRenderTargetView(m_renderTargetView[i], nullptr, handle);

			// 次のアドレスに以降
			handle.ptr += m_rtvDescriptorSize;
		}
	}

	SIZE_T DX12_RenderTaergetView::GetDescriptorHandle(uint32_t _index)
	{
		SIZE_T temp = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;

		temp += (_index * m_rtvDescriptorSize);

		return temp;
	}
}
