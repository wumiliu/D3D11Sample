#pragma once
#include "HpD3D9Type.h"
#include "GameTimer.h"
struct  MousePos
{
	int X;
	int Y;
	bool bLeftDown;
	MousePos()
	{
		X = 0;
		Y = 0;
		bLeftDown = false;
	}
	MousePos(int x, int y)
	{
		X = x;
		Y = y;
		bLeftDown = false;
	}
};
//////////////////////////////////////////////////////////////////////////
//应用程序框架类
//////////////////////////////////////////////////////////////////////////
class D3D11App
{
public:
	D3D11App(HINSTANCE hInstance);
	~D3D11App();
	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.
	int Run();

	virtual bool Init();
	virtual void OnResize();
	virtual void UpdateScene(float TotalTime, float fDeltaTime) = 0;
	virtual void DrawScene() = 0;


	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){};
	virtual void OnMouseUp(WPARAM btnState, int x, int y){};
	virtual void OnMouseMove(WPARAM btnState, int x, int y){};
	virtual void OnMouseWheel(short zDelta, int x, int y){};
	virtual void OnLButtonDblClk(WPARAM btnState, int x, int y){};
	virtual void OnDragFinish(const char* filName){};
protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameStats();
	virtual void InitResource() = 0;
protected:

	HINSTANCE mhAppInst;
	HWND      mhMainWnd;
	bool      mAppPaused;
	bool      mMinimized;
	bool      mMaximized;
	bool      mResizing;

	GameTimer mTimer;

	ID3D11Device			*m_d3dDevice;				//D3D11设备
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	//D3D_DRIVER_TYPE md3dDriverType;
	int mClientWidth;
	int mClientHeight;

	int mClientWidthOld;
	int mClientHeightOld;
	std::shared_ptr<class SwapChain> SwapChainPtr;
	std::shared_ptr<class FontRender> FontRenderPtr;

	bool bMouseDown;
	MousePos mouseLast;
};

