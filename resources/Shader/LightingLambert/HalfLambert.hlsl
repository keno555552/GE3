#ifndef _LM_HALFLAMBERT_LIGHTING_
#define _LM_HALFLAMBERT_LIGHTING_

float3 ApplyLighting_HalfLambert(float3 N, float3 L, float3 lightColor)
{
    return pow(dot(N, L)*0.5f + 0.5f, 2.0f) * lightColor;
}

#endif