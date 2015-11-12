/*============================================================================

                  FXAA v2 CONSOLE by TIMOTHY LOTTES @ NVIDIA

============================================================================*/

// Adapted for Urho3D from http://timothylottes.blogspot.com/2011/04/nvidia-fxaa-ii-for-console.html
Texture2D tDiffMap : register(t0);
SamplerState sDiffMap : register(s0);

#define Sample2DLod0(tex, uv) t##tex.SampleLevel(s##tex, uv, 0.0)


cbuffer cbFxaa : register(b1) {
    float4 cGBufferInvSize : packoffset(c0);
};


struct FxaaVS_Output {
	float4 iScreenPos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

FxaaVS_Output VS(uint id : SV_VertexID) {
	FxaaVS_Output Output;
	Output.Tex = float2((id << 1) & 2, id & 2);
	Output.iScreenPos = float4(Output.Tex * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f), 0.0f, 1.0f);
	return Output;
}

float PS(FxaaVS_Output input) :SV_TARGET
{
	float2 iScreenPos = input.iScreenPos;
	float4 oColor;
    float FXAA_SUBPIX_SHIFT = 1.0/4.0; // Not used
    float FXAA_SPAN_MAX = 8.0;
    float FXAA_REDUCE_MUL = 1.0/8.0;
    float FXAA_REDUCE_MIN = 1.0/128.0;

    float4 cFXAAParams = float4(0.4, 0.5, 0.75,0.0f);
    float2 posOffset = cGBufferInvSize.xy * cFXAAParams.x;

    float3 rgbNW = Sample2DLod0(DiffMap, iScreenPos + float2(-posOffset.x, -posOffset.y)).rgb;
    float3 rgbNE = Sample2DLod0(DiffMap, iScreenPos + float2(posOffset.x, -posOffset.y)).rgb;
    float3 rgbSW = Sample2DLod0(DiffMap, iScreenPos + float2(-posOffset.x, posOffset.y)).rgb;
    float3 rgbSE = Sample2DLod0(DiffMap, iScreenPos + float2(posOffset.x, posOffset.y)).rgb;
    float3 rgbM  = Sample2DLod0(DiffMap, iScreenPos).rgb;

    float3 luma = float3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    if (((lumaMax - lumaMin) / lumaMin) >= cFXAAParams.y)
    {
        float2 dir;
        dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
        dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    
        float dirReduce = max(
            (lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL),
            FXAA_REDUCE_MIN);
        float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
        dir = min(float2( FXAA_SPAN_MAX,  FXAA_SPAN_MAX),
              max(float2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),
              dir * rcpDirMin)) * cGBufferInvSize.xy;
    
        dir *= cFXAAParams.z;
    
        float3 rgbA = (1.0/2.0) * (
            Sample2DLod0(DiffMap, iScreenPos + dir * (1.0/3.0 - 0.5)).xyz +
            Sample2DLod0(DiffMap, iScreenPos + dir * (2.0/3.0 - 0.5)).xyz);
        float3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (
            Sample2DLod0(DiffMap, iScreenPos + dir * (0.0/3.0 - 0.5)).xyz +
            Sample2DLod0(DiffMap, iScreenPos + dir * (3.0/3.0 - 0.5)).xyz);
        float lumaB = dot(rgbB, luma);
        
        float3 rgbOut;
        if((lumaB < lumaMin) || (lumaB > lumaMax))
            rgbOut = rgbA;
        else
            rgbOut = rgbB;

        oColor = float4(rgbOut, 1.0);
    }
    else
        oColor = float4(rgbM, 1.0);
	return oColor;
}
