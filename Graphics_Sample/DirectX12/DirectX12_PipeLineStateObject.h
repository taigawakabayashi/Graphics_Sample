#pragma once
#ifndef PSO_H
#define PSO_H

#include <d3d12.h>
#include <wrl/client.h>

#include "Shader.h"

namespace DirectX12 
{
	using Microsoft::WRL::ComPtr;
	
	class DirectX12_PipeLineState 
	{
	public:

		bool Init(ID3D12Device* _pDevice);

		void SetPipelineState(ID3D12GraphicsCommandList* _pCommandList);

		ID3D12PipelineState* GetPipelineState(){ return m_pipeLineState.Get(); }

	private:

		ComPtr<ID3D12RootSignature>         m_rootSignature = nullptr;
		ComPtr<ID3D12PipelineState>         m_pipeLineState = nullptr;
	};
}
#endif // !PSO_H
