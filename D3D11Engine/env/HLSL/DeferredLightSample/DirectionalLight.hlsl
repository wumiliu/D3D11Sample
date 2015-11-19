
cbuffer  MatrixBuffer: register(b1)
{
	float3 cameraPosition;
	float3 lightDirection;
	float3 Color;
	matrix InvertViewProjection;
};


struct FxaaVS_Output {
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

FxaaVS_Output VS(uint id : SV_VertexID) {
	FxaaVS_Output Output;
	Output.Tex = float2((id << 1) & 2, id & 2);
	Output.Pos = float4(Output.Tex * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
	return Output;
}

Texture2D colorMap: register(t0);
SamplerState SampleType: register(s0);

Texture2D depthMap: register(t1);
SamplerState SampleType1: register(s1);

Texture2D normalMap: register(t2);
SamplerState SampleType2: register(s2);



float4 PS(FxaaVS_Output input) : SV_TARGET{

	float4 normalData = normalMap.Sample(SampleType2, input.Tex);
	float3 normal = 2.0f * normalData.xyz - 1.0f;
	float specularPower = normalData.a * 255.0f;
	float specularIntensity = colorMap.Sample(SampleType, input.Tex).a;
	float depthVal = depthMap.Sample(SampleType1, input.Tex).r;

	float4 position;
	position.x = input.Tex.x * 2.0f - 1.0f;
	position.y = -(input.Tex.x * 2.0f - 1.0f);
	position.z = depthVal;
	position.w = 1.0f;
	//transform to world space
	position = mul(position, InvertViewProjection);
	position /= position.w;

	float3 lightVector = -normalize(lightDirection);

		//compute diffuse light
	float NdL = max(0, dot(normal, lightVector));
	float3 diffuseLight = NdL * Color.rgb;

		//reflexion vector
	float3 reflectionVector = normalize(reflect(-lightVector, normal));
		//camera-to-surface vector
	float3 directionToCamera = normalize(cameraPosition - position);
		//compute specular light
	float specularLight = specularIntensity * pow(saturate(dot(reflectionVector, directionToCamera)), specularPower);
	//output the two lights
	return float4(diffuseLight.rgb, specularLight);

}


