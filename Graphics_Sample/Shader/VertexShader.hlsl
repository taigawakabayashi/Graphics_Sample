//--------------------------------------------------------------------------------------
// Vertex Shader　（頂点シェーダー）
//--------------------------------------------------------------------------------------
cbuffer WorldMatrixBuffer : register(b0)
{
	matrix World;
}

cbuffer CameraMatrixBuffer : register(b1)
{
	matrix View;
	matrix Projection;
}

struct VERTEX_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct VERTEX_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

VERTEX_OUT main(VERTEX_IN input)
{
	VERTEX_OUT output;

	output.Pos = float4(input.Pos, 1.0f);
	
	output.Pos = mul(output.Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	
	output.Tex = input.Tex;
	
	return output;
}
