
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
	float3 normal: NORMAL;
	float3 tangent: TANGENT;
	float2 tex : TEXCOORD0;
	float2 Depth : TEXCOORD1;
};

struct PixelOutputType
{
	float4 Color : SV_Target0;
	float4 Normal : SV_Target1;
	float4 Depth : SV_Target2;
};

PixelInputType VS(VertexInputType input)
{
	PixelInputType output;
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.normal = mul(float4(input.normal, 0.0f), worldMatrix).xyz;
	output.tangent = mul(float4(input.tangent, 0.0f), worldMatrix).xyz;


	output.tex = input.tex;
	output.Depth.x = output.position.z;
	output.Depth.y = output.position.w;

	return output;
}

Texture2D shaderTexture: register(t0);
SamplerState SampleType: register(s0);

Texture2D SpecularMap: register(t1);
SamplerState SampleType1: register(s1);

Texture2D NormalMap: register(t2);
SamplerState SampleType2: register(s2);

PixelOutputType PS(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	output.Color = shaderTexture.Sample(SampleType, input.tex);
	float4 specularAttributes = SpecularMap.Sample(SampleType1, input.tex);
	output.Color.a = specularAttributes.r;

	float3 normalFromMap = NormalMap.Sample(SampleType2, input.tex).xyz;
	//tranform to [-1,1]
	normalFromMap = 2.0f * normalFromMap - 1.0f;


	// build orthonormal basis
	float3 N = normalize(input.normal);
	float3 T = normalize(input.tangent - dot(input.tangent, N)*N);
	float3 B = cross(N, T);
	float3x3 TBN = float3x3(T, B, N);
		// Transform from tangent space to world space.
	float3 bumpedNormalW = normalize(mul(normalFromMap, TBN));

	//normalize the result
	normalFromMap = normalize(bumpedNormalW);
	//output the normal, in [0,1] space
	output.Normal.rgb = 0.5f * (normalFromMap + 1.0f);

	//specular Power
	output.Normal.a = specularAttributes.a;

	output.Depth = input.Depth.x / input.Depth.y;
	return output;
}