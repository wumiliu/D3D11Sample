#include "Uniforms.hlsl"
#include "ScreenPos.hlsl"

struct VertexShaderInput
{
	float3 Position : SV_Position;
};

struct VertexShaderOutput
{
	float4 Position : SV_Position;
	float4 ScreenPosition : TEXCOORD0;
	float3 iFarRay:TEXCOORD1;
};

VertexShaderOutput VS(VertexShaderInput input)
{
	VertexShaderOutput output;
	//processing geometry coordinates
	float4 worldPosition = mul(float4(input.Position, 1), World);
		float4 viewPosition = mul(worldPosition, View);
		output.Position = mul(viewPosition, Projection);
	output.ScreenPosition = output.Position;
	output.iFarRay = GetFarRay(output.Position);
	return output;
}


Texture2D colorMap: register(t0);
SamplerState SampleType: register(s0);

Texture2D depthMap: register(t1);
SamplerState SampleType1: register(s1);

Texture2D normalMap: register(t2);
SamplerState SampleType2: register(s2);

float4 PS(VertexShaderOutput input) : SV_TARGET
{
	//obtain screen position
	input.ScreenPosition.xy /= input.ScreenPosition.w;
	float2 texCoord = 0.5f * (float2(input.ScreenPosition.x, -input.ScreenPosition.y) + 1);
		//解压缩法线贴图从 (0,1) ---> (-1,1)
		float4 normalData = normalMap.Sample(SampleType2, texCoord);
		float3 normal = 2.0f * normalData.xyz - 1.0f;

		float specularPower = normalData.a * 255.0f;
	float specularIntensity = colorMap.Sample(SampleType, texCoord).a;

	float depthVal = depthMap.Sample(SampleType1, texCoord).r;

	float3 position = input.iFarRay * depthVal + cCameraPosPS;
		float3 lightVector = lightPosition.xyz - position.xyz;

		//compute attenuation based on distance - linear attenuation
		float attenuation = saturate(1.0f - length(lightVector) / lightRadius);

	//normalize light vector
	lightVector = normalize(lightVector);

	//compute diffuse light
	float NdL = max(0, dot(normal, lightVector));
	float3 diffuseLight = NdL * Color.rgb;

		//reflection vector
		float3 reflectionVector = normalize(reflect(-lightVector, normal));
		//camera-to-surface vector
		float3 directionToCamera = normalize(cCameraPosPS - position);
		//compute specular light
		float specularLight = specularIntensity * pow(saturate(dot(reflectionVector, directionToCamera)), specularPower);

	//control the brightness of the light
	float lightIntensity = 1.0f;
	float4  textureColor = attenuation * lightIntensity * float4(diffuseLight.rgb, specularLight);

		//take into account attenuation and lightIntensity.
		return textureColor;

}