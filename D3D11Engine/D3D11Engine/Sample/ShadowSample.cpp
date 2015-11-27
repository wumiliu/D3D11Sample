#include "ShadowSample.h"
#include "SampleBase.h"
#include "BaseCode/Texture/TextureMgr.h"

SAMPLE_CPP(ShadowSample)
{
	m_fxaaEnabled = false;
}

ShadowSample::~ShadowSample()
{
}

void ShadowSample::InitResource()
{
	Sample::InitResource();
	cameraNode_->SetPosition(Vector3(0.0f, 25.0f, -45));
	pitch_ = 30.0f;
	Quaternion q = Quaternion::CreateFromEulerAngles(pitch_, 0.0f, 0.0f);
	cameraNode_->SetRotation(q);
	cameraScreenNode_ = scene_->CreateChild("cameraScreenNode");
	Vector3 eyePos(-30.0f, 18.0f, 2.0f);
	cameraScreenNode_->SetPosition(eyePos);
	HpNode* pNode = cameraScreenNode_->CreateChild("CameraNode");
	pNode->SetRotation(Quaternion::CreateFromEulerAngles(30, 0, 0));
	float fieldOfView = (float)XM_PI / 4.0f;
	float AspectHByW = (float)mClientWidth / (float)mClientHeight;
	cameraScreen = pNode->CreateComponent<Camera>();
	cameraScreen->ProjParams(fieldOfView, AspectHByW, 1.0f, 100.0f);

	int nCount = 3;
	XMFLOAT3 eyePos1(-20.0f, 18.0f, 2.0f);
	XMVECTOR q0 = XMQuaternionRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(0.0));
	XMVECTOR q1 = XMQuaternionRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(90.0f));
	XMVECTOR q2 = XMQuaternionRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(180.0f));
	XMVECTOR q3 = XMQuaternionRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), XMConvertToRadians(70.0f));
	mCamerAnimation.Keyframes.resize(nCount);
	mCamerAnimation.Keyframes[0].TimePos = 0.0f;
	mCamerAnimation.Keyframes[0].Translation = eyePos1;
	mCamerAnimation.Keyframes[0].Scale = XMFLOAT3(1.0f, 11.0f, 1.0f);
	XMStoreFloat4(&mCamerAnimation.Keyframes[0].RotationQuat, q0);

	mCamerAnimation.Keyframes[1].TimePos = 2.0f;
	mCamerAnimation.Keyframes[1].Translation = XMFLOAT3(-15.0f, 13.0f, 0.0f);
	mCamerAnimation.Keyframes[1].Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMStoreFloat4(&mCamerAnimation.Keyframes[1].RotationQuat, q1);


	mCamerAnimation.Keyframes[2].TimePos = 6.0f;
	mCamerAnimation.Keyframes[2].Translation = XMFLOAT3(-10.0f, 18.0f, -5.0f);
	mCamerAnimation.Keyframes[2].Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMStoreFloat4(&mCamerAnimation.Keyframes[2].RotationQuat, q2);
	mCamerTimPos = 0.0f;
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);

	depthRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R32_FLOAT,true);
	m_pDepthShader = g_objMaterial.GetShader("HLSL\\ShadowSample\\Depth.hlsl");
	m_pShadowShader = g_objMaterial.GetShader("HLSL\\ShadowSample\\Shadow.hlsl");


}

void ShadowSample::UpdateScene(float fTotalTime, float fDeltaTime)
{

	Sample::UpdateScene(fTotalTime, fDeltaTime);
	bool bLoop = true;
	float fDt = fDeltaTime / 1000.0f;

	mCamerTimPos += fDt*0.5f;
	if (mCamerTimPos >= mCamerAnimation.GetEndTime() && bLoop)	
	{
		mCamerTimPos = 0.0f;// 
	}
	XMFLOAT4X4 mSkullWorld;
	Aniframe aniFrame = mCamerAnimation.Interpolate(mCamerTimPos, mSkullWorld);

	cameraScreenNode_->SetWorldPosition(aniFrame.Translation);
	Quaternion rotate = aniFrame.RotationQuat;
	cameraScreenNode_->SetWorldRotation(rotate);
	if (KEYDOWN(VK_SPACE))
	{
		bKeyDown = true;
	}
	else
	{
		if (bKeyDown)
		{
			m_fxaaEnabled = !m_fxaaEnabled;
			bKeyDown = false;
		}
	}

}

void ShadowSample::DrawScene()
{
	SwapChainPtr->Begin();
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}
	TurnZBufferOn();
	RenderRT();

	ID3D11RenderTargetView* pRTV = SwapChainPtr->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = SwapChainPtr->GetDepthStencilView();
	pRTV = colorRT->GetRTView();
	float ClearColor[4] = { sqrt(0.25f), sqrt(0.25f), sqrt(0.5f), 0.0f };
	m_deviceContext->ClearRenderTargetView(pRTV, ClearColor);
	m_deviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
	// Rebind to original back buffer and depth buffer
	ID3D11RenderTargetView * pRTVs[2] = { pRTV, NULL };
	pRTVs[0] = colorRT->GetRTView();
	m_deviceContext->OMSetRenderTargets(1, pRTVs, pDSV);

	Vector3 lightPos = cameraScreen->GetNode()->GetWorldPosition();
	Vector4 ambientColor = Vector4(0.15f, 0.15f, 0.15f, 1.0f);
	Vector4 diffuseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	gameObject.SetMaterial(m_pShadowShader);
	Matrix lightViewMatrix, lightProjectionMatrix;
	if (cameraScreen)
	{
		lightViewMatrix = cameraScreen->GetView();
		lightProjectionMatrix = cameraScreen->GetProjection();
	}
	mWorld = Matrix::CreateScale(3, 3, 3);

	m_pShadowShader->VSSetConstantBuffers("worldMatrix", &mWorld);
	m_pShadowShader->VSSetConstantBuffers("viewMatrix", &mView);
	m_pShadowShader->VSSetConstantBuffers("projectionMatrix", &mProj);
	m_pShadowShader->VSSetConstantBuffers("lightViewMatrix", &lightViewMatrix);
	m_pShadowShader->VSSetConstantBuffers("lightProjectionMatrix", &lightProjectionMatrix);
	m_pShadowShader->VSSetConstantBuffers("lightPosition", &lightPos);

	ID3D11SamplerState* LinearClamp = g_objStates.LinearClamp();
	m_pShadowShader->PSSetShaderResources(TU_DIFFUSE, gameObject.GetTexture());
	m_pShadowShader->PSSetShaderResources(TU_CUBE, depthRT->GetSRView());

	m_deviceContext->PSSetSamplers(0, 1, &LinearClamp);
	m_deviceContext->PSSetSamplers(1, 1, &LinearClamp);
	m_pShadowShader->PSSetConstantBuffers("ambientColor", &ambientColor);
	m_pShadowShader->PSSetConstantBuffers("diffuseColor", &diffuseColor);

	gameObject.SetMaterial(m_pShadowShader);
	gameObject.Render();

	mWorld = Matrix::CreateScale(3, 3, 3)*Matrix::CreateTranslation(0, 3, 0);
	m_pShadowShader->VSSetConstantBuffers("worldMatrix", &mWorld);
	m_pShadowShader->VSSetConstantBuffers("viewMatrix", &mView);
	m_pShadowShader->VSSetConstantBuffers("projectionMatrix", &mProj);
	m_pShadowShader->VSSetConstantBuffers("lightViewMatrix", &lightViewMatrix);
	m_pShadowShader->VSSetConstantBuffers("lightProjectionMatrix", &lightProjectionMatrix);
	m_pShadowShader->VSSetConstantBuffers("lightPosition", &lightPos);
	m_pShadowShader->PSSetShaderResources(TU_DIFFUSE, gameSphereObject.GetTexture());
	m_pShadowShader->PSSetShaderResources(TU_CUBE, depthRT->GetSRView());

	m_deviceContext->PSSetSamplers(0, 1, &LinearClamp);
	m_deviceContext->PSSetSamplers(1, 1, &LinearClamp);
	m_pShadowShader->PSSetConstantBuffers("ambientColor", &ambientColor);
	m_pShadowShader->PSSetConstantBuffers("diffuseColor", &diffuseColor);

	gameSphereObject.SetMaterial(m_pShadowShader);
	gameSphereObject.Render();





	Vector3 eyePos = cameraNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	cameraScreen->DrawDebugGeometry(mView*mProj);
	SkyBoxPtr->Render(mWorld*mView*mProj);

	SwapChainPtr->Begin();
	// apply FXAA
	TurnZBufferOff();
	if (m_fxaaEnabled)
	{
		MaterialPtr pFXAAShader = g_objMaterial.GetShader("HLSL\\FXAA.hlsl");
		m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		float frameWidth = (float)mClientWidth;
		float frameHeight = (float)mClientHeight;
		Vector4  vFxaa = Vector4(1.0f / frameWidth, 1.0f / frameHeight, 0.0f, 0.0f);

		pFXAAShader->VSSetConstantBuffers("RCPFrame", &vFxaa);
		pFXAAShader->PSSetConstantBuffers("RCPFrame", &vFxaa);

		pFXAAShader->PSSetShaderResources(TU_DIFFUSE, colorRT->GetSRView());
		pFXAAShader->Apply();
		m_deviceContext->Draw(3, 0);
	}
	else
	{
		g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, colorRT->GetSRView());
	}

	ShowRT();
	SwapChainPtr->Flip();
}

void ShadowSample::RenderRT()
{
	depthRT->Begin();
	Matrix wordMatrix, lightViewMatrix, lightProjectionMatrix;
	if (cameraScreen)
	{
		lightViewMatrix = cameraScreen->GetView();
		lightProjectionMatrix = cameraScreen->GetProjection();
	}
	wordMatrix = Matrix::CreateScale(3, 3, 3);

	gameObject.SetMaterial(m_pDepthShader);
	m_pDepthShader->VSSetConstantBuffers("worldMatrix", &wordMatrix);
	m_pDepthShader->VSSetConstantBuffers("viewMatrix", &lightViewMatrix);
	m_pDepthShader->VSSetConstantBuffers("projectionMatrix", &lightProjectionMatrix);
	gameObject.Render();

	wordMatrix = Matrix::CreateScale(3, 3, 3)*Matrix::CreateTranslation(0, 3, 0);
	gameSphereObject.SetMaterial(m_pDepthShader);
	m_pDepthShader->VSSetConstantBuffers("worldMatrix", &wordMatrix);
	m_pDepthShader->VSSetConstantBuffers("viewMatrix", &lightViewMatrix);
	m_pDepthShader->VSSetConstantBuffers("projectionMatrix", &lightProjectionMatrix);
	gameSphereObject.Render();
	depthRT->End();
//	depthRT->Save("depth.png");
}

void ShadowSample::ShowRT()
{
	TurnZBufferOff();
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
