
struct FxaaVS_Output {
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

FxaaVS_Output VS(uint id : SV_VertexID) {
	FxaaVS_Output Output;
	Output.Tex = float2((id << 1) & 2, id & 2);
	Output.Pos = float4(Output.Tex * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
	return Output;
}

Texture2D colorMap: register(t0);
SamplerState SampleType: register(s0);
Texture2D lightMap : register(t1);
SamplerState SampleType1: register(s1);

float4 PS(FxaaVS_Output input) : SV_TARGET{
	float4 diffuseColor = colorMap.Sample(SampleType, input.Tex);
	float4 light = lightMap.Sample(SampleType1, input.Tex);
	float3 diffuseLight = light.rgb;
	float specularLight = light.a;
	return float4((diffuseColor.rgb * diffuseLight + specularLight), 1);

}


