#pragma once
#include "HpD3D9Type.h"
#include "Component.h"
#include "Framework/Frustum.h"
/// %Light types.
enum LightType
{
	LIGHT_DIRECTIONAL = 0,
	LIGHT_SPOT,
	LIGHT_POINT
};
class Light : public Component
{
	OBJECT(Light);
public:
	Light();
	~Light();
	/// Set light type.
	void SetLightType(LightType type);
	/// Set color.
	void SetColor(const Color& color);
	/// Set specular intensity. Zero disables specular calculations. 高光强度
	void SetSpecularIntensity(float intensity);
	/// Set range.
	void SetRange(float range);
	/// Set spotlight field of view.
	void SetFov(float fov);
	/// Set spotlight aspect ratio.
	void SetAspectRatio(float aspectRatio);
	/// Set fade out start distance.
	void SetFadeDistance(float distance);
	/// Set shadow fade out start distance. Only has effect if shadow distance is also non-zero.
	void SetShadowFadeDistance(float distance);

	/// Return light type.
	LightType GetLightType() const { return lightType_; }
	/// Return spotlight frustum.
	Frustum GetFrustum() const;
private:
	/// Light type.
	LightType lightType_;
	/// Color.
	Color color_;
	/// Custom world transform for the light volume.
	Matrix volumeTransform_;
	/// Specular intensity.
	float specularIntensity_;
	/// Range.
	float range_;
	/// Spotlight field of view.
	float fov_;
	/// Spotlight aspect ratio.
	float aspectRatio_;
	/// Fade start distance.
	float fadeDistance_;
	/// Shadow camera near/far clip distance ratio.
	float shadowFadeDistance_;
};

