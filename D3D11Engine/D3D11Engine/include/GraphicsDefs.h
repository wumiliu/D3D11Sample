#pragma  once
#include "StringHash.h"
/// Vertex elements.
enum VertexElement
{
	ELEMENT_POSITION = 0,
	ELEMENT_NORMAL,
	ELEMENT_COLOR,
	ELEMENT_TEXCOORD1,
	ELEMENT_TEXCOORD2,
	ELEMENT_CUBETEXCOORD1,
	ELEMENT_CUBETEXCOORD2,
	ELEMENT_TANGENT,
	ELEMENT_BLENDWEIGHTS,
	ELEMENT_BLENDINDICES,
	ELEMENT_INSTANCEMATRIX1,
	ELEMENT_INSTANCEMATRIX2,
	ELEMENT_INSTANCEMATRIX3,
	MAX_VERTEX_ELEMENTS
};

/// Vertex/index buffer lock state.
enum LockState
{
	LOCK_NONE = 0,
	LOCK_HARDWARE,
	LOCK_SHADOW
};
/// Shader types.
enum ShaderType
{
	VS = 0,
	PS,
};
enum ShaderParameterGroup
{
	SP_FRAME = 0,
	SP_CAMERA,
	SP_ZONE,
	SP_LIGHT,
	SP_MATERIAL,
	SP_OBJECT,
	SP_CUSTOM,
	MAX_SHADER_PARAMETER_GROUPS
};


/// Texture units.
enum TextureUnit
{
	TU_DIFFUSE = 0,
	TU_CUBE = 1,
	TU_NORMAL = 2,

	MAX_TEXTURE_UNITS 
};

enum VERTEX_MASK_FLAG
{
	MASK_NONE = 0x0,
	MASK_POSITION = 0x1,
	MASK_NORMAL = 0x2,
	MASK_COLOR = 0x4,
	MASK_TEXCOORD1 = 0x8,
	MASK_TEXCOORD2 = 0x10,
	MASK_CUBETEXCOORD1 = 0x20,
	MASK_CUBETEXCOORD2 = 0x40,
	MASK_TANGENT = 0x80,
	MASK_BLENDWEIGHTS = 0x100,
	MASK_BLENDINDICES = 0x200,
	MASK_INSTANCEMATRIX1 = 0x400,
	MASK_INSTANCEMATRIX2 = 0x800,
	MASK_INSTANCEMATRIX3 = 0x1000,
};

static const unsigned MASK_DEFAULT = 0xffffffff;
static const unsigned NO_ELEMENT = 0xffffffff;




const StringHash VSP_AMBIENTSTARTCOLOR("AmbientStartColor");
const StringHash VSP_AMBIENTENDCOLOR("AmbientEndColor");
const StringHash VSP_BILLBOARDROT("BillboardRot");
const StringHash VSP_CAMERAPOS("CameraPos");
const StringHash VSP_CAMERAROT("CameraRot");
const StringHash VSP_CLIPPLANE("ClipPlane");
const StringHash VSP_NEARCLIP("NearClip");
const StringHash VSP_FARCLIP("FarClip");
const StringHash VSP_DEPTHMODE("DepthMode");
const StringHash VSP_DELTATIME("DeltaTime");
const StringHash VSP_ELAPSEDTIME("ElapsedTime");
const StringHash VSP_FRUSTUMSIZE("FrustumSize");
const StringHash VSP_GBUFFEROFFSETS("GBufferOffsets");
const StringHash VSP_LIGHTDIR("LightDir");
const StringHash VSP_LIGHTPOS("LightPos");
const StringHash VSP_MODEL("Model");
const StringHash VSP_VIEWPROJ("ViewProj");
const StringHash VSP_UOFFSET("UOffset");
const StringHash VSP_VOFFSET("VOffset");
const StringHash VSP_ZONE("Zone");
const StringHash VSP_LIGHTMATRICES("LightMatrices");
const StringHash VSP_SKINMATRICES("SkinMatrices");
const StringHash VSP_VERTEXLIGHTS("VertexLights");
const StringHash PSP_AMBIENTCOLOR("AmbientColor");
const StringHash PSP_CAMERAPOS("CameraPosPS");
const StringHash PSP_DELTATIME("DeltaTimePS");
const StringHash PSP_DEPTHRECONSTRUCT("DepthReconstruct");
const StringHash PSP_ELAPSEDTIME("ElapsedTimePS");
const StringHash PSP_FOGCOLOR("FogColor");
const StringHash PSP_FOGPARAMS("FogParams");
const StringHash PSP_GBUFFERINVSIZE("GBufferInvSize");
const StringHash PSP_LIGHTCOLOR("LightColor");
const StringHash PSP_LIGHTDIR("LightDirPS");
const StringHash PSP_LIGHTPOS("LightPosPS");
const StringHash PSP_MATDIFFCOLOR("MatDiffColor");
const StringHash PSP_MATEMISSIVECOLOR("MatEmissiveColor");
const StringHash PSP_MATENVMAPCOLOR("MatEnvMapColor");
const StringHash PSP_MATSPECCOLOR("MatSpecColor");
const StringHash PSP_NEARCLIP("NearClipPS");
const StringHash PSP_FARCLIP("FarClipPS");
const StringHash PSP_SHADOWCUBEADJUST("ShadowCubeAdjust");
const StringHash PSP_SHADOWDEPTHFADE("ShadowDepthFade");
const StringHash PSP_SHADOWINTENSITY("ShadowIntensity");
const StringHash PSP_SHADOWMAPINVSIZE("ShadowMapInvSize");
const StringHash PSP_SHADOWSPLITS("ShadowSplits");
const StringHash PSP_LIGHTMATRICES("LightMatricesPS");

 const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
