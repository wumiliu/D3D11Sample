

float4 GetScreenPos(float4 clipPos)
{
	float4 cGBufferOffsets = float4( 0.5f, 0.5f, 0.5f, 0.5f );
	return float4(
		clipPos.x * cGBufferOffsets.z + cGBufferOffsets.x * clipPos.w,
		-clipPos.y * cGBufferOffsets.w + cGBufferOffsets.y * clipPos.w,
		0.0,
		clipPos.w);
}

float3 GetFarRay(float4 clipPos)
{
	float3 viewRay = float3(
		clipPos.x / clipPos.w * cFrustumSize.x,
		clipPos.y / clipPos.w * cFrustumSize.y,
		cFrustumSize.z);

	return mul(viewRay, cCameraRot);
}
