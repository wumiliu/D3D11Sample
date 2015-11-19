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
	float4 Color : SV_Target0;
	float4 Normal : SV_Target1;
	float4 Depth : SV_Target2;
};

PixelOutputType PS(FxaaVS_Output input) : SV_TARGET
{
	PixelOutputType output;
	output.Color = 0.0f;
	output.Color.a = 0.0f;
	//output.Color = float4(0, 1, 0, 1);
	//[-1,-1] -->[0,1]    0.5(x+1)
	//when transforming 0.5f into [-1,1], we will get 0.0f
	output.Normal.rgb = 0.5f;
	//no specular power
	output.Normal.a = 0.0f;
	//max depth
	output.Depth = 0.0f;

	return output;
}