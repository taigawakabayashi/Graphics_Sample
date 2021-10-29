#include <DirectX12/DirectX12_PipeLineStateObject.h>

namespace DirectX12 {

	bool DirectX12_PipeLineState::Init(ID3D12Device* _pDevice)
	{
		HRESULT hr = S_OK;
	
#pragma region RootSignature
		{
			D3D12_DESCRIPTOR_RANGE ranges[1]{};

			ranges[0].BaseShaderRegister = 0;
			ranges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
			ranges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			ranges[0].RegisterSpace = 0;
			ranges[0].NumDescriptors = 1;

			// RootSignatureの作成
			D3D12_ROOT_PARAMETER rootParameter[3]{};

			rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			rootParameter[0].Descriptor.ShaderRegister = 0;
			rootParameter[0].Descriptor.RegisterSpace = 0;
			rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

			rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			rootParameter[1].Descriptor.ShaderRegister = 1;
			rootParameter[1].Descriptor.RegisterSpace = 0;
			rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

			rootParameter[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParameter[2].DescriptorTable.NumDescriptorRanges = 1;
			rootParameter[2].DescriptorTable.pDescriptorRanges = ranges;
			rootParameter[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

			// サンプラーステート
			D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
			samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
			samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			samplerDesc.MipLODBias = 0;
			samplerDesc.MaxAnisotropy = 0;
			samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
			samplerDesc.MinLOD = 0.0f;
			samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
			samplerDesc.ShaderRegister = 0;
			samplerDesc.RegisterSpace = 0;
			samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			 
			//
			D3D12_ROOT_SIGNATURE_DESC rootDesc = {};

			rootDesc.NumParameters = _countof(rootParameter);
			rootDesc.pParameters = rootParameter;
			rootDesc.NumStaticSamplers = 1;
			rootDesc.pStaticSamplers = &samplerDesc;
			rootDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			ID3DBlob* pSignature;

			hr = D3D12SerializeRootSignature(&rootDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSignature, nullptr);
			if(FAILED(hr))
				return false;

			hr = _pDevice->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
			if (FAILED(hr))
				return false;
		}
#pragma endregion
	
#pragma region PipeLineState

		{
			// 頂点レイアウトの作成
			D3D12_INPUT_ELEMENT_DESC elementDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			};

			// ラスターステートの設定
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
			rasterDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			// ブレンドステートの設定
			D3D12_BLEND_DESC blendDesc = {};

			blendDesc.AlphaToCoverageEnable = false;
			blendDesc.IndependentBlendEnable = false;
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].LogicOpEnable = false;
			blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_CLEAR;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			// 深度ステンシルステートの設定
			D3D12_DEPTH_STENCIL_DESC depthDesc = {};

			depthDesc.DepthEnable = true;
			depthDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			depthDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			depthDesc.StencilEnable = false;
			depthDesc.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
			depthDesc.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

			depthDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			depthDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeLineDesc = {};

			pipeLineDesc.InputLayout = { elementDesc, _countof(elementDesc) };
			pipeLineDesc.pRootSignature = m_rootSignature.Get();
			pipeLineDesc.VS = Shader::GetInstance()->GetShaderByte(ShadersStage::VS);	// 頂点シェーダーの設定
			pipeLineDesc.PS = Shader::GetInstance()->GetShaderByte(ShadersStage::PS);	// ピクセルシェーダーの設定
			pipeLineDesc.RasterizerState = rasterDesc;
			pipeLineDesc.BlendState = blendDesc;
			pipeLineDesc.DepthStencilState = depthDesc;
			pipeLineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
			pipeLineDesc.SampleMask = UINT_MAX;
			pipeLineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;	// 三角形に設定(描画方法とは別)
			pipeLineDesc.NumRenderTargets = 1;
			pipeLineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			pipeLineDesc.SampleDesc = { 1, 0 };

			hr = _pDevice->CreateGraphicsPipelineState(&pipeLineDesc, IID_PPV_ARGS(&m_pipeLineState));
			if (FAILED(hr))
				return false;
		}

#pragma endregion

		return true;
	}

	void DirectX12_PipeLineState::SetPipelineState(ID3D12GraphicsCommandList* _pCommandList)
	{
		_pCommandList->SetPipelineState(m_pipeLineState.Get());
				
		_pCommandList->SetGraphicsRootSignature(m_rootSignature.Get());
	}
}
