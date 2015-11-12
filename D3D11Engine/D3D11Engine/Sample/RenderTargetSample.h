
#pragma once
#include "Sample.h"
class RenderTargetSample : public Sample
{
public:
	SAMPLE_H(RenderTargetSample);
	~RenderTargetSample();
	virtual void DrawScene();
	void RenderRT();
protected:
	virtual void InitResource();
	void ShowRT();
private:
	RenderTarget2DPtr colorRT;

};

