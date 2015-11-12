Texture2D texDiffuse : register(t0);
SamplerState textureSampler : register(s0);

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer MeshBuffer : register(b0)
{
	matrix LocalToProjected4x4;
	matrix LocalToWorld4x4;
	matrix WorldToView4x4;
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
	uint fragment3 : SV_Target2;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
V2P VS(A2V vertex)
{
	V2P result;

	float4 wp = mul(vertex.pos, LocalToWorld4x4);

		// set output data
	result.pos = mul(vertex.pos, LocalToProjected4x4);
	result.uv = vertex.uv;
	result.worldNorm = mul(vertex.normal, (float3x3)LocalToWorld4x4);
	result.viewDepth = mul(wp, WorldToView4x4).z;

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
		float viewDepth = pixel.viewDepth / 1000.0f;

	float3 diffuse = bTextured > 0 ? texDiffuse.Sample(textureSampler, float2(1, 1) - pixel.uv).rgb : DiffuseColor;
		float edge = coverage != 0xf;

	result.fragment1 = float4(worldNormal, viewDepth);
	result.fragment2 = float4(diffuse, edge);
	result.fragment3 = coverage;

	return result;
}