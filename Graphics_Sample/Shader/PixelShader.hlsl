//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

Texture2D	g_Tex : register(t0);				// テクスチャ
SamplerState g_SamplerLinear : register(s0);	// サンプラー

struct VERTEX_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

float4 main(VERTEX_OUT input) : SV_Target
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);

	//input.color.w = alpha;

	// R, G, B, A
	//return float4(1.0f,0.0f,0.0f,1.0f);

	// 暗いフィルター
//	input.color.r = input.color.r * 0.5f;
//	input.color.g = input.color.g * 0.5f;
//	input.color.b = input.color.b * 0.5f;

	// モノクロ化（グレースケール）
   /* input.color = texcol;
	float monoColor = input.color.r * 0.299f + input.color.g * 0.587f + input.color.b * 0.114f;
	input.color.r = monoColor;
	input.color.g = monoColor;
	input.color.b = monoColor;*/
    //input.color = input.color;

    //input.color = saturate(dot(float4(1, 1, -1, 0), input.normal) * float4(1, 1, 1, 1) * input.color);

	return texcol * color;
}
