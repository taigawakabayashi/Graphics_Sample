//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

//Texture2D	g_Tex : register(t0);				// テクスチャ
//SamplerState g_SamplerLinear : register(s0);	// サンプラー

struct VERTEX_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

float4 main(VERTEX_OUT input) : SV_Target
{
	float4 color = float4(1.0f, 0.0f, 0.0f, 0.5f);
	//float4 color = float4(1.0f, 0.0f, 0.0f, 1.0f);
		
	//float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);

	return /*texcol **/ color;
}
