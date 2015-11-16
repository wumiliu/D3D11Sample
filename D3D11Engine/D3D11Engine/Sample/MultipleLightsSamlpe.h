#pragma once
#include "Sample.h"
#include "Scene/Camera.h"
#include "MaterialMgr.h"
#include "Framework/GameObject.h"

class MultipleLights : public Sample
{
	struct MyLightClass
	{
	public:
		Vector4 m_diffuseColor;
		Vector4 m_position;
	};
public:
	SAMPLE_H(MultipleLights);
	~MultipleLights();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);

	virtual void DrawScene();

protected:
	virtual void InitResource();
	void RenderBase();
	void RenderDeferred();
	void RenderTest();
private:
	RenderTarget2DPtr colorRT;
	RenderTarget2DPtr normalRT;
	RenderTarget2DPtr lightRT;

	MyLightClass m_Light1;
	MyLightClass m_Light2;
	MyLightClass m_Light3;
	MyLightClass m_Light4;
	std::shared_ptr<class D3D11RendererMaterial> m_MaterialMulitPoint;
	std::shared_ptr<class D3D11RendererMaterial> m_pPoint;

	MaterialPtr m_pDeferredShader;
	GameObject gameObjectSphere;

};

