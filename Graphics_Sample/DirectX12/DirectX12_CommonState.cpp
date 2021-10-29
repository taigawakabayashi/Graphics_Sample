#include "DirectX12/DirectX12_CommonState.h"
#include "GHI/GHI_Device.h"

namespace DirectX12 
{
    void* DX12_PipelineState::Get(uint32_t hash)
    {
        auto itr = m_pipelineStates.find(hash);

        if (itr == m_pipelineStates.end()) 
        {
            m_pipelineStates[hash] = nullptr;
        }
        else 
        {
            m_pipelineStates[hash]->Release();
        }

        return m_pipelineStates[hash];
    }

    void* DX12_PipelineState::GetRootSignature(uint32_t hash)
    {
        auto itr = m_rootSignature.find(hash);

        if (itr == m_rootSignature.end())
        {
            m_rootSignature[hash] = nullptr;
        }
        else
        {
            m_rootSignature[hash]->Release();
        }

        return m_rootSignature[hash];
    }
}
