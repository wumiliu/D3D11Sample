#pragma once
#include "Windows/D3D11App.h"
class Sample :public D3D11App
{
public:
	Sample(HINSTANCE hInstance, int nWidth = 1024, int nHeight = 600);
	~Sample();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);

	virtual void DrawScene();
protected:
	void InitResource();

};

