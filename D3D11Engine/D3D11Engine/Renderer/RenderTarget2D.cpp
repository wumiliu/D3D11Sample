#include "RenderTarget2D.h"
#include "DeviceManager.h"
#include "BaseCode/Texture/TextureMgr.h"
RenderTarget2D::RenderTarget2D(int Width, int Height, DXGI_FORMAT Format, bool bDepth)
{
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = Width;
	texDesc.Height = Height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Format = Format;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;
	ID3D11Device* pd3dDevice = g_objDeviecManager.GetDevice();
	pd3dDevice->CreateTexture2D(&texDesc, 0, &mTexture2D);

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2DArray.ArraySize = 1;
	rtvDesc.Texture2DArray.MipSlice = 0;


	rtvDesc.Texture2DArray.FirstArraySlice = 0;
	pd3dDevice->CreateRenderTargetView(mTexture2D, &rtvDesc, &mRTV);


	mDSV = NULL;

	if (bDepth)
	{
		D3D11_TEXTURE2D_DESC depthTexDesc;
		depthTexDesc.Width = Width;
		depthTexDesc.Height = Height;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;

		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		ID3D11Texture2D* depthTex = 0;
		pd3dDevice->CreateTexture2D(&depthTexDesc, 0, &depthTex);

		// Create the depth stencil view for the entire cube
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Format = depthTexDesc.Format;
		dsvDesc.Flags = 0;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		pd3dDevice->CreateDepthStencilView(depthTex, &dsvDesc, &mDSV);
		SAFE_RELEASE(depthTex);

	}

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = static_cast<UINT>(Width);
	desc.Height = static_cast<UINT>(Height);
	desc.MipLevels = static_cast<UINT>(1);
	desc.ArraySize = static_cast<UINT>(1);
	desc.Format = texDesc.Format;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;

	desc.BindFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	HRESULT hr = pd3dDevice->CreateTexture2D(&desc, NULL, &mTextureShader2D);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	memset(&SRVDesc, 0, sizeof(SRVDesc));
	SRVDesc.Format = texDesc.Format;
	SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;
	pd3dDevice->CreateShaderResourceView(mTextureShader2D, &SRVDesc, &mSRV);

	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;
	mViewport.Width = (float)Width;
	mViewport.Height = (float)Height;
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
}


RenderTarget2D::~RenderTarget2D()
{
	SAFE_RELEASE(mRTV);
	SAFE_RELEASE(mSRV);
	SAFE_RELEASE(mTexture2D);
	SAFE_RELEASE(mDSV);
	SAFE_RELEASE(mTextureShader2D);

}

void RenderTarget2D::Save(const char* fileName)
{
	g_objTextureMgr.Save(mTexture2D, fileName);
}

void RenderTarget2D::Begin()
{
	m_renderTargetView = NULL;
	m_depthStencilView = NULL;
	ID3D11DeviceContext* deviceContext = g_objDeviecManager.GetImmediateContext();

	deviceContext->OMGetRenderTargets(1, &m_renderTargetView, &m_depthStencilView);
	deviceContext->RSSetViewports(1, &mViewport);
	if (mDSV != NULL)
	{
		deviceContext->OMSetRenderTargets(1, &mRTV, mDSV);
		deviceContext->ClearDepthStencilView(mDSV, D3D10_CLEAR_DEPTH, 1.0f, 0);
	}
	else
	{
		if (m_depthStencilView != NULL)
		{
			deviceContext->ClearDepthStencilView(m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
		}
		deviceContext->OMSetRenderTargets(1, &mRTV, m_depthStencilView);
	}

	float color[4];
	color[0] = 0.1921568627450980392156862745098f;
	color[1] = 0.30196078431372549019607843137255f;
	color[2] = 0.47450980392156862745098039215686f;
	color[3] = 1.0f;

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 0.0f;
	// Clear the back buffer.
	deviceContext->ClearRenderTargetView(mRTV, color);
	// Clear the depth buffer.
	
}

void RenderTarget2D::End()
{
	SetBackBufferRenderTarget();
}

void RenderTarget2D::SetBackBufferRenderTarget()
{
	ID3D11DeviceContext* deviceContext = g_objDeviecManager.GetImmediateContext();
	ID3D11RenderTargetView* NullRt[1] = { NULL };
	deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
	}
	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
	}
}

ID3D11ShaderResourceView* RenderTarget2D::GetSRView()
{
	g_objDeviecManager.GetImmediateContext()->CopyResource(mTextureShader2D, mTexture2D);
	return mSRV;
}
