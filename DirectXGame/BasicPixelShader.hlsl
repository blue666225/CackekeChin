#include "BasicShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float3 light = normalize(float3(1,-1,1)); // 右下奥　向きのライト
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 0.3f;
	float4 texcolor = tex.Sample(smp, input.uv) * color;
	return float4(texcolor.rgb * brightness, texcolor.a);
	//return float4(1, 1, 1, 1);
}