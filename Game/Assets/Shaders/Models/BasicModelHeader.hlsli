//// �e��錾 ////

struct SVSInput
{
	float4 pos : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 uv : TEXCOORD;
	min16uint4 boneNo : BONE_NO;
	min16uint4 weight : WEIGHT;
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct SPSInput
{
	float4 svpos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 uv : TEXCOORD0;
	float4 posInWorld : TEXCOORD1;
	float4 posInLVP : TEXCOORD2;
};

#define FLT_MAX 3.402823466e+38F

//// �e�탌�W�X�^ ////

SamplerState g_sampler : register(s0);

// �X�L�j���O�p�̃{�[���s��
StructuredBuffer<float4x4> g_mBones : register(t0);
// �C���X�^���V���O�p�̃��[���h�s��̔z��
StructuredBuffer<float4x4> g_worldMatrixArray : register(t1);
// �e�N�X�`��
Texture2D<float4> g_shadowMap : register(t2);
Texture2D<float4> g_diffuseTexture : register(t3);
Texture2D<float4> g_normalTexture : register(t4);

cbuffer ModelCB : register(b0)
{
	float4x4 g_mWorld;
	float4x4 g_mViewProj;
	float4x4 g_mLightViewProj;
	float3 g_lightPos;
	int g_isShadowReceiver;
}


//// �֐� ////

