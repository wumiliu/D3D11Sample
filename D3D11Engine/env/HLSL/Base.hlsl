
cbuffer  MatrixBuffer: register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : SV_Position;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_Position;
	float3 posL: POSITION;
	float2 tex : TEXCOORD;
};

PixelInputType VS(VertexInputType input)
{
	PixelInputType output;
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.posL = mul(float4(input.normal, 0.0f), worldMatrix).xyz;

	output.tex = input.tex;
	return output;
}


SamplerState SampleType: register(s0);
Texture2D shaderTexture;
float4 PS(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	textureColor = shaderTexture.Sample(SampleType, input.tex);
	//textureColor = float4(0,1,1,1);
	return textureColor;
}