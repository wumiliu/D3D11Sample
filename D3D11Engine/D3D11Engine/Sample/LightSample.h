#pragma once
#include "Sample.h"
#include "Scene/Camera.h"
#include "MaterialMgr.h"
#include "Framework/GameObject.h"

class LightSample : public Sample
{
	struct LightBuffer
	{
		Vector4 lightDirection;
	};

public:
	SAMPLE_H(LightSample);
	~LightSample();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);

	virtual void DrawScene();
	void RenderRT();
protected:
	virtual void InitResource();
	void ShowRT();
	void RenderDeferre();
	void RenderBase();
	void RenderFXAA();
private:
	RenderTarget2DPtr fxaaRT;
	RenderTarget2DPtr colorRT;
	RenderTarget2DPtr normalRT;

	MaterialPtr m_pLightingShader;
	MaterialPtr m_pDeferredShader;

	GeometricPrimitivePtr TeapotPtr;
	class HpNode* lightNode_;
	class Camera* lightCamera;
	bool m_bLightCmaera;
	GameObject gameCubeObject;

};

