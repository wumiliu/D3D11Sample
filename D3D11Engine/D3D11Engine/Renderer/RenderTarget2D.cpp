#include "RenderTarget2D.h"
#include "DeviceManager.h"
#include "BaseCode/Texture/TextureMgr.h"
RenderTarget2D::RenderTarget2D(int Width, int Height, DXGI_FORMAT Format)
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

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	memset(&SRVDesc, 0, sizeof(SRVDesc));
	SRVDesc.Format = texDesc.Format;
	SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;
	pd3dDevice->CreateShaderResourceView(mTexture2D, &SRVDesc, &mSRV);


}


RenderTarget2D::~RenderTarget2D()
{
	SAFE_RELEASE(mRTV);
	SAFE_RELEASE(mSRV);
	SAFE_RELEASE(mTexture2D);
}

void RenderTarget2D::Save(const char* fileName)
{
	g_objTextureMgr.Save(mTexture2D, fileName);
}
