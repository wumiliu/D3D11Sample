#pragma once
#include "Sample.h"
/************************************************************************/
/* 延迟光照的实现                                                                     */
/************************************************************************/

class DeferredLighting : public Sample
{
public:
	SAMPLE_H(DeferredLighting);
	~DeferredLighting();
	virtual void DrawScene();

protected:
	virtual void InitResource();
private:
	RenderTarget2DPtr colorRT;
	RenderTarget2DPtr normalRT;
	RenderTarget2DPtr depthRT;
	RenderTarget2DPtr lightRT;

	std::shared_ptr<class D3D11RendererMaterial> m_MaterialMulitPoint;
	std::shared_ptr<class D3D11RendererMaterial> m_MaterialDeferred;
	std::shared_ptr<class D3D11RendererMaterial> m_MaterialGBuffer;
	std::shared_ptr<class D3D11RendererMaterial> m_MaterialPtr;

};

