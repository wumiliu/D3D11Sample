#include "RenderTargetSample.h"

#include "SampleBase.h"

SAMPLE_CPP(RenderTargetSample)
{

}

RenderTargetSample::~RenderTargetSample()
{

}

void RenderTargetSample::InitResource()
{
	Sample::InitResource();
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, true);
}

void RenderTargetSample::DrawScene()
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	Camera* cameraMain = cameraNode_->GetComponent<Camera>(true);
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}
	SwapChainPtr->Begin();

	SwapChainPtr->TurnZBufferOn();
	gameObject.Render(Matrix::CreateScale(5, 5, 5), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(3, 3, 3), mView, mProj);
	RenderRT();

	int x = (int)(mClientWidth * 0.66666f - 10);
	int y = (int)(mClientHeight * 0.66666f - 10);
	int width = mClientWidth + 10;
	int height = mClientHeight + 10;
	RECT rect;
	rect.left = (int)(mClientWidth * 0.66666f - 5);
	rect.right = mClientWidth - 5;
	rect.top = (int)(mClientHeight * 0.66666f - 5);
	rect.bottom = mClientHeight - 5;
	float h = (float)(rect.bottom - rect.top);
	float w = (float)(rect.right - rect.left);
	Vector3 eyePos = cameraNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	SkyBoxPtr->Render(mWorld*mView*mProj);


	ShowRT();
	SwapChainPtr->Flip();
}

void RenderTargetSample::RenderRT()
{
	colorRT->Begin();

	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	Camera* cameraMain = cameraNode_->GetComponent<Camera>(true);
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}

	Vector3 eyePos = cameraNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	SkyBoxPtr->Render(mWorld*mView*mProj);
	// 绘制2D的时候，关闭深度缓冲.天空盒优先于2d 绘制
	SwapChainPtr->TurnZBufferOff();
	m_deviceContext->RSSetState(g_objStates.CullNone());
	g_objSprite.ShowTexture(20, 20, "Data\\Texture\\wall01.dds");
	g_objSprite.ShowRect(400, 400, 500, 500, { 0, 0, 1, 0 }, mTimer.TotalTime());
	g_objSprite.DrawCircle(100, 100, 50, { 0, 1, 0, 1 });
	g_objSprite.ShowBlock(556, 256, 656, 356, { 1, 0, 0, 0.5f }, mTimer.TotalTime());

	colorRT->End();

}

void RenderTargetSample::ShowRT()
{
	SwapChainPtr->TurnZBufferOff();//绘制2D的时候，关闭深度缓冲
	int x = (int)(mClientWidth * 0.66666f - 10);
	int y = (int)(mClientHeight * 0.66666f - 10);
	int width = mClientWidth - x;
	int height = mClientHeight - y;
	g_objSprite.ShowBlock(x, y, x + width, y + height, { 0.000000000f, 0.000000000f, 0.000000000f, 0.500000000f });
	x = (int)(mClientWidth * 0.66666f - 5);
	y = (int)(mClientHeight * 0.66666f - 5);
	int w = mClientWidth - x - 5;
	int h = mClientHeight - y - 5;
	g_objSprite.ShowTexture(x, y, x + w, y + h, colorRT->GetSRView());
}
