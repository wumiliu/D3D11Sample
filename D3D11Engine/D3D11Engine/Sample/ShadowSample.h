#pragma once
#include "Sample.h"
#include "MaterialMgr.h"
#include "Framework/AnimationHelper.h"
class ShadowSample : public Sample
{
public:
	SAMPLE_H(ShadowSample);
	~ShadowSample();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);
	virtual void DrawScene();
protected:
	virtual void InitResource();
	class HpNode* cameraScreenNode_;
	class Camera* cameraScreen;

private:
	void RenderRT();
	void ShowRT();
private:
	RenderTarget2DPtr colorRT;
	bool m_fxaaEnabled;
	RenderTarget2DPtr depthRT; //color and specular intensity
	MaterialPtr m_pDepthShader;

	MaterialPtr m_pShadowShader;
	AnimationHelper::BoneAnimation mCamerAnimation;
	float mCamerTimPos;
};

