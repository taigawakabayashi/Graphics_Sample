#pragma once
#ifndef OBJ_H
#define OBJ_H
#include "DirectX11/DirectX11_GraphicsManager.h"
#include "DirectX12/DirectX12_GraphicsManager.h"
#include "Shader.h"
#include "Texture.h"

using Microsoft::WRL::ComPtr;

class Object 
{
public:

	virtual bool Init() = 0;
	virtual void Input(uint64_t) = 0;
	virtual void Update(uint64_t) = 0;
	virtual void Draw(uint64_t) = 0;
	virtual void Uninit() = 0;

	virtual ~Object(){}

protected:

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

	Texture m_tex;
};


class DirectX11_Object : public Object
{
public:

	bool Init() override;
	void Input(uint64_t) override {}
	void Update(uint64_t) override;
	void Draw(uint64_t) override;
	void Uninit() override;

private:

	ComPtr<ID3D11Buffer> m_vertexBuffer;      // 頂点バッファ
	ComPtr<ID3D11Buffer> m_constantBuffer;    // 定数バッファ
	ComPtr<ID3D11Buffer> m_indexBuffer;       // インデックスバッファ

	ComPtr<ID3D11ShaderResourceView> m_texSrv;
};

class DirectX12_Object : public Object
{
public:

	bool Init() override;
	void Input(uint64_t) override {}
	void Update(uint64_t) override;
	void Draw(uint64_t) override;
	void Uninit() override;

private:

	uint32_t m_constantBufferIndex = 0;

	XMMATRIX* m_constantBufferMatrix[2] = { nullptr, nullptr };

	ComPtr<ID3D12Resource>              m_constantBuffer[2] = { nullptr, nullptr };
	ComPtr<ID3D12Resource>              m_vertexBuffer = nullptr;
	ComPtr<ID3D12Resource>              m_indexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW            m_vertexBufferView = {};
	D3D12_INDEX_BUFFER_VIEW             m_indexBufferView = {};
};

#endif // !OBJ_H
