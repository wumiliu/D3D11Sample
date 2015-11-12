
cbuffer  MatrixBuffer: register(b0)
{
	matrix MVP;
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
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType VS(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, MVP).xyww;
	output.position.z = output.position.w;
	output.posL = input.position.xyz;
	return output;
}

#define Sample2D(tex, uv) t##tex.Sample(s##tex, uv)
TextureCube tDiffCubeMap : register(t1);
SamplerState sDiffCubeMap : register(s1);

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS(PixelInputType input) : SV_TARGET
{
	float4 textureColor = Sample2D(DiffCubeMap, input.posL);
	return textureColor;
}