#include "LightSample.h"
#include "SampleBase.h"

SAMPLE_CPP(LightSample)
{

}

LightSample::~LightSample()
{

}

void LightSample::InitResource()
{
	Sample::InitResource();
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM,true);
}

void LightSample::DrawScene()
{
	SwapChainPtr->TurnZBufferOff();
	SwapChainPtr->Begin();
	g_objSprite.ShowTexture(20, 20, "Data\\Texture\\wall01.dds");
	ID3D11ShaderResourceView* pSrv;
	pSrv = SwapChainPtr->GetResourceView();

	ID3D11RenderTargetView* pRTV0 = colorRT->GetRTView();
	ID3D11RenderTargetView* renderTargets[1] = { pRTV0 };
	m_deviceContext->OMSetRenderTargets(1, renderTargets, colorRT->GetDSView());
	g_objSprite.ShowTexture(20, 20, "Data\\Texture\\wall01.dds");
	g_objSprite.ShowRect(400, 400, 500, 500, { 0, 0, 1, 0 }, mTimer.TotalTime());
	g_objSprite.DrawCircle(100, 100, 50, { 0, 1, 0, 1 });
	g_objSprite.ShowTexture(0, 0, 100, 100, pSrv);

	SwapChainPtr->Begin();
	pSrv = colorRT->GetSRView();
	g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, pSrv);


	SwapChainPtr->Flip();
}

void LightSample::RenderRT()
{
	ID3D11RenderTargetView* pRTV0 = colorRT->GetRTView();
	ID3D11RenderTargetView* renderTargets[1] = { pRTV0 };
	m_deviceContext->OMSetRenderTargets(1, renderTargets, colorRT->GetDSView());
	colorRT->Begin();
	g_objSprite.ShowTexture(20, 20, "Data\\Texture\\wall01.dds");
	g_objSprite.ShowRect(400, 400, 500, 500, { 0, 0, 1, 0 }, mTimer.TotalTime());
	g_objSprite.DrawCircle(100, 100, 50, { 0, 1, 0, 1 });

}
