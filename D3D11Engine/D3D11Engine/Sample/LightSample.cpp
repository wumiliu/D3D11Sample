#include "LightSample.h"
#include "SampleBase.h"
#include "Renderer//GeometricPrimitive.h"
#include "BaseCode/Texture/TextureMgr.h"
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
	
	gameCubeObject.InitResource(GEOMETRY_TYPE_BOX);
	gameCubeObject.SetTexture("Data\\Texture\\seafloor.dds");
	lightNode_ = scene_->CreateChild("Camera");
	lightNode_->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	Quaternion q = Quaternion::CreateFromEulerAngles(0.0f, 0.0f, 0.0f);
	cameraNode_->SetRotation(q);
	float fieldOfView = (float)XM_PI / 4.0f;
	float AspectHByW = (float)mClientWidth / (float)mClientHeight;
	lightCamera = lightNode_->CreateComponent<Camera>();
	lightCamera->ProjParams(fieldOfView, AspectHByW, 1.0f, 100.0f);

	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R32G32B32A32_FLOAT, true);
	normalRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R32G32B32A32_FLOAT, true);
	fxaaRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R32G32B32A32_FLOAT, true);

	//m_pLightingShader = g_objMaterial.GetShader("HLSL\\GeometricPrimitive.hlsl");
	m_pLightingShader = g_objMaterial.GetShader("HLSL\\LightSample\\LightSample.hlsl");
	gameCubeObject.SetMaterial(m_pLightingShader);
	m_pDeferredShader = g_objMaterial.GetShader("HLSL\\LightSample\\Deferred.hlsl");

	TeapotPtr = GeometricPrimitive::CreateTeapot();
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
	if (m_bLightCmaera)
	{
		RenderDeferre();
		return;
	}
	else
	{
		RenderBase();
		return;
	}

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
	m_deviceContext->RSSetState(g_objStates.CullCounterClockwise());
	Vector3 lightDirection = Vector3(0.0f, 0.0f, 1.0f);
	m_pLightingShader->PSSetConstantBuffers("lightDirection", &lightDirection);
	static float rotation = 0.0f;
	rotation = (float)3.141592654f * 0.15f;

	// Rotate the world matrix by the rotation value so that the cube will spin.
	mWorld = Matrix::CreateRotationY(rotation);
	mWorld *= Matrix::CreateScale(5.0f);
	gameCubeObject.Render(mWorld, mView, mProj);
	//gameObject.Render(Matrix::CreateScale(3, 3, 3), mView, mProj);

	//lightCamera->DrawDebugGeometry(mView*mProj, true, { 1, 0, 0, 1 });


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
	Camera* cameraMain = lightNode_->GetComponent<Camera>(true);
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}



	Vector3 lightDirection = Vector3(0.0f, 0.0f, 1.0f);
	m_pLightingShader->PSSetConstantBuffers("lightDirection", &lightDirection);
	m_deviceContext->RSSetState(g_objStates.CullClockwise());
	// Update the rotation variable each frame.
	static float rotation = 0.0f;
	rotation += (float)3.141592654f * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Rotate the world matrix by the rotation value so that the cube will spin.
	mWorld = Matrix::CreateRotationY(rotation);

	gameCubeObject.Render(mWorld, mView, mProj);


	Vector3 eyePos = lightNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	SkyBoxPtr->Render(mWorld*mView*mProj);
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

void LightSample::RenderDeferre()
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

	ID3D11RenderTargetView* pRTV = SwapChainPtr->GetRenderTargetView();
	ID3D11DepthStencilView*        pDSV = SwapChainPtr->GetDepthStencilView();
	ID3D11RenderTargetView* pGBufRTV[] = { colorRT->GetRTView(), normalRT->GetRTView()};
	float clearColor[4] = { 0.1921568627450980392156862745098f, 0.30196078431372549019607843137255f, 0.47450980392156862745098039215686f, 1.0f };


	m_deviceContext->ClearRenderTargetView(pGBufRTV[0], clearColor);
	m_deviceContext->ClearRenderTargetView(pGBufRTV[1], clearColor);

	m_deviceContext->OMSetRenderTargets(2, pGBufRTV, pDSV);
//	colorRT->Begin();
	Vector3 lightDirection = Vector3(0.0f, 0.0f, 1.0f);
	m_pLightingShader->PSSetConstantBuffers("lightDirection", &lightDirection);
	m_deviceContext->RSSetState(g_objStates.CullNone());
	// Update the rotation variable each frame.
	static float rotation = 0.0f;
	rotation = (float)3.141592654f * 0.15f;
//	rotation += (float)3.141592654f * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	// Rotate the world matrix by the rotation value so that the cube will spin.
	mWorld = Matrix::CreateRotationY(rotation);
	mWorld *= Matrix::CreateScale(5.0f);
	gameCubeObject.SetMaterial(m_pDeferredShader);
	gameCubeObject.Render(mWorld, mView, mProj);

	fxaaRT->Begin();
//	ShowRT();

	m_deviceContext->RSSetState(g_objStates.CullNone());
	SwapChainPtr->TurnZBufferOff();
	MaterialPtr pFXAAShader = g_objMaterial.GetShader("HLSL\\LightSample\\FillGBuffer.hlsl");
	pFXAAShader->PSSetConstantBuffers("lightDirection", &lightDirection);
	m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pFXAAShader->PSSetShaderResources(TU_DIFFUSE, colorRT->GetSRView());
	pFXAAShader->PSSetShaderResources(TU_CUBE, normalRT->GetSRView());
	pFXAAShader->Apply();
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.AlphaBlend(), BlendFactor, 0xFFFFFFFF);
	m_deviceContext->Draw(3, 0);
	SwapChainPtr->TurnZBufferOn();
	fxaaRT->End();
	SwapChainPtr->Begin();
	RenderFXAA();
	SwapChainPtr->Flip();
}

void LightSample::RenderBase()
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
	//	colorRT->Begin();
	Vector3 lightDirection = Vector3(0.0f, 0.0f, 1.0f);
	m_pLightingShader->PSSetConstantBuffers("lightDirection", &lightDirection);
	m_deviceContext->RSSetState(g_objStates.CullNone());
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.AlphaBlend(), BlendFactor, 0xFFFFFFFF);

	static float rotation = 0.0f;
	rotation = (float)3.141592654f * 0.15f;
	//	rotation += (float)3.141592654f * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	// Rotate the world matrix by the rotation value so that the cube will spin.
	mWorld = Matrix::CreateRotationY(rotation);
	mWorld *= Matrix::CreateScale(5.0f);
	gameCubeObject.SetMaterial(m_pLightingShader);
	gameCubeObject.Render(mWorld, mView, mProj);
	SwapChainPtr->TurnZBufferOn();
	SwapChainPtr->Flip();
}

void LightSample::RenderFXAA()
{
	MaterialPtr pFXAAShader = g_objMaterial.GetShader("HLSL\\FXAA.hlsl");
	m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	float frameWidth = (float)mClientWidth;
	float frameHeight = (float)mClientHeight;
	Vector4  vFxaa = Vector4(1.0f / frameWidth, 1.0f / frameHeight, 0.0f, 0.0f);

	pFXAAShader->VSSetConstantBuffers("RCPFrame", &vFxaa);
	pFXAAShader->PSSetConstantBuffers("RCPFrame", &vFxaa);

	pFXAAShader->PSSetShaderResources(TU_DIFFUSE, fxaaRT->GetSRView());
	pFXAAShader->Apply();
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);
	m_deviceContext->Draw(3, 0);


}
