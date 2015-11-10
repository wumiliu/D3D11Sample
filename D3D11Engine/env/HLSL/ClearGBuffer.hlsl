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
struct PixelOutputType
{
	float4 color0 : SV_Target0;
	float4 color1 : SV_Target1;
	float4 color2 : SV_Target2;
	float4 color3: SV_Target3;
};
Texture2D shaderTexture;
SamplerState SampleType;

PixelOutputType PS(FxaaVS_Output input) : SV_TARGET
{
	PixelOutputType output;
	float4 textureColor = { 1.0f, 0.0f, 0.0f, 1.0f };
		textureColor = shaderTexture.Sample(SampleType, input.Tex);
	output.color0 = textureColor;
	output.color1 = float4(1, 1, 0, 1);
	output.color2 = float4(1, 1, 0, 1);
	output.color3 = float4(1, 0, 1, 1);
	return output;
}