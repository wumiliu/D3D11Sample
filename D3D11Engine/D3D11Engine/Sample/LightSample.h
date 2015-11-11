#pragma once
#include "Sample.h"


class LightSample : public Sample
{
public:
	SAMPLE_H(LightSample);
	~LightSample();
	virtual void DrawScene();
	void RenderRT();
protected:
	virtual void InitResource();
private:
	RenderTarget2DPtr colorRT;

};

