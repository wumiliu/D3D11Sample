#include "FXAASample.h"
#include "SampleBase.h"

SAMPLE_CPP(FXAASample)
{
	m_fxaaEnabled = true;
}

FXAASample::~FXAASample()
{

}

void FXAASample::InitResource()
{
	Sample::InitResource();
	colorRT = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM);
}

void FXAASample::DrawScene()
{
	SwapChainPtr->Begin();
	ID3D11RenderTargetView* pRTV = SwapChainPtr->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = SwapChainPtr->GetDepthStencilView();
	if (m_fxaaEnabled)
	{
		pRTV = colorRT->GetRTView();
	}
	float ClearColor[4] = { sqrt(0.25f), sqrt(0.25f), sqrt(0.5f), 0.0f };
	m_deviceContext->ClearRenderTargetView(pRTV, ClearColor);
	m_deviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
	// Rebind to original back buffer and depth buffer
	ID3D11RenderTargetView * pRTVs[2] = { pRTV, NULL };

	if (m_fxaaEnabled)
	{
		pRTVs[0] = colorRT->GetRTView();
	}

	m_deviceContext->OMSetRenderTargets(1, pRTVs, pDSV);



	RenderSample();

	// apply FXAA
	if (m_fxaaEnabled)
	{
		SwapChainPtr->Begin();
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
		ShowRT();

	}
	else
	{

	}
	SwapChainPtr->Flip();
	
}

void FXAASample::ShowRT()
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

