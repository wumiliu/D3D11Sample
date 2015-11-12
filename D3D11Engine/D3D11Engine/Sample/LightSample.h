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
	void ShowRT();
private:
	RenderTarget2DPtr colorRT;

};

