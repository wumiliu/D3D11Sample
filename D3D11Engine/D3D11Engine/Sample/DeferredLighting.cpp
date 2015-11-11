#include "DeferredLighting.h"
#include "SampleBase.h"


SAMPLE_CPP(DeferredLighting)
{

}


DeferredLighting::~DeferredLighting()
{
}

void DeferredLighting::InitResource()
{
	RendererMaterialDesc desc;
	desc.strHLSLPath = "HLSL\\Skybox.hlsl";
	m_MaterialMulitPoint = std::make_shared<D3D11RendererMaterial>(desc);

	desc.strHLSLPath = "HLSL\\Skybox.hlsl";
	m_MaterialDeferred = std::make_shared<D3D11RendererMaterial>(desc);

	desc.strHLSLPath = "HLSL\\ClearGBuffer.hlsl";
	m_MaterialGBuffer = std::make_shared<D3D11RendererMaterial>(desc);

	desc.strHLSLPath = "HLSL\\Fxaa.hlsl";
	m_MaterialPtr = std::make_shared<D3D11RendererMaterial>(desc);


	Sample::InitResource();
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	normalRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	depthRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
	lightRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);

}

void DeferredLighting::DrawScene()
{
	SwapChainPtr->Begin();
	SwapChainPtr->TurnZBufferOn();
	ID3D11RenderTargetView* pRTV0 = colorRT->GetRTView();
	ID3D11RenderTargetView* pRTV1 = normalRT->GetRTView();
	ID3D11RenderTargetView* pRTV2 = depthRT->GetRTView();
	ID3D11RenderTargetView* pRTV3 = lightRT->GetRTView();

	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}
	gameObject.Render(Matrix::CreateScale(5, 5, 5), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(3, 3, 3), mView, mProj);


	Vector3 eyePos = cameraNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	SkyBoxPtr->Render(mWorld*mView*mProj);

	ID3D11RenderTargetView* renderTargets[4] = { pRTV0, pRTV1, pRTV2, pRTV3 };
	m_deviceContext->OMSetRenderTargets(4, renderTargets, SwapChainPtr->GetDepthStencilView());

	ID3D11ShaderResourceView* pSrv = SwapChainPtr->GetResourceView();
	m_MaterialGBuffer->PSSetShaderResources(TU_DIFFUSE, pSrv);
	m_MaterialGBuffer->Apply();
	m_deviceContext->Draw(3, 0);
	g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, pSrv);
	pSrv = colorRT->GetSRView();

	SwapChainPtr->Begin();
	m_MaterialPtr->PSSetShaderResources(TU_DIFFUSE, pSrv);
	m_MaterialPtr->Apply();
	m_deviceContext->Draw(3, 0);
	SwapChainPtr->Flip();

}
