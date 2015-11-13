#pragma once
#include "Windows/D3D11App.h"
#include "Framework/GameObject.h"

#define SAMPLE_H(typeName) \
	 public: \
	 typeName(HINSTANCE hInstance, int nWidth = 1024, int nHeight = 600);

#define SAMPLE_CPP(typeName) \
	typeName:: typeName(HINSTANCE hInstance, int nWidth, int nHeight):\
	 Sample(hInstance,nWidth,nHeight)

typedef std::shared_ptr<class RenderTarget2D> RenderTarget2DPtr;

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

class Sample :public D3D11App
{
public:
	Sample(HINSTANCE hInstance, int nWidth = 1024, int nHeight = 600);
	~Sample();
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);

	virtual void DrawScene();
	virtual void OnMouseUp(WPARAM btnState, int x, int y);
	virtual void OnMouseMove(WPARAM btnState, int x, int y);
protected:
	virtual void InitResource();
	HRESULT DeviceCreated();
	void CreateScrene();
	void RenderSample();
	std::shared_ptr<class Scene> scene_; 
	class HpNode* cameraNode_;
	class Camera* cameraMain;
	std::shared_ptr<class SkyBox>SkyBoxPtr;
	/// Camera yaw angle.
	float yaw_;
	/// Camera pitch angle.
	float pitch_;
	GameObject gameObject;
	GameObject gameSphereObject;

	ID3D11SamplerState*	m_pTextureSampler;
	ID3D11SamplerState*	m_pPointSampler;
	ID3D11DepthStencilState* m_pWriteStencilDSState;
	ID3D11DepthStencilState* m_pTestStencilDSState;
	bool bKeyDown;
};

