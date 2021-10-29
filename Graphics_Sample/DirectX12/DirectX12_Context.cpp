#include "DirectX12_Context.h"

void DirectX12::DX12_CommandBuffer::Init(GHI::GHI_Device* _pDevice)
{
	ID3D12Device* tempDevice = reinterpret_cast<ID3D12Device*>(_pDevice->Get());

	// キューとアロケータのTypeを合わせる
	D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	// コマンドアロケータの作成
	tempDevice->CreateCommandAllocator(type, IID_PPV_ARGS(&m_commandAllocator));

	// コマンドリストの作成
	HRESULT hr = tempDevice->CreateCommandList(0, type, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));

	if (SUCCEEDED(hr))
	{
		// 初期化時には一旦Closeする
		m_commandList->Close();
	}
}

void DirectX12::DX12_CommandBuffer::ResetCommand()
{
	m_commandAllocator->Reset();

	m_commandList->Reset(m_commandAllocator, nullptr);
}

void DirectX12::DX12_CommandBuffer::ClearRenderTargetView(GHI::GHI_SwapChain* _swapChain, const float _clearColor[])
{
	_swapChain->UpdateBackBufferIndex();

	ID3D12Resource* tempRTV = reinterpret_cast<ID3D12Resource*>(_swapChain->GetCurrentRTV());

	// バリア初期設定
	D3D12_RESOURCE_BARRIER barrier;

	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // Resourceの状態遷移に対してバリアを設定
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // 特に設定しなければこれでいい
	barrier.Transition.pResource = tempRTV;										// バリアを張るResourceを設定
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;              // 状態遷移前のState
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;         // 状態遷移後のState
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // どのサブリソースに対してバリアを張るか

	// バリアを設定
	m_commandList->ResourceBarrier(1, &barrier);

	D3D12_CPU_DESCRIPTOR_HANDLE tempHandle;
	SIZE_T temp = _swapChain->GetDescriptorHandle();

	tempHandle.ptr = temp;

	m_commandList->ClearRenderTargetView(tempHandle, _clearColor, 0, nullptr);
}

void DirectX12::DX12_CommandBuffer::SetRenderTargetView(GHI::GHI_SwapChain* _swapChain, GHI::GHI_DepthStencilView* _depthStencilView)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	rtvHandle.ptr = _swapChain->GetDescriptorHandle();

	if (_depthStencilView != nullptr) 
	{
		//D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;

	}
	else {

		m_commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
	}
}

void DirectX12::DX12_CommandBuffer::SetViewPorrt(GHI::GHI_ViewPort* _viewPort)
{
	m_commandList->RSSetViewports(1, reinterpret_cast<D3D12_VIEWPORT*>(_viewPort->Get()));
}

void DirectX12::DX12_CommandBuffer::SetIABuffer(BufferType _bufferType, GHI::GHI_Buffer* _pBuffer)
{
	switch (_bufferType)
	{
	case BufferType::VERTEX:
	{
		D3D12_VERTEX_BUFFER_VIEW tempView{};

		ID3D12Resource* tempBuffer = reinterpret_cast<ID3D12Resource*>(_pBuffer->Get());

		tempView.BufferLocation = tempBuffer->GetGPUVirtualAddress();
		tempView.StrideInBytes = _pBuffer->GetBufferInfo()->m_stride;
		tempView.SizeInBytes = _pBuffer->GetBufferInfo()->m_bufferSize;

		m_commandList->IASetVertexBuffers(0, 1, &tempView);

		break;
	}
	case BufferType::INDEX:
	{
		D3D12_INDEX_BUFFER_VIEW tempView{};

		ID3D12Resource* tempBuffer = reinterpret_cast<ID3D12Resource*>(_pBuffer->Get());

		tempView.BufferLocation = tempBuffer->GetGPUVirtualAddress();
		tempView.Format = static_cast<DXGI_FORMAT>(_pBuffer->GetBufferInfo()->m_format);
		tempView.SizeInBytes = _pBuffer->GetBufferInfo()->m_bufferSize;

		m_commandList->IASetIndexBuffer(&tempView);

		break;
	}
	}
}

void DirectX12::DX12_CommandBuffer::SetConstantBuffer(uint32_t _rootParamerterIndex, GHI::GHI_Buffer* _pBuffer)
{
	ID3D12Resource* tempBuffer = reinterpret_cast<ID3D12Resource*>(_pBuffer->Get());

	m_commandList->SetGraphicsRootConstantBufferView(_rootParamerterIndex, tempBuffer->GetGPUVirtualAddress());
}

void DirectX12::DX12_CommandBuffer::SetPrimitiveTopology(PrimitiveTopology _topology)
{
	m_commandList->IASetPrimitiveTopology(static_cast<D3D12_PRIMITIVE_TOPOLOGY>(_topology));
}

void DirectX12::DX12_CommandBuffer::SetStates(GHI::GHI_PipelineState* _pPipelineState, 
											  BlendType _blendType, 
											  RasterizerType _rasterizerType, 
											  DepthStencilType _depthStencilType, 
											  SamplerType _samplerType)
{
	uint32_t hash = static_cast<uint32_t>(_blendType) | static_cast<uint32_t>(_rasterizerType) << 4 | static_cast<uint32_t>(_depthStencilType) << 8;

	m_commandList->SetGraphicsRootSignature(reinterpret_cast<ID3D12RootSignature*>(_pPipelineState->GetRootSignature(hash)));
	m_commandList->SetPipelineState(reinterpret_cast<ID3D12PipelineState*>(_pPipelineState->Get(hash)));
}

void DirectX12::DX12_CommandBuffer::DrawInstanced(uint32_t _numVertexPerInstance, 
												  uint32_t _numInstance, 
												  uint32_t _startVertexLocation, 
												  uint32_t _startInstanceLocation)
{
	m_commandList->DrawInstanced(_numVertexPerInstance, _numInstance, _startVertexLocation, _startInstanceLocation);
}

void DirectX12::DX12_CommandBuffer::DrawIndexedInstanced(uint32_t _numIndexPerInstance, 
														 uint32_t _numInstance, 
														 uint32_t _startIndexLocation, 
														 uint32_t _baseVertexLocation, 
														 uint32_t _startInstanceLocation)
{
	m_commandList->DrawIndexedInstanced(_numIndexPerInstance,
										_numInstance,
										_startIndexLocation,
										_baseVertexLocation,
										_startInstanceLocation);
}

void DirectX12::DX12_CommandBuffer::FinishCommand(GHI::GHI_SwapChain* _swapChain)
{
	ID3D12Resource* tempRTV = reinterpret_cast<ID3D12Resource*>(_swapChain->GetCurrentRTV());

	// バリア初期設定 
	D3D12_RESOURCE_BARRIER barrier;

	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // Resourceの状態遷移に対してバリアを設定
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // 特に設定しなければこれでいい
	barrier.Transition.pResource = tempRTV;										// バリアを張るResourceを設定
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;        // 状態遷移前のState
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;               // 状態遷移後のState
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // どのサブリソースに対してバリアを張るか

	// バリアを設定
	m_commandList->ResourceBarrier(1, &barrier);

	m_commandList->Close();
}

void DirectX12::DX12_CommandQueue::CreateFence(GHI::GHI_Device* _pDevice)
{
	ID3D12Device* tempDevice = reinterpret_cast<ID3D12Device*>(_pDevice->Get());

	// コマンドキュー用のフェンスイベント
	m_fenceEvent = CreateEvent(nullptr, FALSE, false, nullptr);

	// コマンドキュー用のフェンスを作成
	tempDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
}

void DirectX12::DX12_CommandQueue::CreateCommandBuffer(GHI::GHI_Device* _pDevice)
{
	std::unique_ptr<GHI::GHI_CommandBuffer> temp = std::make_unique<DX12_CommandBuffer>();

	temp->Init(_pDevice);

	m_commandBuffers.emplace_back(std::move(temp));
}

void DirectX12::DX12_CommandQueue::ExecuteCommandBuffers()
{
	// コマンドをまとめる
	ID3D12CommandList* pCommandList[] = { reinterpret_cast<ID3D12CommandList*>(m_commandBuffers[0]->Get()) };

	// コマンドキューで実行
	m_commandQueue->ExecuteCommandLists(1, pCommandList);

	static uint64_t flame = 0;

	// flameの値になったらイベントをキック
	m_fence->SetEventOnCompletion(flame, m_fenceEvent);

	m_commandQueue->Signal(m_fence, flame);

	// イベントがキックされるまで待機
	WaitForSingleObject(m_fenceEvent, INFINITE);

	++flame;
}

void DirectX12::DX12_CommandQueue::Swap(GHI::GHI_SwapChain* _swapChain)
{
	_swapChain->Present();
}
