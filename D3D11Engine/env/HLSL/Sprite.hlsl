cbuffer  MatrixBuffer: register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};
cbuffer  MyDefine: register(b1)
{
	uint spriteType; //0只有颜色,1只有纹理，2纹理加颜色
	uint bShow3D;
}

struct VertexInputType
{
	float4 position : SV_Position;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_Position;
	float4 color : COLOR;
	float2 tex : TEXCOORD;
};

PixelInputType VS(VertexInputType input)
{
	PixelInputType output;
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	if(bShow3D)
	{
		output.position = mul(output.position, viewMatrix);
		output.position = mul(output.position, projectionMatrix);
	}

	// Store the input color for the pixel shader to use.
	output.color = input.color;
	output.tex = input.tex;
	return output;
}

Texture2D shaderTexture: register(t0);
SamplerState SampleType: register(s0);
float4 PS(PixelInputType input) : SV_TARGET
{
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	float4 textureColor =  input.color;
	if(spriteType == 0)
	{
		return textureColor;
	}
	else if(spriteType == 1)
	{
		float4 diffColor = shaderTexture.Sample(SampleType, input.tex);
		return diffColor;
	}
	else if(spriteType == 2)
	{
		float4 diffColor = shaderTexture.Sample(SampleType, input.tex);
		return diffColor * textureColor;
	}
	return textureColor;
}