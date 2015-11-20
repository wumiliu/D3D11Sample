
cbuffer CameraVS : register(b1)
{
	float3 cCameraPos;
	float3 cFrustumSize;
	matrix cCameraRot;
	matrix View;
	matrix Projection;
}

cbuffer ObjectVS : register(b5)
{
	matrix World;
}

cbuffer CameraPS : register(b1)
{
	float3 cCameraPosPS;
}

cbuffer LightPS : register(b3)
{
	float3 lightDirection;
	float3 lightPosition;
	float3 Color;
	float lightRadius;
}