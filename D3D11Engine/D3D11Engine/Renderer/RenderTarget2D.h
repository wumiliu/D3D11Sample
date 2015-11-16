#pragma once
#include "HpD3D9Type.h"
/************************************************************************/
/* 
DXGI_FORMAT_R8G8B8A8_UNORM：每个元素包含 4 个 8 位无符号整数分量，分量的取值范围在[0, 1] 区间 内

DXGI_FORMAT_R32G32B32A32_FLOAT
包含 4 个浮点分量，可以存储一个使用浮点坐标的 3D 向量（而不一定是颜色向量）

*/
/************************************************************************/
class RenderTarget2D
{
public:
	RenderTarget2D(int Width, int Height, DXGI_FORMAT Format, bool bDepth =false);
	~RenderTarget2D();
	
	ID3D11RenderTargetView* GetRTView(){ return mRTV; }
	ID3D11DepthStencilView* GetDSView(){ return mDSV; }
	//不能同时把RT绑定到管线，又把RT视图绑定到另一个RT上，会有警告
	ID3D11ShaderResourceView* GetSRView();

	void Begin();

	void End();
	void SetBackBufferRenderTarget();

	void Save(const char* fileName);

private:
	ID3D11Texture2D* mTexture2D;
	ID3D11Texture2D* mTextureShader2D;
	ID3D11RenderTargetView* mRTV;
	ID3D11ShaderResourceView* mSRV;
	D3D11_VIEWPORT mViewport;
	ID3D11DepthStencilView* mDSV;
	ID3D11RenderTargetView	*m_renderTargetView;		//渲染对象视图
	ID3D11DepthStencilView	*m_depthStencilView;		//深度/模板视图
};

