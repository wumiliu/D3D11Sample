#pragma once
#include "HpD3D9Type.h"

struct Aniframe
{
	Vector3 Translation;
	Vector3 Scale;
	Vector4 RotationQuat;
};
class AnimationHelper
{
public:
	struct Keyframe
	{
		Keyframe();
		~Keyframe();

		float TimePos;
		XMFLOAT3 Translation;
		XMFLOAT3 Scale;
		XMFLOAT4 RotationQuat;
	};
	struct BoneAnimation
	{
		float GetStartTime()const;
		float GetEndTime()const;

		Aniframe Interpolate(float t, XMFLOAT4X4& M)const;

		std::vector<Keyframe> Keyframes;

	};

};

