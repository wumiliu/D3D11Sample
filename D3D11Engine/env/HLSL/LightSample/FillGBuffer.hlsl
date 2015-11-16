
struct PixelInputType
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};
PixelInputType VS(uint id : SV_VertexID) {
	PixelInputType Output;
	Output.Tex = float2((id << 1) & 2, id & 2);
	Output.Pos = float4(Output.Tex * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
	return Output;
}

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
SamplerState SampleTypePoint : register(s0);
SamplerState SampleTypePoint1 : register(s1);


cbuffer LightBuffer
{
	float3 lightDirection;
	float padding;
};

float4 PS(PixelInputType input) : SV_TARGET
{
	float4 colors;
	float4 normals;
	float3 lightDir;
	float lightIntensity;
	float4 outputColor;


	// Sample the colors from the color render texture using the point sampler at this texture coordinate location.
	colors = colorTexture.Sample(SampleTypePoint, input.Tex);

	// Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
	float4 normalData = normalTexture.Sample(SampleTypePoint1, input.Tex);
	normals.xyz = 2.0f * normalData.xyz - 1.0f;
	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(normals.xyz, lightDir));

	// Determine the final amount of diffuse color based on the color of the pixel combined with the light intensity.
	outputColor = saturate(colors * lightIntensity);

	return outputColor;
}