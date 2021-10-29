#include "DirectX11/DirectX11_Device.h"
#include "GHI/GHI_Shader.h"

namespace DirectX11 
{
	GHI::GHI_Shader* DX11_Device::CreateShader(GraphicsShaderDesc* _pDesc) 
	{
		ID3DBlob* temp = nullptr;

#if defined(_DEBUG)
		UINT compile_flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compile_flag = 0;
#endif

		m_shader = std::make_unique<DX11_Shader>();

		if (_pDesc->vertexShader.entryPoint != NULL) {

			ID3D11VertexShader* tempShader = reinterpret_cast<ID3D11VertexShader*>(m_shader->GetVS());
			ID3D11InputLayout* tempInputLayout = reinterpret_cast<ID3D11InputLayout*>(m_shader->GetInputLayout());

			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{"POSITION",    0,  DXGI_FORMAT_R32G32B32_FLOAT,    0,  D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA,    0   },
				{"TEXCOORD",    0,  DXGI_FORMAT_R32G32_FLOAT,       0,  D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA,    0   },
			};

			uint32_t numElements = ARRAYSIZE(layout);

			D3DCompileFromFile(_pDesc->vertexShader.path.c_str(),
				nullptr,
				nullptr,
				_pDesc->vertexShader.entryPoint,
				_pDesc->vertexShader.shaderModel,
				compile_flag,
				0,
				&temp,
				nullptr);

			m_device->CreateVertexShader(temp->GetBufferPointer(), temp->GetBufferSize(), nullptr, &tempShader);

			m_device->CreateInputLayout(layout, numElements, temp->GetBufferPointer(), temp->GetBufferSize(), &tempInputLayout);
		}

		if (_pDesc->hulShader.entryPoint != NULL) {

		}

		if (_pDesc->domainShader.entryPoint != NULL) {

		}

		if (_pDesc->geometryShader.entryPoint != NULL) {

		}

		if (_pDesc->pixelShader.entryPoint != NULL) {

			ID3D11PixelShader* tempShader = reinterpret_cast<ID3D11PixelShader*>(m_shader->GetPS());

			D3DCompileFromFile(_pDesc->pixelShader.path.c_str(),
				nullptr,
				nullptr,
				_pDesc->pixelShader.entryPoint,
				_pDesc->pixelShader.shaderModel,
				compile_flag,
				0,
				&temp,
				nullptr);

			m_device->CreatePixelShader(temp->GetBufferPointer(), temp->GetBufferSize(), nullptr, &tempShader);
		}

		return m_shader.get();
	}

	GHI::GHI_Buffer* DX11_Device::CreateBuffer(BufferType _bufferType, BufferInfo* _pBufferInfo, void* _pInitData)
	{
		GHI::GHI_Buffer* temp = new DX11_Buffer;

		switch (_bufferType)
		{
		case BufferType::VERTEX:
		{
			ID3D11Buffer* tempBuffer = reinterpret_cast<ID3D11Buffer*>(temp->Get());

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.ByteWidth = _pBufferInfo->m_bufferSize;

			D3D11_SUBRESOURCE_DATA initData;
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = _pInitData;

			m_device->CreateBuffer(&bufferDesc, &initData, &tempBuffer);

			temp->SetBufferInfo(_pBufferInfo);

			break;
		}
		case BufferType::INDEX:
		{
			ID3D11Buffer* tempBuffer = reinterpret_cast<ID3D11Buffer*>(temp->Get());

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bufferDesc.ByteWidth = _pBufferInfo->m_bufferSize;

			D3D11_SUBRESOURCE_DATA initData;
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = _pInitData;

			m_device->CreateBuffer(&bufferDesc, &initData, &tempBuffer);

			temp->SetBufferInfo(_pBufferInfo);

			break;
		}
		case BufferType::CONSTANT:
		{
			ID3D11Buffer* tempBuffer = reinterpret_cast<ID3D11Buffer*>(temp->Get());

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.ByteWidth = _pBufferInfo->m_bufferSize;

			D3D11_SUBRESOURCE_DATA initData;
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = _pInitData;

			m_device->CreateBuffer(&bufferDesc, &initData, &tempBuffer);

			temp->SetBufferInfo(_pBufferInfo);

			break;
		}
		case BufferType::STRUCTURED:

			break;
		}

		return temp;
	}

	void DX11_Device::InitStates()
	{
		m_pipelineState = std::make_unique<DX11_PipelineState>();

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

	std::unique_ptr<GHI::GHI_BlendState> DX11_Device::CreateBlendState(BlendType _blendType)
	{
		switch (_blendType)
		{
		case BlendType::ALPHA_ENABLE:
		{
			std::unique_ptr<GHI::GHI_BlendState> temp = std::make_unique<DX11_BlendState>();

			D3D11_BLEND_DESC blendDesc{};

			// ブレンドステート設定(アルファブレンド可)
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

			ID3D11BlendState* tempState = reinterpret_cast<ID3D11BlendState*>(temp->Get());

			m_device->CreateBlendState(&blendDesc, &tempState);

			return std::move(temp);
		}
		case BlendType::ALPHA_DISABLE:
		{
			std::unique_ptr<GHI::GHI_BlendState> temp = std::make_unique<DX11_BlendState>();

			D3D11_BLEND_DESC blendDesc{};

			// ブレンドステート設定(アルファブレンド不可)
			blendDesc.RenderTarget[0].BlendEnable = false;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

			ID3D11BlendState* tempState = reinterpret_cast<ID3D11BlendState*>(temp->Get());

			m_device->CreateBlendState(&blendDesc, &tempState);

			return std::move(temp);
		}
		}

		return nullptr;
	}

	std::unique_ptr<GHI::GHI_RasterizerState> DX11_Device::CreateRasterizerState(RasterizerType _rasterizerType)
	{
		switch (_rasterizerType)
		{
		case RasterizerType::CULL_NONE_FILL_SOLID:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX11_RasterizerState>();

			D3D11_RASTERIZER_DESC rasterDesc{};

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_NONE;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* tempState = reinterpret_cast<ID3D11RasterizerState*>(temp->Get());

			m_device->CreateRasterizerState(&rasterDesc, &tempState);

			return std::move(temp);
		}
		case RasterizerType::CULL_FRONT_FILL_SOLID:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX11_RasterizerState>();

			D3D11_RASTERIZER_DESC rasterDesc{};

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_FRONT;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* tempState = reinterpret_cast<ID3D11RasterizerState*>(temp->Get());

			m_device->CreateRasterizerState(&rasterDesc, &tempState);

			return std::move(temp);
		}
		case RasterizerType::CULL_BACK_FILL_SOLID:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX11_RasterizerState>();

			D3D11_RASTERIZER_DESC rasterDesc{};

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_BACK;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* tempState = reinterpret_cast<ID3D11RasterizerState*>(temp->Get());

			m_device->CreateRasterizerState(&rasterDesc, &tempState);

			return std::move(temp);
		}
		case RasterizerType::CULL_NONE_FILL_WIREFRAME:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX11_RasterizerState>();

			D3D11_RASTERIZER_DESC rasterDesc{};

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_NONE;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* tempState = reinterpret_cast<ID3D11RasterizerState*>(temp->Get());

			m_device->CreateRasterizerState(&rasterDesc, &tempState);

			return std::move(temp);
		}
		case RasterizerType::CULL_FRONT_FILL_WIREFRAME:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX11_RasterizerState>();

			D3D11_RASTERIZER_DESC rasterDesc{};

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_FRONT;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* tempState = reinterpret_cast<ID3D11RasterizerState*>(temp->Get());

			m_device->CreateRasterizerState(&rasterDesc, &tempState);

			return std::move(temp);
		}
		case RasterizerType::CULL_BACK_FILL_WIREFRAME:
		{
			std::unique_ptr<GHI::GHI_RasterizerState> temp = std::make_unique<DX11_RasterizerState>();

			D3D11_RASTERIZER_DESC rasterDesc{};

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_BACK;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ID3D11RasterizerState* tempState = reinterpret_cast<ID3D11RasterizerState*>(temp->Get());

			m_device->CreateRasterizerState(&rasterDesc, &tempState);

			return std::move(temp);
		}
		}

		return nullptr;
	}

	std::unique_ptr<GHI::GHI_DepthStencilState> DX11_Device::CreateDepthStencilState(DepthStencilType _depthStencilType)
	{
		switch (_depthStencilType)
		{
		case DepthStencilType::DEPTH_ENABLE_STENCIL_ENABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX11_DepthStencilState>();

			D3D11_DEPTH_STENCIL_DESC depthDesc{};

			// ステンシルステート作成
			depthDesc.DepthEnable = true;
			depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthDesc.StencilEnable = true;
			depthDesc.StencilReadMask = 0x01;
			depthDesc.StencilWriteMask = 0xFF;

			// 表面の設定
			depthDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// 裏面の設定
			depthDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			ID3D11DepthStencilState* tempState = reinterpret_cast<ID3D11DepthStencilState*>(temp->Get());

			m_device->CreateDepthStencilState(&depthDesc, &tempState);

			return std::move(temp);
		}
		case DepthStencilType::DEPTH_ENABLE_STENCIL_DISABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX11_DepthStencilState>();

			D3D11_DEPTH_STENCIL_DESC depthDesc{};

			// ステンシルステート作成
			depthDesc.DepthEnable = true;
			depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthDesc.StencilEnable = false;
			depthDesc.StencilReadMask = 0x01;
			depthDesc.StencilWriteMask = 0xFF;

			// 表面の設定
			depthDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// 裏面の設定
			depthDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			ID3D11DepthStencilState* tempState = reinterpret_cast<ID3D11DepthStencilState*>(temp->Get());

			m_device->CreateDepthStencilState(&depthDesc, &tempState);

			return std::move(temp);
		}
		case DepthStencilType::DEPTH_DISABLE_STENCIL_ENABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX11_DepthStencilState>();

			D3D11_DEPTH_STENCIL_DESC depthDesc{};

			// ステンシルステート作成
			depthDesc.DepthEnable = false;
			depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthDesc.StencilEnable = true;
			depthDesc.StencilReadMask = 0x01;
			depthDesc.StencilWriteMask = 0xFF;

			// 表面の設定
			depthDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// 裏面の設定
			depthDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			ID3D11DepthStencilState* tempState = reinterpret_cast<ID3D11DepthStencilState*>(temp->Get());

			m_device->CreateDepthStencilState(&depthDesc, &tempState);

			return std::move(temp);
		}
		case DepthStencilType::DEPTH_DISABLE_STENCIL_DISABLE:
		{
			std::unique_ptr<GHI::GHI_DepthStencilState> temp = std::make_unique<DX11_DepthStencilState>();

			D3D11_DEPTH_STENCIL_DESC depthDesc{};

			// ステンシルステート作成
			depthDesc.DepthEnable = false;
			depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthDesc.StencilEnable = false;
			depthDesc.StencilReadMask = 0x01;
			depthDesc.StencilWriteMask = 0xFF;

			// 表面の設定
			depthDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// 裏面の設定
			depthDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			ID3D11DepthStencilState* tempState = reinterpret_cast<ID3D11DepthStencilState*>(temp->Get());

			m_device->CreateDepthStencilState(&depthDesc, &tempState);

			return std::move(temp);
		}
		}

		return nullptr;
	}
}
