cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CameraVS : register(b1)
{
	matrix cCameraRot;
	float3 cFrustumSize;
	float4 cGBufferOffsets;
}

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
	float4 ScreenPosition : TEXCOORD0;
	float3 oFarRay:TEXCOORD1;
};


float3 GetFarRay(float4 clipPos)
{
	float3 viewRay = float3(
		clipPos.x / clipPos.w * cFrustumSize.x,
		clipPos.y / clipPos.w * cFrustumSize.y,
		cFrustumSize.z);

	return mul(float4(viewRay,1.0f), cCameraRot).xyz;
}

float4 GetScreenPos(float4 clipPos)
{
	return float4(
		clipPos.x * cGBufferOffsets.z + cGBufferOffsets.x * clipPos.w,
		-clipPos.y * cGBufferOffsets.w + cGBufferOffsets.y * clipPos.w,
		0.0,
		clipPos.w);
}



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
	output.ScreenPosition = GetScreenPos(output.position);
	output.oFarRay = GetFarRay(output.position) * output.position.w;
	return output;
}

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
SamplerState SampleTypePoint : register(s0);
SamplerState SampleTypePoint1 : register(s1);

cbuffer LightBuffer
{
	float4 diffuseColor;
	float4 lightPosition;
};

float4 PS(PixelInputType input) : SV_TARGET
{
	float4 colors;
	float4 normals;

	
	// Sample the colors from the color render texture using the point sampler at this texture coordinate location.
	colors = colorTexture.Sample(SampleTypePoint, input.ScreenPosition.xy / input.ScreenPosition.w);
	// Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
	float4 normalData = normalTexture.Sample(SampleTypePoint1, input.ScreenPosition.xy / input.ScreenPosition.w);
	normals.xyz = 2.0f * normalData.xyz - 1.0f;
	float depth = normalData.w;
	float3 worldPos = input.oFarRay * depth / input.ScreenPosition.w;
	float4 projWorldPos = float4(worldPos, 1.0);
	float3 lightPos = lightPosition.xyz - projWorldPos.xyz;
	lightPos = normalize(lightPos);
	float lightIntensity1 = saturate(dot(normals.xyz, lightPos));

	float4 color1 = diffuseColor* lightIntensity1;
	float4 color = saturate(color1) * colors;
	return color;
}
