#include "object3d.hlsli"

//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}

struct TransformationMatrix
{
    float4x4 WVP;
    float4x4 world;
};
StructuredBuffer<TransformationMatrix> gTransformationMatrix : register(t0);

struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

VertexShaderOutput main(VertexShaderInput input, int instanceId:SV_InstanceId)
{
    VertexShaderOutput output;
    output.position = mul(input.position, gTransformationMatrix[instanceId].WVP);
    output.texcoord = input.texcoord;
    output.normal = normalize(mul(input.normal, (float3x3) gTransformationMatrix[instanceId].world));
    return output;
}


