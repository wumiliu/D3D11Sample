#include "LightSample.h"
#include "SampleBase.h"

SAMPLE_CPP(LightSample)
{
	m_bLightCmaera = false;
}

LightSample::~LightSample()
{

}

void LightSample::InitResource()
{
	Sample::InitResource();
	 lightNode_ = scene_->CreateChild("Camera");
	 lightNode_->SetPosition(Vector3(0.0f, 5.0f, 1.0f));
	Quaternion q = Quaternion::CreateFromEulerAngles(0.0f, 0.0f, 0.0f);
	cameraNode_->SetRotation(q);
	float fieldOfView = (float)XM_PI / 4.0f;
	float AspectHByW = (float)mClientWidth / (float)mClientHeight;
	lightCamera = lightNode_->CreateComponent<Camera>();
	lightCamera->ProjParams(fieldOfView, AspectHByW, 1.0f, 100.0f);

	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM,true);
}

void LightSample::UpdateScene(float fTotalTime, float fDeltaTime)
{
	if (KEYDOWN(VK_SPACE))
	{
		bKeyDown = true;
	}
	else
	{
		if (bKeyDown)
		{
			m_bLightCmaera = !m_bLightCmaera;
			bKeyDown = false;
		}
	}

	if (m_bLightCmaera)
	{
		const float MOVE_SPEED = 20.0f;
		float dt = fDeltaTime / 1000.0f;
		if (::GetAsyncKeyState('W') & 0x8000)
			lightNode_->Translate(Vector3::Backward * MOVE_SPEED * dt);
		if (::GetAsyncKeyState('S') & 0x8000)
			lightNode_->Translate(Vector3::Forward * MOVE_SPEED * dt);
		if (::GetAsyncKeyState('A') & 0x8000)
			lightNode_->Translate(Vector3::Left * MOVE_SPEED * dt);
		if (::GetAsyncKeyState('D') & 0x8000)
			lightNode_->Translate(Vector3::Right * MOVE_SPEED * dt);
	}
	else
	{
		Sample::UpdateScene(fTotalTime, fDeltaTime);
	}
}

void LightSample::DrawScene()
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
	m_deviceContext->RSSetState(g_objStates.CullNone());
	lightCamera->DrawDebugGeometry(mView*mProj, true, { 1, 0, 0, 1 });


	RenderRT();

	Vector3 eyePos = cameraNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	SkyBoxPtr->Render(mWorld*mView*mProj);


	ShowRT();
	SwapChainPtr->Flip();
}

void LightSample::RenderRT()
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

	SwapChainPtr->TurnZBufferOff();
	m_deviceContext->RSSetState(g_objStates.CullNone());
	g_objSprite.ShowTexture(20, 20, "Data\\Texture\\wall01.dds");
	g_objSprite.ShowRect(400, 400, 500, 500, { 0, 0, 1, 0 }, mTimer.TotalTime());
	g_objSprite.DrawCircle(100, 100, 50, { 0, 1, 0, 1 });
	g_objSprite.ShowBlock(556, 256, 656, 356, { 1, 0, 0, 0.5f }, mTimer.TotalTime());
	ID3D11ShaderResourceView* pSrv = SwapChainPtr->GetResourceView();
	g_objSprite.ShowTexture(556, 256, 656, 356, pSrv);


	colorRT->End();

}

void LightSample::ShowRT()
{
	SwapChainPtr->TurnZBufferOff();
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
