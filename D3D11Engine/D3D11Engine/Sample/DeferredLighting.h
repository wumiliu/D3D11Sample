#pragma once
#include "Sample.h"
/************************************************************************/
/* 延迟光照的实现                                                                     */
/************************************************************************/
#include "MaterialMgr.h"
class DeferredLighting : public Sample
{
public:
	SAMPLE_H(DeferredLighting);
	~DeferredLighting();
	virtual void DrawScene();

protected:
	virtual void InitResource();
private:
	void Render();
	void ShowRT();
	void ShowFXAA();
private:
	RenderTarget2DPtr m_TexGBuffer;
	RenderTarget2DPtr m_TexGBuffer2;
	RenderTarget2DPtr m_TexGBufResolved2;
	RenderTarget2DPtr m_TexCoverageMask;

	MaterialPtr m_pFillGBufShader;
	MaterialPtr m_pComplexMaskShader;
	MaterialPtr m_pLightingShader;


};

