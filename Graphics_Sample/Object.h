#pragma once
#ifndef OBJ_H
#define OBJ_H
#include "DirectX11/DirectX11_GraphicsManager.h"
#include "DirectX12/DirectX12_GraphicsManager.h"
#include "Shader.h"

using Microsoft::WRL::ComPtr;

class Object 
{
public:

	bool Init();
	void Input(uint64_t){}
	void Update(uint64_t);
	void Draw(uint64_t);
	void Uninit();

	void SetSrv(ID3D11ShaderResourceView* _srv){ m_texSrv = _srv; }

private:
	
	Vector3 m_pos = Vector3::zero();
	Vector3 m_scale = Vector3::one();
	Vector3 m_angle = Vector3::zero();

	struct Vertex 
	{
		Vector3 Pos;
		Vector2 UV;
	};

	struct Index
	{
		uint32_t idx[3];
	};

	uint32_t m_numVertex = 0;
	uint32_t m_numIndex = 0;

	XMMATRIX m_worldMtx = XMMatrixIdentity();

	ComPtr<ID3D11Buffer> m_vertexBuffer;      // 頂点バッファ
	ComPtr<ID3D11Buffer> m_constantBuffer;    // 定数バッファ
	ComPtr<ID3D11Buffer> m_indexBuffer;       // インデックスバッファ

	ComPtr<ID3D11ShaderResourceView> m_texSrv;
};

class Object_DirectX12 
{
public:

	bool Init();
	void Input(uint64_t) {}
	void Update(uint64_t);
	void Draw(uint64_t);
	void Uninit();

private:

	Vector3 m_pos = Vector3::zero();
	Vector3 m_scale = Vector3::one();
	Vector3 m_angle = Vector3::zero();

	struct Vertex
	{
		Vector3 Pos;
		Vector2 UV;
	};

	struct Index
	{
		uint16_t idx[3];
	};

	uint32_t m_numVertex = 0;
	uint32_t m_numIndex = 0;
	uint32_t m_constantBufferIndex = 0;

	XMMATRIX m_worldMtx = XMMatrixIdentity();
	XMMATRIX m_viewMtx = XMMatrixIdentity();
	XMMATRIX m_projectionMtx = XMMatrixIdentity();

	XMMATRIX* m_constantBufferMatrix[2] = { nullptr, nullptr };

	ComPtr<ID3D12Resource>              m_constantBuffer[2] = { nullptr, nullptr };
	ComPtr<ID3D12Resource>              m_vertexBuffer = nullptr;
	ComPtr<ID3D12Resource>              m_indexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW            m_vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW             m_indexBufferView;
};

#endif // !OBJ_H
