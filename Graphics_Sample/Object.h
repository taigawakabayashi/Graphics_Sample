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
    void Input(uint64_t){}
    void Update(uint64_t);
    void Draw(uint64_t);
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

    uint32_t m_numVertex = 0;
    uint32_t m_numIndex = 0;

    XMMATRIX m_worldMtx = XMMatrixIdentity();

    ComPtr<ID3D11Buffer> m_vertexBuffer;      // ���_�o�b�t�@
    ComPtr<ID3D11Buffer> m_constantBuffer;    // �萔�o�b�t�@
    ComPtr<ID3D11Buffer> m_indexBuffer;       // �C���f�b�N�X�o�b�t�@

    ComPtr<ID3D11ShaderResourceView> m_texSrv;
};

#endif // !OBJ_H