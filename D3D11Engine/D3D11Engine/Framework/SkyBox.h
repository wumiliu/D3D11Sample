#pragma once
#include "HpD3D9Type.h"


class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	void InitResource();
	void Render(Matrix MVP,bool bTest = false);
private:
	std::shared_ptr<class GemoetryRender> GemoetryRenderPtr;
	std::shared_ptr<class D3D11RendererMaterial> m_MaterialPtr;
	ID3D11ShaderResourceView* m_pSrv;

};

