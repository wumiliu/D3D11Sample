#include "MultipleLightsSamlpe.h"
#include "SampleBase.h"
//////////////////////////////////////////////////////////////////////////
//spot light用圆锥，point light用球或者立方体，directional light和ambient light用全屏四边形
//light volume。但由于light volume保证是凸几何体，在渲染上比shadow volume简单不少。

SAMPLE_CPP(MultipleLights)

{
}


MultipleLights::~MultipleLights()
{
}

void MultipleLights::InitResource()
{
	Sample::InitResource();
	cameraNode_->SetPosition(Vector3(0.0f, 5.0f, -10.0f));
	pitch_ = 30.0f;
	Quaternion q = Quaternion::CreateFromEulerAngles(pitch_, 0.0f, 0.0f);
	cameraNode_->SetRotation(q);
	m_MaterialMulitPoint = g_objMaterial.GetShader("HLSL\\MultiplePoint.hlsl");
	m_pDeferredShader = g_objMaterial.GetShader("HLSL\\MultipleSample\\Deferred.hlsl");
	m_pPoint = g_objMaterial.GetShader("HLSL\\MultipleSample\\light.hlsl");

	gameSphereObject.SetMaterial(m_MaterialMulitPoint);
	gameObject.SetTexture("Data\\Texture\\wall01.dds");
	m_Light1.m_diffuseColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_Light1.m_position = { -3.0f, 1.0f, 3.0f, 1.0f };

	m_Light2.m_diffuseColor = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_Light2.m_position = { 3.0f, 1.0f, 3.0f, 1.0f };

	m_Light3.m_diffuseColor = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_Light3.m_position = { -3.0f, 1.0f, -3.0f, 1.0f };

	m_Light4.m_diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_Light4.m_position = { 3.0f, 1.0f, -3.0f, 1.0f };
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	normalRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	lightRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	gameObjectSphere.InitResource(GEOMETRY_TYPE_SPHERE);
}

void MultipleLights::UpdateScene(float fTotalTime, float fDeltaTime)
{
	Sample::UpdateScene(fTotalTime, fDeltaTime);
}

void MultipleLights::DrawScene()
{
	RenderTest();
	return;
	RenderBase();
}

void MultipleLights::RenderBase()
{
	SwapChainPtr->Begin();
	SwapChainPtr->TurnZBufferOn();
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}
	Vector4 diffuseColor[4];
	Vector4 lightPosition[4];

	diffuseColor[0] = m_Light1.m_diffuseColor;
	diffuseColor[1] = m_Light2.m_diffuseColor;
	diffuseColor[2] = m_Light3.m_diffuseColor;
	diffuseColor[3] = m_Light4.m_diffuseColor;


	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1.m_position;
	lightPosition[1] = m_Light2.m_position;
	lightPosition[2] = m_Light3.m_position;
	lightPosition[3] = m_Light4.m_position;

	m_MaterialMulitPoint->VSSetConstantBuffers("lightPosition", &lightPosition[0]);
	m_MaterialMulitPoint->PSSetConstantBuffers("diffuseColor", &diffuseColor[0]);

	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);
	ID3D11SamplerState* LinearWrap = g_objStates.LinearWrap();
	m_deviceContext->PSSetSamplers(0, 1, &LinearWrap);
	gameObject.SetMaterial(m_MaterialMulitPoint);
	gameObject.Render(Matrix::Identity, mView, mProj);
	gameSphereObject.SetMaterial(m_MaterialMulitPoint);
	gameSphereObject.Render(Matrix::Identity, mView, mProj);

	SwapChainPtr->Flip();
}

void MultipleLights::RenderDeferred()
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
	ID3D11RenderTargetView* pRTV = SwapChainPtr->GetRenderTargetView();
	ID3D11DepthStencilView*        pDSV = SwapChainPtr->GetDepthStencilView();
	ID3D11RenderTargetView* pGBufRTV[] = { colorRT->GetRTView(), normalRT->GetRTView() };
	float clearColor[4] = { 0.1921568627450980392156862745098f, 0.30196078431372549019607843137255f, 0.47450980392156862745098039215686f, 1.0f };
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);
	m_deviceContext->ClearRenderTargetView(pGBufRTV[0], clearColor);
	m_deviceContext->ClearRenderTargetView(pGBufRTV[1], clearColor);
	m_deviceContext->OMSetRenderTargets(2, pGBufRTV, pDSV);
	float fFar = 1000.0f;
	m_pDeferredShader->VSSetConstantBuffers("fFar", &fFar);

	gameObject.SetMaterial(m_pDeferredShader);
	gameObject.Render(Matrix::Identity, mView, mProj);
	lightRT->Begin();
	Matrix cCameraRot = cameraMain->mInvViewMatrix;

	m_pPoint->VSSetConstantBuffers("cCameraRot", &cCameraRot);
	Vector4 cGBufferOffsets = { 0.5f, 0.5f, 0.5f, 0.5f };
	m_pPoint->VSSetConstantBuffers("cGBufferOffsets", &cGBufferOffsets);

	Vector3 nearVector, farVector;
	cameraMain->GetFrustumSize(nearVector, farVector);
	m_pPoint->VSSetConstantBuffers("cFrustumSize", &farVector);
	gameObjectSphere.SetMaterial(m_MaterialMulitPoint);
	mWorld = Matrix::CreateTranslation(-3.0f, 1.0f, 3.0f);
	gameObjectSphere.Render(mWorld, mView, mProj);
	lightRT->End();

	SwapChainPtr->Begin();
	SwapChainPtr->TurnZBufferOff();
	g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, lightRT->GetSRView());
	SwapChainPtr->Flip();
}

void MultipleLights::RenderTest()
{
	SwapChainPtr->Begin();
	SwapChainPtr->TurnZBufferOn();

	Vector4 diffuseColor[4];
	Vector4 lightPosition[4];

	diffuseColor[0] = m_Light1.m_diffuseColor;
	diffuseColor[1] = m_Light2.m_diffuseColor;
	diffuseColor[2] = m_Light3.m_diffuseColor;
	diffuseColor[3] = m_Light4.m_diffuseColor;


	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1.m_position;
	lightPosition[1] = m_Light2.m_position;
	lightPosition[2] = m_Light3.m_position;
	lightPosition[3] = m_Light4.m_position;

	//m_MaterialMulitPoint->VSSetConstantBuffers("lightPosition", &lightPosition[0]);
//	m_MaterialMulitPoint->PSSetConstantBuffers("diffuseColor", &diffuseColor[0]);

	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	Camera* cameraMain = cameraNode_->GetComponent<Camera>(true);
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}


	lightRT->Begin();
	Matrix cCameraRot = cameraMain->mInvViewMatrix;

	m_pPoint->VSSetConstantBuffers("cCameraRot", &cCameraRot);
	Vector4 cGBufferOffsets = { 0.5f, 0.5f, 0.5f, 0.5f };
	m_pPoint->VSSetConstantBuffers("cGBufferOffsets", &cGBufferOffsets);

	Vector3 nearVector, farVector;
	cameraMain->GetFrustumSize(nearVector, farVector);
	m_pPoint->VSSetConstantBuffers("cFrustumSize", &farVector);
	gameObjectSphere.SetMaterial(m_MaterialMulitPoint);
	mWorld = Matrix::CreateTranslation(-3.0f, 1.0f, 3.0f);
	gameObjectSphere.Render(mWorld, mView, mProj);
	lightRT->End();


	SwapChainPtr->Begin();
	SwapChainPtr->TurnZBufferOff();
	g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, lightRT->GetSRView());
	SwapChainPtr->Flip();
}
