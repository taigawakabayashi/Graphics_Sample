#include "DirectX12/DirectX12_RenderTargetView.h"
#include "GHI/GHI_Device.h"
#include "GHI/GHI_SwapChain.h"

namespace DirectX12 
{
	void DX12_RenderTaergetView::Create(GHI::GHI_Device* _pDevice, GHI::GHI_SwapChain* _pSwapChain)
	{
		ID3D12Device* pDevice = reinterpret_cast<ID3D12Device*>(_pDevice->Get());

		// DescriptorHeap�̏����ݒ�
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
		ZeroMemory(&heapDesc, sizeof(heapDesc));

		heapDesc.NumDescriptors = 2;                        // �o�b�N�o�b�t�@�̐�
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;     // �����_�[�^�[�Q�b�g�r���[�̂��߂̃q�[�v
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;   // �f�t�H���g
		heapDesc.NodeMask = 0;                              // �f�t�H���g

		// DescriptorHeap�̍쐬
		pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_rtvDescriptorHeap));

		m_rtvDescriptorHeap->SetName(L"SwapChain_Heap");

		// RenderTargetView�̃I�t�Z�b�g���擾
		m_rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		// Heap���̊J�n�A�h���X���擾
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

		IDXGISwapChain3* swapChain = reinterpret_cast<IDXGISwapChain3*>(_pSwapChain->Get());

		// �o�b�N�o�b�t�@�̐�����RTV���쐬
		for (int i = 0; i < 2; ++i)
		{
			// �o�b�N�o�b�t�@���擾
			swapChain->GetBuffer(i, IID_PPV_ARGS(&m_renderTargetView[i]));

			// �o�b�N�o�b�t�@�����Ƃ�RenderTargetView���쐬
			pDevice->CreateRenderTargetView(m_renderTargetView[i], nullptr, handle);

			// ���̃A�h���X�Ɉȍ~
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