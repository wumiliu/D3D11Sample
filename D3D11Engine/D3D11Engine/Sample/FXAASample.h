#pragma once

#include "Sample.h"
class FXAASample : public Sample
{
public:
	SAMPLE_H(FXAASample);
	~FXAASample();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);
	virtual void DrawScene();
	void RenderRT();
protected:
	virtual void InitResource();
	void ShowRT();
private:
	RenderTarget2DPtr colorRT;
	bool m_fxaaEnabled;

};
