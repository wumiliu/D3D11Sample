#pragma once
#include "Sample.h"
#include "MaterialMgr.h"

/************************************************************************/
/* http://www.catalinzima.com/xna/tutorials/deferred-rendering-in-xna/
移植这边的功能
*/
/************************************************************************/
class DeferredLight : public Sample
{
public:
	SAMPLE_H(DeferredLight);
	~DeferredLight();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);
	virtual void DrawScene();
	void ClearGBuffer();
	void RenderScene();
	void DrawLights(float gameTime);
	void DrawPointLight(Vector3 lightPosition, Color color, float lightRadius, float lightIntensity);
	void DrawDirectionalLight(Vector3 lightDirection, Color color);
protected:
	virtual void InitResource();
	RenderTarget2DPtr colorRT; //color and specular intensity
	RenderTarget2DPtr normalRT; //normals + specular power
	RenderTarget2DPtr depthRT; //depth
	RenderTarget2DPtr lightRT; //lighting
	RenderTarget2DPtr lightRTEx; //lighting


	MaterialPtr	clearBufferEffect;
	MaterialPtr	pointLightEffect;
	MaterialPtr	finalCombineEffect;
	MaterialPtr	directionalLightEffect;
	MaterialPtr	renderGBuffer;
	bool m_fxaaEnabled;

	
};

