#pragma once
#ifndef OBJ_H
#define OBJ_H
#include "DirectX11Graphics.h"
#include "Shader.h"

using Microsoft::WRL::ComPtr;

class Object 
{
public:

    bool Init();
    void Input(uint32_t deltaTime){}
    void Update(uint32_t deltaTime);
    void Draw(uint32_t deltaTime);
    void Uninit();

    void SetSrv(ID3D11ShaderResourceView* srv){ m_texSrv = srv; }

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

    uint32_t m_numVertex;
    uint32_t m_numIndex;

    XMMATRIX m_worldMtx;

    ComPtr<ID3D11Buffer> m_vertexBuffer;      // 頂点バッファ
    ComPtr<ID3D11Buffer> m_constantBuffer;    // 定数バッファ
    ComPtr<ID3D11Buffer> m_indexBuffer;       // インデックスバッファ

    ComPtr<ID3D11ShaderResourceView> m_texSrv;
};

#endif // !OBJ_H
