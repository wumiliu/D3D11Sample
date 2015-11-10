#pragma once
#include "HpD3D9Type.h"

class RenderTarget2D
{
public:
	RenderTarget2D(int Width,int Height, DXGI_FORMAT Format);
	~RenderTarget2D();
	ID3D11ShaderResourceView* GetSRView(){ return mSRV; }
	ID3D11RenderTargetView* GetRTView(){ return mRTV; }
	void Save(const char* fileName);

private:
	ID3D11Texture2D* mTexture2D;
	ID3D11RenderTargetView* mRTV;
	ID3D11ShaderResourceView* mSRV;

};

