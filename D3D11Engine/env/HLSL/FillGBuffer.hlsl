Texture2D texDiffuse : register(t0);
SamplerState textureSampler : register(s0);

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer MeshBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer SubMeshBuffer : register(b1)
{
	float3 DiffuseColor;
	int bTextured;
};

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct A2V
{
	float4 pos : SV_Position;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 uv : TEXCOORD;
};

struct V2P
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float3 worldNorm : TEXCOORD1;
	float viewDepth : TEXCOORD2;
};

struct P2F
{
	float4 fragment1 : SV_Target0;
	float4 fragment2 : SV_Target1;
	float4 fragment3 : SV_Target2;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
V2P VS(A2V vertex)
{
	V2P result;

	vertex.pos.w = 1.0f;
	result.pos = mul(vertex.pos, worldMatrix);
	result.pos = mul(result.pos,  viewMatrix);
	result.pos = mul(result.pos, projectionMatrix);

	// set output data
	result.uv = vertex.uv;
	result.worldNorm = mul(vertex.normal, (float3x3)worldMatrix);
	result.viewDepth = result.pos.w;

	return result;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

P2F PS(V2P	pixel,
	uint	coverage : SV_Coverage) : SV_Target
{
	P2F result;

	float3 worldNormal = normalize(pixel.worldNorm);
		//简单的硬编码了，远平面
	float viewDepth = pixel.viewDepth / 1000.0f;

	float3 diffuse = bTextured > 0 ? texDiffuse.Sample(textureSampler, float2(1, 1) - pixel.uv).rgb : DiffuseColor;
		float edge = coverage != 0xf;

	result.fragment1 = float4(worldNormal, viewDepth);
	result.fragment2 = float4(diffuse, edge);
	result.fragment3 = coverage;

	return result;
}