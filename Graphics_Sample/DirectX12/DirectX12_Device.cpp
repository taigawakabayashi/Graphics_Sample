#include "DirectX12/DirectX12_Device.h"
#include "DirectX12/DirectX12_Shader.h"

#include "GHI/GHI_Context.h"

namespace DirectX12 
{
	GHI::GHI_SwapChain* DX12_Device::CreateSwapChain(HWND _hWnd, Vector2 _size,GHI::GHI_CommandQueue* _pCommandQueue)
	{
		GHI::GHI_SwapChain* tempChain = new DX12_SwapChain;

		ID3D12CommandQueue* tempQueue = reinterpret_cast<ID3D12CommandQueue*>(_pCommandQueue->Get());

		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.Width = static_cast<UINT>(_size.x);
		desc.Height = static_cast<UINT>(_size.y);
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Stereo = false;                                // フルスクリーン指定
		desc.SampleDesc = DXGI_SAMPLE_DESC{ 1,0 };
		desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;            // バッファ識別
		desc.BufferCount = 2;								// バックバッファ数
		desc.Scaling = DXGI_SCALING_STRETCH;                // バックバッファのスケーリング指定
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;    // スワップ時のバッファの扱い
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;        // アルファモード??
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;// 動作オプション (フルスクリーン切り替え可)

		// スワップチェインの初期設定
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = static_cast<UINT>(_size.x);
		swapChainDesc.BufferDesc.Height = static_cast<UINT>(_size.y);
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = _hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Windowed = true;

		IDXGIFactory4* pFactory = nullptr;

		IDXGISwapChain1* pTempSwap = nullptr;

		CreateDXGIFactory1(IID_PPV_ARGS(&pFactory));

		// スワップチェインの作成
		pFactory->CreateSwapChainForHwnd(
			tempQueue,
			_hWnd,
			&desc,
			nullptr,
			nullptr,
			&pTempSwap);

		// GetCurrentBackBufferIndexを使うためにIDXGISwapChain3にする
		pTempSwap->QueryInterface(IID_PPV_ARGS(tempChain->GetPP()));

		// 現在のバックバッファのインデックスを取得
		tempChain->UpdateBackBufferIndex();

		// 解放処理
		pFactory->Release();
		pFactory = nullptr;

		pTempSwap->Release();
		pTempSwap = nullptr;

		return tempChain;
	}

	GHI::GHI_Shader* DX12_Device::CreateShader(GraphicsShaderDesc* _pDesc)
	{
		ID3DBlob* temp = nullptr;

#if defined(_DEBUG)
		UINT compile_flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compile_flag = 0;
#endif

		m_shader = std::make_unique<DX12_Shader>();

		if (_pDesc->vertexShader.entryPoint != NULL) {

			D3D12_INPUT_ELEMENT_DESC layout[] =
			{
				{"POSITION",    0,  DXGI_FORMAT_R32G32B32_FLOAT,    0,  D3D11_APPEND_ALIGNED_ELEMENT,   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,    0   },
				{"TEXCOORD",    0,  DXGI_FORMAT_R32G32_FLOAT,       0,  D3D11_APPEND_ALIGNED_ELEMENT,   D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,    0   },
			};

			uint32_t numElements = ARRAYSIZE(layout);

			D3D12_SHADER_BYTECODE* tempByteCode = reinterpret_cast<D3D12_SHADER_BYTECODE*>(m_shader->GetVS());
			D3D12_INPUT_LAYOUT_DESC* tempInputLayput = reinterpret_cast<D3D12_INPUT_LAYOUT_DESC*>(m_shader->GetInputLayout());

			D3DCompileFromFile(_pDesc->vertexShader.path.c_str(),
				nullptr,
				nullptr, 
				_pDesc->vertexShader.entryPoint, 
				_pDesc->vertexShader.shaderModel, 
				compile_flag, 
				0, 
				&temp, 
				nullptr);

			tempByteCode->BytecodeLength = temp->GetBufferSize();
			tempByteCode->pShaderBytecode = temp->GetBufferPointer();

			tempInputLayput->pInputElementDescs = layout;
			tempInputLayput->NumElements = numElements;
		}

		if (_pDesc->hulShader.entryPoint != NULL) {


		}

		if (_pDesc->domainShader.entryPoint != NULL) {


		}

		if (_pDesc->geometryShader.entryPoint != NULL) {


		}

		if (_pDesc->pixelShader.entryPoint != NULL) {

			D3D12_SHADER_BYTECODE* tempByteCode = reinterpret_cast<D3D12_SHADER_BYTECODE*>(m_shader->GetPS());

			D3DCompileFromFile(_pDesc->pixelShader.path.c_str(),
				nullptr,
				nullptr,
				_pDesc->pixelShader.entryPoint,
				_pDesc->pixelShader.shaderModel,
				compile_flag,
				0,
				&temp,
				nullptr);

			tempByteCode->BytecodeLength = temp->GetBufferSize();
			tempByteCode->pShaderBytecode = temp->GetBufferPointer();
		}

		ID3D12RootSignature* tempRootSignature = reinterpret_cast<ID3D12RootSignature*>(m_shader->Get());

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

		D3D12SerializeRootSignature(&rootDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pSignature, nullptr);

		m_device->CreateRootSignature(0, pSignature->GetBufferPointer(), pSignature->GetBufferSize(), IID_PPV_ARGS(&tempRootSignature));

		return m_shader.get();
		//return new DX12_Shader;
	}

	GHI::GHI_Buffer* DX12_Device::CreateBuffer(BufferType _bufferType, BufferInfo* _pBufferInfo, void* _pInitData)
	{
		GHI::GHI_Buffer* temp = new DX12_Buffer;

		switch (_bufferType)
		{
		case BufferType::VERTEX:
		{
			ID3D12Resource* tempBuffer = reinterpret_cast<ID3D12Resource*>(temp->Get());

			D3D12_HEAP_PROPERTIES prop = {};

			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 0;
			prop.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC desc = {};

			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Alignment = 0;
			desc.Width = _pBufferInfo->m_bufferSize;
			desc.Height = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.SampleDesc = { 1, 0 };
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			desc.Flags = D3D12_RESOURCE_FLAG_NONE;

			m_device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&tempBuffer));
			
			void* p = nullptr;

			tempBuffer->Map(0, nullptr, &p);

			memcpy(p, _pInitData, _pBufferInfo->m_bufferSize);

			tempBuffer->Unmap(0, nullptr);

			temp->SetBufferInfo(_pBufferInfo);

			break;
		}
		case BufferType::INDEX:
		{
			ID3D12Resource* tempBuffer = reinterpret_cast<ID3D12Resource*>(temp->Get());

			D3D12_HEAP_PROPERTIES prop = {};

			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 0;
			prop.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC desc = {};

			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Alignment = 0;
			desc.Width = _pBufferInfo->m_bufferSize;
			desc.Height = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.SampleDesc = { 1, 0 };
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			desc.Flags = D3D12_RESOURCE_FLAG_NONE;

			m_device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&tempBuffer));

			void* p = nullptr;

			tempBuffer->Map(0, nullptr, &p);

			memcpy(p, _pInitData, _pBufferInfo->m_bufferSize);

			tempBuffer->Unmap(0, nullptr);

			temp->SetBufferInfo(_pBufferInfo);

			break;
		}
		case BufferType::CONSTANT:
		{
			ID3D12Resource* tempBuffer = reinterpret_cast<ID3D12Resource*>(temp->Get());

			// バッファのサイズを256の倍数に
			uint32_t size = 256 * ((_pBufferInfo->m_bufferSize / 256) + 1);

			D3D12_HEAP_PROPERTIES prop = {};

			prop.Type = D3D12_HEAP_TYPE_UPLOAD;
			prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			prop.CreationNodeMask = 0;
			prop.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC desc = {};

			desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			desc.Alignment = 0;
			desc.Width = size;
			desc.Height = 1;
			desc.DepthOrArraySize = 1;
			desc.MipLevels = 1;
			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.SampleDesc = { 1, 0 };
			desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			desc.Flags = D3D12_RESOURCE_FLAG_NONE;

			m_device->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&tempBuffer));

			void* p = nullptr;

			tempBuffer->Map(0, nullptr, &p);

			memcpy(p, _pInitData, _pBufferInfo->m_bufferSize);

			tempBuffer->Unmap(0, nullptr);

			temp->SetBufferInfo(_pBufferInfo);

			break;
		}
		case BufferType::STRUCTURED:

			break;
		}

		return temp;
	}

	GHI::GHI_PipelineState* DX12_Device::CreatePipelineState(GHI::GHI_Shader* _pShader, BlendType _blendType, RasterizerType _rasterizerType, DepthStencilType _depthStencilType)
	{
		if (m_pipelineState != nullptr) 
		{
			m_pipelineState = std::make_unique<DX12_PipelineState>();
		}

		D3D12_INPUT_LAYOUT_DESC elementDesc = *(reinterpret_cast<D3D12_INPUT_LAYOUT_DESC*>(_pShader->GetInputLayout()));

		D3D12_SHADER_BYTECODE vertexShaderCode = *(reinterpret_cast<D3D12_SHADER_BYTECODE*>(_pShader->GetVS()));
		D3D12_SHADER_BYTECODE pixelShaderCode = *(reinterpret_cast<D3D12_SHADER_BYTECODE*>(_pShader->GetVS()));

		D3D12_RASTERIZER_DESC rasterDesc = *(reinterpret_cast<D3D12_RASTERIZER_DESC*>(m_pipelineState->GetRasterizerState(_rasterizerType)));
		D3D12_BLEND_DESC blendDesc = *(reinterpret_cast<D3D12_BLEND_DESC*>(m_pipelineState->GetBlendState(_blendType)));
		D3D12_DEPTH_STENCIL_DESC depthDesc = *(reinterpret_cast<D3D12_DEPTH_STENCIL_DESC*>(m_pipelineState->GetDepthStencilState(_depthStencilType)));

		uint32_t hash = static_cast<uint32_t>(_blendType) | static_cast<uint32_t>(_rasterizerType) << 4 | static_cast<uint32_t>(_depthStencilType) << 8;

		ID3D12PipelineState* tempPSO = reinterpret_cast<ID3D12PipelineState*>(m_pipelineState->Get(hash));

		void* tempSignature = m_pipelineState->GetRootSignature(hash);

		tempSignature = _pShader->Get();

		D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeLineDesc = {};

		pipeLineDesc.InputLayout = elementDesc;
		pipeLineDesc.pRootSignature = reinterpret_cast<ID3D12RootSignature*>(_pShader->Get());
		pipeLineDesc.VS = vertexShaderCode;	// 頂点シェーダーの設定
		pipeLineDesc.PS = pixelShaderCode;	// ピクセルシェーダーの設定
		pipeLineDesc.RasterizerState = rasterDesc;
		pipeLineDesc.BlendState = blendDesc;
		pipeLineDesc.DepthStencilState = depthDesc;
		pipeLineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		pipeLineDesc.SampleMask = UINT_MAX;
		pipeLineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;	// 三角形に設定(描画方法とは別)
		pipeLineDesc.NumRenderTargets = 1;
		pipeLineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		pipeLineDesc.SampleDesc = { 1, 0 };

		m_device->CreateGraphicsPipelineState(&pipeLineDesc, IID_PPV_ARGS(&tempPSO));

		return m_pipelineState.get();
	}

	void DX12_Device::InitStates()
	{
		m_pipelineState = std::make_unique<DX12_PipelineState>();

		// BlendState
		{
			std::unique_ptr<GHI::GHI_BlendState> tempBlendState = CreateBlendState(BlendType::ALPHA_ENABLE);

			m_pipelineState->SetBlendState(BlendType::ALPHA_ENABLE, std::move(tempBlendState));

			tempBlendState = CreateBlendState(BlendType::ALPHA_DISABLE);

			m_pipelineState->SetBlendState(BlendType::ALPHA_DISABLE, std::move(tempBlendState));
		}

		// RasterizerState
		{
			std::unique_ptr<GHI::GHI_RasterizerState> tempRasterizeState = CreateRasterizerState(RasterizerType::CULL_NONE_FILL_SOLID);

			m_pipelineState->SetRasterizerState(RasterizerType::CULL_NONE_FILL_SOLID, std::move(tempRasterizeState));

			tempRasterizeState = CreateRasterizerState(RasterizerType::CULL_FRONT_FILL_SOLID);

			m_pipelineState->SetRasterizerState(RasterizerType::CULL_FRONT_FILL_SOLID, std::move(tempRasterizeState));

			tempRasterizeState = CreateRasterizerState(RasterizerType::CULL_BACK_FILL_SOLID);

			m_pipelineState->SetRasterizerState(RasterizerType::CULL_BACK_FILL_SOLID, std::move(tempRasterizeState));

			tempRasterizeState = CreateRasterizerState(RasterizerType::CULL_NONE_FILL_WIREFRAME);

			m_pipelineState->SetRasterizerState(RasterizerType::CULL_NONE_FILL_WIREFRAME, std::move(tempRasterizeState));

			tempRasterizeState = CreateRasterizerState(RasterizerType::CULL_FRONT_FILL_WIREFRAME);

			m_pipelineState->SetRasterizerState(RasterizerType::CULL_FRONT_FILL_WIREFRAME, std::move(tempRasterizeState));

			tempRasterizeState = CreateRasterizerState(RasterizerType::CULL_BACK_FILL_WIREFRAME);

			m_pipelineState->SetRasterizerState(RasterizerType::CULL_BACK_FILL_WIREFRAME, std::move(tempRasterizeState));
		}

		// DepthStencilState
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> tempDepthStencilState = CreateDepthStencilState(DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE);

			m_pipelineState->SetDepthStencilState(DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE, std::move(tempDepthStencilState));

			tempDepthStencilState = CreateDepthStencilState(DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE);

			m_pipelineState->SetDepthStencilState(DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE, std::move(tempDepthStencilState));

			tempDepthStencilState = CreateDepthStencilState(DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE);

			m_pipelineState->SetDepthStencilState(DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE, std::move(tempDepthStencilState));

			tempDepthStencilState = CreateDepthStencilState(DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE);

			m_pipelineState->SetDepthStencilState(DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE, std::move(tempDepthStencilState));
		}
	}

	std::unique_ptr<GHI::GHI_BlendState> DX12_Device::CreateBlendState(BlendType _blendType)
	{
		switch (_blendType)
		{
		case BlendType::ALPHA_ENABLE: 
		{
			std::unique_ptr<GHI::GHI_BlendState> temp = std::make_unique<DX12_BlendState>();

			D3D12_BLEND_DESC* tempDesc = reinterpret_cast<D3D12_BLEND_DESC*>(temp->Get());

			// ブレンドステート設定(アルファブレンド可)
			tempDesc->AlphaToCoverageEnable = false;
			tempDesc->IndependentBlendEnable = false;
			tempDesc->RenderTarget[0].BlendEnable = true;
			tempDesc->RenderTarget[0].LogicOpEnable = false;
			tempDesc->RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
			tempDesc->RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			tempDesc->RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			tempDesc->RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			tempDesc->RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
			tempDesc->RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			tempDesc->RenderTarget[0].LogicOp = D3D12_LOGIC_OP_CLEAR;
			tempDesc->RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			return std::move(temp);
		}
		case BlendType::ALPHA_DISABLE: 
		{
			std::unique_ptr<GHI::GHI_BlendState> temp = std::make_unique<DX12_BlendState>();

			D3D12_BLEND_DESC* tempDesc = reinterpret_cast<D3D12_BLEND_DESC*>(temp->Get());

			// ブレンドステート設定(アルファブレンド可)
			tempDesc->AlphaToCoverageEnable = false;
			tempDesc->IndependentBlendEnable = false;
			tempDesc->RenderTarget[0].BlendEnable = false;
			tempDesc->RenderTarget[0].LogicOpEnable = false;
			tempDesc->RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
			tempDesc->RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
			tempDesc->RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
			tempDesc->RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
			tempDesc->RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
			tempDesc->RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
			tempDesc->RenderTarget[0].LogicOp = D3D12_LOGIC_OP_CLEAR;
			tempDesc->RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			return std::move(temp);
		}
		}

		return nullptr;
	}

	std::unique_ptr<GHI::GHI_RasterizerState> DX12_Device::CreateRasterizerState(RasterizerType _rasterizerType)
	{
		switch (_rasterizerType)
		{
		case RasterizerType::CULL_NONE_FILL_SOLID: 
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX12_RasterizerState>();

			D3D12_RASTERIZER_DESC* rasterDesc = reinterpret_cast<D3D12_RASTERIZER_DESC*>(temp->Get());

			rasterDesc->FillMode = D3D12_FILL_MODE_SOLID;
			rasterDesc->CullMode = D3D12_CULL_MODE_NONE;
			rasterDesc->FrontCounterClockwise = false;
			rasterDesc->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			rasterDesc->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterDesc->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterDesc->DepthClipEnable = true;
			rasterDesc->MultisampleEnable = false;
			rasterDesc->AntialiasedLineEnable = false;
			rasterDesc->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			return std::move(temp);
		}
		case RasterizerType::CULL_FRONT_FILL_SOLID:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX12_RasterizerState>();

			D3D12_RASTERIZER_DESC* rasterDesc = reinterpret_cast<D3D12_RASTERIZER_DESC*>(temp->Get());

			rasterDesc->FillMode = D3D12_FILL_MODE_SOLID;
			rasterDesc->CullMode = D3D12_CULL_MODE_FRONT;
			rasterDesc->FrontCounterClockwise = false;
			rasterDesc->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			rasterDesc->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterDesc->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterDesc->DepthClipEnable = true;
			rasterDesc->MultisampleEnable = false;
			rasterDesc->AntialiasedLineEnable = false;
			rasterDesc->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			return std::move(temp);
		}
		case RasterizerType::CULL_BACK_FILL_SOLID:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX12_RasterizerState>();

			D3D12_RASTERIZER_DESC* rasterDesc = reinterpret_cast<D3D12_RASTERIZER_DESC*>(temp->Get());

			rasterDesc->FillMode = D3D12_FILL_MODE_SOLID;
			rasterDesc->CullMode = D3D12_CULL_MODE_BACK;
			rasterDesc->FrontCounterClockwise = false;
			rasterDesc->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			rasterDesc->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterDesc->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterDesc->DepthClipEnable = true;
			rasterDesc->MultisampleEnable = false;
			rasterDesc->AntialiasedLineEnable = false;
			rasterDesc->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			return std::move(temp);
		}
		case RasterizerType::CULL_NONE_FILL_WIREFRAME:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX12_RasterizerState>();

			D3D12_RASTERIZER_DESC* rasterDesc = reinterpret_cast<D3D12_RASTERIZER_DESC*>(temp->Get());

			rasterDesc->FillMode = D3D12_FILL_MODE_WIREFRAME;
			rasterDesc->CullMode = D3D12_CULL_MODE_NONE;
			rasterDesc->FrontCounterClockwise = false;
			rasterDesc->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			rasterDesc->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterDesc->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterDesc->DepthClipEnable = true;
			rasterDesc->MultisampleEnable = false;
			rasterDesc->AntialiasedLineEnable = false;
			rasterDesc->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
			
			return std::move(temp);
		}
		case RasterizerType::CULL_FRONT_FILL_WIREFRAME:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX12_RasterizerState>();

			D3D12_RASTERIZER_DESC* rasterDesc = reinterpret_cast<D3D12_RASTERIZER_DESC*>(temp->Get());

			rasterDesc->FillMode = D3D12_FILL_MODE_WIREFRAME;
			rasterDesc->CullMode = D3D12_CULL_MODE_FRONT;
			rasterDesc->FrontCounterClockwise = false;
			rasterDesc->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			rasterDesc->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterDesc->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterDesc->DepthClipEnable = true;
			rasterDesc->MultisampleEnable = false;
			rasterDesc->AntialiasedLineEnable = false;
			rasterDesc->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			return std::move(temp);
		}
		case RasterizerType::CULL_BACK_FILL_WIREFRAME:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX12_RasterizerState>();

			D3D12_RASTERIZER_DESC* rasterDesc = reinterpret_cast<D3D12_RASTERIZER_DESC*>(temp->Get());

			rasterDesc->FillMode = D3D12_FILL_MODE_WIREFRAME;
			rasterDesc->CullMode = D3D12_CULL_MODE_BACK;
			rasterDesc->FrontCounterClockwise = false;
			rasterDesc->DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
			rasterDesc->DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
			rasterDesc->SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
			rasterDesc->DepthClipEnable = true;
			rasterDesc->MultisampleEnable = false;
			rasterDesc->AntialiasedLineEnable = false;
			rasterDesc->ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

			return std::move(temp);
		}
		}

		return nullptr;
	}

	std::unique_ptr<GHI::GHI_DepthStencilState> DX12_Device::CreateDepthStencilState(DepthStencilType _depthStencilType)
	{
		switch (_depthStencilType)
		{
		case DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX12_DepthStencilState>();

			D3D12_DEPTH_STENCIL_DESC* depthDesc = reinterpret_cast<D3D12_DEPTH_STENCIL_DESC*>(temp->Get());

			// ステンシルステート作成
			depthDesc->DepthEnable = true;
			depthDesc->DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			depthDesc->DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			depthDesc->StencilEnable = true;
			depthDesc->StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
			depthDesc->StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

			// 表面の設定
			depthDesc->FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			// 裏面の設定
			depthDesc->BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			return std::move(temp);
		}
		case DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX12_DepthStencilState>();

			D3D12_DEPTH_STENCIL_DESC* depthDesc = reinterpret_cast<D3D12_DEPTH_STENCIL_DESC*>(temp->Get());

			// ステンシルステート作成
			depthDesc->DepthEnable = true;
			depthDesc->DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			depthDesc->DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			depthDesc->StencilEnable = false;
			depthDesc->StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
			depthDesc->StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

			// 表面の設定
			depthDesc->FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			// 裏面の設定
			depthDesc->BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			return std::move(temp);
		}
		case DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX12_DepthStencilState>();

			D3D12_DEPTH_STENCIL_DESC* depthDesc = reinterpret_cast<D3D12_DEPTH_STENCIL_DESC*>(temp->Get());

			// ステンシルステート作成
			depthDesc->DepthEnable = false;
			depthDesc->DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			depthDesc->DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			depthDesc->StencilEnable = true;
			depthDesc->StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
			depthDesc->StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

			// 表面の設定
			depthDesc->FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			// 裏面の設定
			depthDesc->BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			return std::move(temp);
		}
		case DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX12_DepthStencilState>();

			D3D12_DEPTH_STENCIL_DESC* depthDesc = reinterpret_cast<D3D12_DEPTH_STENCIL_DESC*>(temp->Get());

			// ステンシルステート作成
			depthDesc->DepthEnable = false;
			depthDesc->DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			depthDesc->DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			depthDesc->StencilEnable = false;
			depthDesc->StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
			depthDesc->StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

			// 表面の設定
			depthDesc->FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			// 裏面の設定
			depthDesc->BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_INCR;
			depthDesc->BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			depthDesc->BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			return std::move(temp);
		}
		}

		return nullptr;
	}
}
