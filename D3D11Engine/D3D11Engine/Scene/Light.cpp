#include "Light.h"
#include "HpNode.h"
/// Return the larger of two floats.
inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
/// Clamp a float to a range.
inline float Clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

static const float M_EPSILON = 0.000001f;
static const float M_MIN_NEARCLIP = 0.01f;
static const float M_MAX_FOV = 160.0f;
Light::Light()
{

}


Light::~Light()
{
}

void Light::SetLightType(LightType type)
{
	lightType_ = type;
}

void Light::SetColor(const Color& color)
{
	color_ = color;
}

void Light::SetSpecularIntensity(float intensity)
{
	specularIntensity_ = Max(intensity, 0.0f);
}

void Light::SetRange(float range)
{
	range_ = Max(range, 0.0f);
}

void Light::SetFov(float fov)
{
	fov_ = Clamp(fov, 0.0f, M_MAX_FOV);
}

void Light::SetAspectRatio(float aspectRatio)
{
	aspectRatio_ = Max(aspectRatio, M_EPSILON);
}

void Light::SetFadeDistance(float distance)
{
	fadeDistance_ = Max(distance, 0.0f);

}

void Light::SetShadowFadeDistance(float distance)
{
	shadowFadeDistance_ = Max(distance, 0.0f);
}

Frustum Light::GetFrustum() const
{
	Matrix frustumTransform;
	if (node_)
	{
		frustumTransform.Decompose(node_->GetWorldScale(), node_->GetWorldRotation(), node_->GetWorldPosition());
	}
	// Note: frustum is unaffected by node or parent scale
	Frustum ret;
	ret.Define(fov_, aspectRatio_, 1.0f, M_MIN_NEARCLIP, range_, frustumTransform);
	return ret;
}
