#include "DeferredLight.h"

#include "SampleBase.h"
#include "BaseCode/Texture/TextureMgr.h"


SAMPLE_CPP(DeferredLight)
{
	m_fxaaEnabled = false;
}

DeferredLight::~DeferredLight()
{
}

void DeferredLight::InitResource()
{
	Sample::InitResource();
//	cameraNode_->SetPosition(Vector3(0.0f, 2.0f, -45.0f));
	cameraNode_->SetPosition(Vector3(0.0f, 25.0f, -45));
	pitch_ = 30.0f;
	Quaternion q = Quaternion::CreateFromEulerAngles(pitch_, 0.0f, 0.0f);
	cameraNode_->SetRotation(q);
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, true);
	normalRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	depthRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R32_FLOAT);
	lightRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	lightRTEx = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);


	clearBufferEffect = g_objMaterial.GetShader("HLSL\\Deferred\\ClearGBuffer.hlsl");
	renderGBuffer = g_objMaterial.GetShader("HLSL\\Deferred\\RenderGBuffer.hlsl");

	pointLightEffect = g_objMaterial.GetShader("HLSL\\Deferred\\PointLight.hlsl");

	directionalLightEffect = g_objMaterial.GetShader("HLSL\\Deferred\\DirectionalLight.hlsl");
	finalCombineEffect = g_objMaterial.GetShader("HLSL\\Deferred\\CombineFinal.hlsl");

}

void DeferredLight::ClearGBuffer()
{
	clearBufferEffect->Apply();
	m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);
	TurnZBufferOff();
	m_deviceContext->Draw(3, 0);

}
void DeferredLight::UpdateScene(float fTotalTime, float fDeltaTime)
{
	Sample::UpdateScene(fTotalTime, fDeltaTime);
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
void DeferredLight::DrawScene()
{
	SwapChainPtr->Begin();

	ID3D11RenderTargetView* pRTV = SwapChainPtr->GetRenderTargetView();
	ID3D11DepthStencilView*   pDSV = SwapChainPtr->GetDepthStencilView();

	// Fill the G-Buffer
	ID3D11RenderTargetView* pGBufRTV[] = { colorRT->GetRTView(), normalRT->GetRTView(), depthRT->GetRTView() };
	m_deviceContext->OMSetRenderTargets(3, pGBufRTV, pDSV);

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float clearColor1[4] = { 0.1921568627450980392156862745098f, 0.30196078431372549019607843137255f, 0.47450980392156862745098039215686f, 1.0f };


	m_deviceContext->ClearRenderTargetView(pGBufRTV[0], clearColor);
	m_deviceContext->ClearRenderTargetView(pGBufRTV[1], clearColor);
	m_deviceContext->ClearRenderTargetView(pGBufRTV[2], clearColor);
	ClearGBuffer();
	RenderScene();
	DrawLights(mTimer.TotalTime());


	lightRTEx->Begin();
	finalCombineEffect->PSSetShaderResources(TU_DIFFUSE, colorRT->GetSRView());
	finalCombineEffect->PSSetShaderResources(TU_CUBE, lightRT->GetSRView());
	ID3D11SamplerState* LinearClamp = g_objStates.LinearClamp();
	m_deviceContext->PSSetSamplers(TU_DIFFUSE, 1, &LinearClamp);
	m_deviceContext->PSSetSamplers(TU_CUBE, 1, &LinearClamp);
	finalCombineEffect->Apply();

	m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);
	m_deviceContext->RSSetState(g_objStates.CullCounterClockwise());
	TurnZBufferOff();
	m_deviceContext->Draw(3, 0);

	lightRTEx->End();

	SwapChainPtr->Begin();
	int halfWidth = mClientWidth / 2;
	int halfHeight = mClientHeight / 2;
	TurnZBufferOff();
	g_objSprite.SetAlphaBlend(false);
	g_objSprite.ShowTexture(0, 0, halfWidth, halfHeight, colorRT->GetSRView());
	g_objSprite.ShowTexture(0, halfHeight, halfWidth, mClientHeight, normalRT->GetSRView());
	g_objSprite.ShowTexture(halfWidth, 0, mClientWidth, halfHeight, lightRT->GetSRView());
	g_objSprite.ShowTexture(halfWidth, halfHeight, mClientWidth, mClientHeight, lightRTEx->GetSRView());

	if (m_fxaaEnabled)
	{
		MaterialPtr pFXAAShader = g_objMaterial.GetShader("HLSL\\FXAA.hlsl");
		m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		float frameWidth = (float)mClientWidth;
		float frameHeight = (float)mClientHeight;
		Vector4  vFxaa = Vector4(1.0f / frameWidth, 1.0f / frameHeight, 0.0f, 0.0f);

		pFXAAShader->VSSetConstantBuffers("RCPFrame", &vFxaa);
		pFXAAShader->PSSetConstantBuffers("RCPFrame", &vFxaa);

		pFXAAShader->PSSetShaderResources(TU_DIFFUSE, lightRTEx->GetSRView());
		pFXAAShader->Apply();
		m_deviceContext->Draw(3, 0);
	}
	else
	{
		g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, lightRTEx->GetSRView());
	}


	SwapChainPtr->Flip();

}

void DeferredLight::RenderScene()
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}
	TurnZBufferOn();
	m_deviceContext->RSSetState(g_objStates.CullCounterClockwise());
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);

	gameObject.SetMaterial(renderGBuffer);
	gameObject.SetTexture("");

	ID3D11SamplerState* LinearWrap = g_objStates.LinearWrap();

	renderGBuffer->PSSetShaderResources(TU_DIFFUSE, g_objTextureMgr.CreateTexture("Data\\Texture\\ground_diffuse.jpg"));
	renderGBuffer->PSSetShaderResources(TU_CUBE, g_objTextureMgr.CreateTexture("Data\\Texture\\ground_specular.jpg"));
	renderGBuffer->PSSetShaderResources(TU_NORMAL, g_objTextureMgr.CreateTexture("Data\\Texture\\ground_normal.jpg"));
	m_deviceContext->PSSetSamplers(TU_DIFFUSE, 1, &LinearWrap);
	m_deviceContext->PSSetSamplers(TU_CUBE, 1, &LinearWrap);
	m_deviceContext->PSSetSamplers(TU_NORMAL, 1, &LinearWrap);


	gameObject.Render(Matrix::CreateScale(5, 5, 5)*Matrix::CreateTranslation(0, 0, 0), mView, mProj);
	
	gameSphereObject.SetMaterial(renderGBuffer);
	gameSphereObject.SetTexture("");
	Matrix rotate = Matrix::CreateRotationY(XM_PI / 3 * mTimer.TotalTime());
	renderGBuffer->PSSetShaderResources(TU_DIFFUSE, g_objTextureMgr.CreateTexture("Data\\Texture\\wall01.dds"));
	//renderGBuffer->PSSetShaderResources(TU_CUBE, g_objTextureMgr.CreateTexture("Data\\Texture\\null_specular.tga"));
	//renderGBuffer->PSSetShaderResources(TU_NORMAL, g_objTextureMgr.CreateTexture("Data\\Texture\\null_normal.tga"));
	gameSphereObject.Render(Matrix::CreateScale(10, 10, 10)* rotate* Matrix::CreateTranslation(0, 10, 0), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(10, 10, 10)* rotate*Matrix::CreateTranslation(20, 10, 0), mView, mProj);

	gameSphereObject.Render(Matrix::CreateScale(10, 10, 10)* rotate*Matrix::CreateTranslation(0, 10, 20), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(10, 10, 10)*rotate* Matrix::CreateTranslation(0, 10, 40), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(10, 10, 10)* rotate*Matrix::CreateTranslation(20, 10, 20), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(10, 10, 10)* rotate*Matrix::CreateTranslation(20, 10, 40), mView, mProj);


}

void DeferredLight::DrawLights(float gameTime)
{
	using namespace DirectX::SimpleMath;
	Color colors[12];

	colors[0] = static_cast<XMVECTOR>(DirectX::Colors::Red);
	colors[1] = static_cast<XMVECTOR>(DirectX::Colors::Blue);
	colors[2] = static_cast<XMVECTOR>(DirectX::Colors::IndianRed);
	colors[3] = static_cast<XMVECTOR>(DirectX::Colors::CornflowerBlue);
	colors[4] = static_cast<XMVECTOR>(DirectX::Colors::Gold);
	colors[5] = static_cast<XMVECTOR>(DirectX::Colors::Green);
	colors[6] = static_cast<XMVECTOR>(DirectX::Colors::Crimson);
	colors[7] = static_cast<XMVECTOR>(DirectX::Colors::SkyBlue);
	colors[8] = static_cast<XMVECTOR>(DirectX::Colors::Red);
	colors[9] = static_cast<XMVECTOR>(DirectX::Colors::ForestGreen);
	colors[10] = static_cast<XMVECTOR>(DirectX::Colors::White);
	colors[11] = static_cast<XMVECTOR>(DirectX::Colors::Wheat);

	float angle = (float)gameTime;
	lightRT->Begin();
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	m_deviceContext->OMSetBlendState(g_objStates.AlphaBlend(), BlendFactor, 0xFFFFFFFF);
	TurnZBufferOff();//πÿ±’…Ó∂»
	Color lightColor = static_cast<XMVECTOR>(DirectX::Colors::SkyBlue);
	DrawDirectionalLight(Vector3(0, -1, 1), lightColor);

	int n = 15;
	SetDefaultPoint();
	for (int i = 0; i < n; i++)
	{
		Vector3 pos = Vector3((float)sinf(i * TwoPi / n + angle), 0.30f, (float)cosf(i * TwoPi / n + angle));
		DrawPointLight(pos * 40, colors[i % 10], 15, 2);

		pos = Vector3((float)cosf((i + 5) * TwoPi / n - angle), 0.30f, (float)sinf((i + 5) * TwoPi / n - angle));
		DrawPointLight(pos * 20, colors[i % 10], 20, 1);

		pos = Vector3((float)cosf(i * TwoPi / n + angle), 0.10f, (float)sinf(i *TwoPi / n + angle));
		DrawPointLight(pos * 75, colors[i % 10], 45, 2);

		pos = Vector3((float)cosf(i * TwoPi / n + angle), -0.3f, (float)sinf(i * TwoPi / n + angle));
		DrawPointLight(pos * 20, colors[i % 10], 20, 2);
	}
	DrawPointLight(Vector3(0, (float)sinf(angle * 0.8f) * 40, 0), colors[0], 30, 5);

	DrawPointLight(Vector3(0, 25, 0), colors[10], 30, 1);
	DrawPointLight(Vector3(0, 0, 70), colors[11], 55 + 10 * (float)sinf(5 * angle), 3);
	lightRT->End();

}

void DeferredLight::SetDefaultPoint()
{
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}
	gameSphereObject.SetMaterial(pointLightEffect);
	gameSphereObject.SetTexture("");

	ID3D11SamplerState* LinearClamp = g_objStates.LinearClamp();
	ID3D11SamplerState* PointClamp = g_objStates.PointClamp();

	pointLightEffect->PSSetShaderResources(TU_DIFFUSE, colorRT->GetSRView());
	pointLightEffect->PSSetShaderResources(TU_CUBE, depthRT->GetSRView());
	pointLightEffect->PSSetShaderResources(TU_NORMAL, normalRT->GetSRView());
	m_deviceContext->PSSetSamplers(0, 1, &LinearClamp);
	m_deviceContext->PSSetSamplers(1, 1, &PointClamp);
	m_deviceContext->PSSetSamplers(2, 1, &PointClamp);
	pointLightEffect->VSSetConstantBuffers("View", &mView);
	pointLightEffect->VSSetConstantBuffers("Projection", &mProj);
	Vector3 pPos = cameraMain->GetNode()->GetWorldPosition();
	pointLightEffect->PSSetConstantBuffers("cameraPosition", &pPos);
	Matrix ViewProj = mView* mProj;
	Matrix InvViewProj = ViewProj.Invert();
	pointLightEffect->PSSetConstantBuffers("InvertViewProjection", &InvViewProj);
}

void DeferredLight::DrawPointLight(Vector3 lightPosition, Color color, float lightRadius, float lightIntensity)
{
	Matrix sphereWorldMatrix = Matrix::CreateScale(lightRadius) * Matrix::CreateTranslation(lightPosition);

	pointLightEffect->VSSetConstantBuffers("World", &sphereWorldMatrix);


	pointLightEffect->PSSetConstantBuffers("lightPosition", &lightPosition);
	pointLightEffect->PSSetConstantBuffers("Color", &color);
	pointLightEffect->PSSetConstantBuffers("lightRadius", &lightRadius);
	pointLightEffect->PSSetConstantBuffers("lightIntensity", &lightIntensity);



	pointLightEffect->PSSetConstantBuffers("lightIntensity", &lightIntensity);
	Vector3 pPos = cameraMain->GetNode()->GetWorldPosition();
	float cameraToCenter = Vector3::Distance(pPos, lightPosition);

	if (cameraToCenter < lightRadius)
	{
		m_deviceContext->RSSetState(g_objStates.CullClockwise());
	}
	{
		m_deviceContext->RSSetState(g_objStates.CullCounterClockwise());
	}
	gameSphereObject.Render();

}

void DeferredLight::DrawDirectionalLight(Vector3 lightDirection, Color color)
{

	ID3D11SamplerState* LinearClamp = g_objStates.LinearClamp();
	ID3D11SamplerState* PointClamp = g_objStates.PointClamp();

	directionalLightEffect->PSSetShaderResources(TU_DIFFUSE, colorRT->GetSRView());
	directionalLightEffect->PSSetShaderResources(TU_CUBE, depthRT->GetSRView());
	directionalLightEffect->PSSetShaderResources(TU_NORMAL, normalRT->GetSRView());
	m_deviceContext->PSSetSamplers(0, 1, &LinearClamp);
	m_deviceContext->PSSetSamplers(1, 1, &PointClamp);
	m_deviceContext->PSSetSamplers(2, 1, &PointClamp);



	directionalLightEffect->PSSetConstantBuffers("lightDirection", &lightDirection);
	directionalLightEffect->PSSetConstantBuffers("Color", &color);

	Vector3 pPos = cameraMain->GetNode()->GetWorldPosition();
	directionalLightEffect->PSSetConstantBuffers("cameraPosition", &pPos);

	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}

	Matrix ViewProj = mView* mProj;
	Matrix InvViewProj = ViewProj.Invert();
	directionalLightEffect->PSSetConstantBuffers("InvertViewProjection", &InvViewProj);
	directionalLightEffect->Apply();
	m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(3, 0);
}
