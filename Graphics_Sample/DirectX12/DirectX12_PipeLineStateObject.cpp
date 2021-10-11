#include <DirectX12/DirectX12_PipeLineStateObject.h>

namespace DirectX12 {

    bool DirectX12_PipeLineState::Init(ID3D12Device* _pDevice)
    {
        HRESULT hr = S_OK;
    
#pragma region ConstantBuffer
        {
            //
            D3D12_DESCRIPTOR_HEAP_DESC constantDesc = {};
    
            constantDesc.NumDescriptors = 1;
            constantDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
            constantDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    
            hr = _pDevice->CreateDescriptorHeap(&constantDesc, IID_PPV_ARGS(&m_constantHeap));
            if(FAILED(hr))
                return false;
        }

        {
            D3D12_HEAP_PROPERTIES constantProp = {};

            constantProp.Type = D3D12_HEAP_TYPE_UPLOAD;
            constantProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            constantProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
            constantProp.CreationNodeMask = 1;
            constantProp.VisibleNodeMask = 1;

            D3D12_RESOURCE_DESC constantDesc = {};

            constantDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            constantDesc.Alignment = 0;
            constantDesc.Width = 256;
            constantDesc.Height = 0;
            constantDesc.DepthOrArraySize = 1;
            constantDesc.MipLevels = 1;
            constantDesc.Format = DXGI_FORMAT_UNKNOWN;
            constantDesc.SampleDesc = { 1, 0 };
            constantDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            constantDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

            hr = _pDevice->CreateCommittedResource(&constantProp, 
                                                   D3D12_HEAP_FLAG_NONE, 
                                                   &constantDesc, 
                                                   D3D12_RESOURCE_STATE_GENERIC_READ, 
                                                   nullptr, 
                                                   IID_PPV_ARGS(&m_constantBuffer));
            if(FAILED(hr))
                return false;
        }

        {
            D3D12_CONSTANT_BUFFER_VIEW_DESC viewDesc = {};

            viewDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
            viewDesc.SizeInBytes = 256;

            _pDevice->CreateConstantBufferView(&viewDesc, m_constantHeap->GetCPUDescriptorHandleForHeapStart());
        }

        m_constantBuffer->Map(0, nullptr, nullptr);

        {
            D3D12_DESCRIPTOR_RANGE range[1];
            D3D12_ROOT_PARAMETER rootParameter[1];

            range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
            range[0].NumDescriptors = 1;
            range[0].BaseShaderRegister = 0;
            range[0].RegisterSpace = 0;
            range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

            rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
            rootParameter[0].DescriptorTable.NumDescriptorRanges = 1;
            rootParameter[0].DescriptorTable.pDescriptorRanges = range;
            rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
        
            D3D12_ROOT_SIGNATURE_DESC rootDesc = {};

            rootDesc.NumParameters = _countof(rootParameter);
            rootDesc.pParameters = rootParameter;
            rootDesc.NumStaticSamplers = 0;
            rootDesc.pStaticSamplers = nullptr;
            rootDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

            ID3DBlob* pSignature;

            hr = D3D12SerializeRootSignature(&rootDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &pSignature, nullptr);
            if(FAILED(hr))
                return false;

            hr = _pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
        }
#pragma endregion
    
#pragma region PipeLineState

        {
            D3D12_INPUT_ELEMENT_DESC elementDesc[] = 
            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            };

            D3D12_RASTERIZER_DESC rasterDesc = {};

            rasterDesc.FillMode = D3D12_FILL_MODE_SOLID;
            rasterDesc.CullMode = D3D12_CULL_MODE_BACK;
            rasterDesc.FrontCounterClockwise = false;
            rasterDesc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
            rasterDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
            rasterDesc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
            rasterDesc.DepthClipEnable = true;
            rasterDesc.MultisampleEnable = false;
            rasterDesc.AntialiasedLineEnable = false;
            rasterDesc.ForcedSampleCount = 0;
            rasterDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

            D3D12_BLEND_DESC blendDesc = {};

            blendDesc.AlphaToCoverageEnable = false;
            blendDesc.IndependentBlendEnable = false;
            blendDesc.RenderTarget[0].BlendEnable = false;
            blendDesc.RenderTarget[0].LogicOpEnable = false;
            blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
            blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
            blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
            blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
            blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
            blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
            blendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
            blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

            D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeLineDesc = {};

            pipeLineDesc.InputLayout = { elementDesc, _countof(elementDesc) };
            pipeLineDesc.pRootSignature = m_rootSignature.Get();
            pipeLineDesc.VS = Shader::GetInstance()->GetShaderByte(Shaders::VS);
            pipeLineDesc.PS = Shader::GetInstance()->GetShaderByte(Shaders::PS);
            pipeLineDesc.RasterizerState = rasterDesc;
            pipeLineDesc.BlendState = blendDesc;
            pipeLineDesc.DepthStencilState.DepthEnable = FALSE;
            pipeLineDesc.DepthStencilState.StencilEnable = FALSE;
            pipeLineDesc.SampleMask = UINT_MAX;
            pipeLineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
            pipeLineDesc.NumRenderTargets = 1;
            pipeLineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
            pipeLineDesc.SampleDesc.Count = 1;

            hr = _pDevice->CreateGraphicsPipelineState(&pipeLineDesc, IID_PPV_ARGS(&m_pipeLineState));
            if(FAILED(hr))
                return false;
        }

#pragma endregion

#pragma region Vertex

        {
            float position[] = 
            {
                 0.0f,  0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
            };

            D3D12_HEAP_PROPERTIES prop = {};

            prop.Type = D3D12_HEAP_TYPE_UPLOAD;
            prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
            prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
            prop.CreationNodeMask = 1;
            prop.VisibleNodeMask = 1;

            D3D12_RESOURCE_DESC desc = {};

            desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
            desc.Alignment = 0;
            desc.Width = sizeof(position);
            desc.Height = 1;
            desc.DepthOrArraySize = 1;
            desc.MipLevels = 1;
            desc.Format = DXGI_FORMAT_UNKNOWN;
            desc.SampleDesc = { 1, 0 };
            desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
            desc.Flags = D3D12_RESOURCE_FLAG_NONE;

            hr = _pDevice->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_vertexBufferPosition));

            uint8_t* p;

            hr = m_vertexBufferPosition->Map(0, nullptr, reinterpret_cast<void**>(&p));

            memcpy(p, position, sizeof(position));

            m_vertexBufferPosition->Unmap(0, nullptr);

            //
            m_vertexBufferView.BufferLocation = m_vertexBufferPosition->GetGPUVirtualAddress();
            m_vertexBufferView.SizeInBytes = sizeof(position);
            m_vertexBufferView.StrideInBytes = sizeof(float) * 3;

            //D3D12_VERTEX_BUFFER_VIEW views[] = { m_vertexBufferView, /*m_View*/ };

            //_pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            //_pCommandList->IASetVertexBuffers(0, _countof(views), views);

            //_pCommandList->DrawInstanced(3, 1, 0, 0);
        }

#pragma endregion


        return true;
    }

    void DirectX12_PipeLineState::SetRootSignature(ID3D12GraphicsCommandList* _pCommandList)
    {
        _pCommandList->SetGraphicsRootSignature(m_rootSignature.Get());

        _pCommandList->SetDescriptorHeaps(1, m_constantHeap.GetAddressOf());

        _pCommandList->SetGraphicsRootDescriptorTable(0, m_constantHeap->GetGPUDescriptorHandleForHeapStart());
    }
}
