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
	m_pFillGBufShader = g_objMaterial.GetShader("HLSL\\FillGBuffer.hlsl");
	m_pComplexMaskShader = g_objMaterial.GetShader("HLSL\\ComplexMask.hlsl");
	m_pLightingShader = g_objMaterial.GetShader("HLSL\\Lighting.hlsl");


	Sample::InitResource();
	m_TexGBuffer = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_TexGBuffer2 = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_TexGBufResolved2 = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R16_UINT);
	m_TexCoverageMask = std::make_shared<RenderTarget2D>(mClientWidth, mClientHeight, DXGI_FORMAT_R16G16B16A16_FLOAT);

}

void DeferredLighting::DrawScene()
{

	Render();
}

void DeferredLighting::Render()
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}

	ID3D11RenderTargetView* pRTV = SwapChainPtr->GetRenderTargetView();
	ID3D11DepthStencilView*        pDSV = SwapChainPtr->GetDepthStencilView();
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	// Clear the back buffer
	m_deviceContext->ClearRenderTargetView(pRTV, clearColor);
	m_deviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
	{
		// Fill the G-Buffer
		ID3D11RenderTargetView* pGBufRTV[] = { m_TexGBuffer->GetRTView(), m_TexGBuffer2->GetRTView(), m_TexCoverageMask->GetRTView() };
		m_deviceContext->ClearRenderTargetView(pGBufRTV[0], clearColor);
		m_deviceContext->ClearRenderTargetView(pGBufRTV[1], clearColor);
		m_deviceContext->ClearRenderTargetView(pGBufRTV[2], clearColor);

		m_deviceContext->OMSetRenderTargets(3, pGBufRTV, pDSV);
		m_deviceContext->OMSetDepthStencilState(NULL, 0);
		Vector3 vDiffuse = { 0.745100021f, 0.709800005f, 0.674499989f };
		int bTextured = 1;
		m_pFillGBufShader->PSSetConstantBuffers("DiffuseColor", &vDiffuse);
		m_pFillGBufShader->PSSetConstantBuffers("bTextured", &bTextured);

		gameObject.SetMaterial(m_pFillGBufShader);
		
		gameObject.Render(Matrix::CreateScale(5, 5, 5), mView, mProj);
		gameSphereObject.SetMaterial(m_pFillGBufShader);
		gameSphereObject.Render(Matrix::CreateScale(3, 3, 3), mView, mProj);

		ID3D11RenderTargetView* pClearRTV[] = { NULL, NULL, NULL };
		m_deviceContext->OMSetRenderTargets(3, pClearRTV, NULL);

	/*	m_deviceContext->IASetInputLayout(m_pDefaultInputLayout);
		m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->VSSetShader(m_pFillGBufVertexShader, NULL, 0);
		m_deviceContext->PSSetShader(m_pFillGBufPixelShader, NULL, 0);

		m_deviceContext->PSSetSamplers(0, 1, &m_pTextureSampler);

*/

		// Calculate lighting
		m_deviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
		m_deviceContext->OMSetRenderTargets(1, &pRTV, pDSV);

		SwapChainPtr->Begin();
		//ShowRT();
	//	g_objSprite.ShowTexture(0, 0, mClientWidth, mClientHeight, m_TexGBuffer2->GetSRView());
		ShowFXAA();
		SwapChainPtr->Flip();

	}


}

void DeferredLighting::ShowRT()
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
	g_objSprite.ShowTexture(x, y, x + w, y + h, m_TexGBuffer2->GetSRView());
}

void DeferredLighting::ShowFXAA()
{
	MaterialPtr pFXAAShader = g_objMaterial.GetShader("HLSL\\FXAA.hlsl");
	m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	float frameWidth = (float)mClientWidth;
	float frameHeight = (float)mClientHeight;
	Vector4  vFxaa = Vector4(1.0f / frameWidth, 1.0f / frameHeight, 0.0f, 0.0f);

	pFXAAShader->VSSetConstantBuffers("RCPFrame", &vFxaa);
	pFXAAShader->PSSetConstantBuffers("RCPFrame", &vFxaa);


	pFXAAShader->PSSetShaderResources(TU_DIFFUSE, m_TexGBuffer2->GetSRView());
	pFXAAShader->Apply();
	m_deviceContext->Draw(3, 0);

}
