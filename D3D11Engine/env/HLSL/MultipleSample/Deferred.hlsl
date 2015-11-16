cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CamerBuffer
{
	float fNear;
	float fFar;
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
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float2 Depth : TEXCOORD1;
	float3 normal : NORMAL;
};

struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
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
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	output.Depth.x = output.position.z;
	output.Depth.y = output.position.w;

	return output;
}

Texture2D shaderTexture;
SamplerState SampleType;


PixelOutputType PS(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	output.color = shaderTexture.Sample(SampleType, input.tex);

	// Invert the light direction for calculations.
	//output the normal, in [0,1] space
	output.normal.xyz = 0.5f * (input.normal + 1.0f);
	//保存深度值
	output.normal.a = input.Depth.y / fFar;
	return output;
}
