#pragma once
#include "Sample.h"
#include "Scene/Camera.h"

class LightSample : public Sample
{
public:
	SAMPLE_H(LightSample);
	~LightSample();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);

	virtual void DrawScene();
	void RenderRT();
protected:
	virtual void InitResource();
	void ShowRT();
private:
	RenderTarget2DPtr colorRT;
	class HpNode* lightNode_;
	class Camera* lightCamera;
	bool m_bLightCmaera;
};

