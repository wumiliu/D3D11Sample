#include "SkyBox.h"
#include "Renderer/D3D11RendererMaterial.h"
#include "Renderer/GemoetryRender.h"
#include "Basecode/DXFunction.h"
#include "Renderer/DeviceManager.h"
#include "Renderer/CommonStates.h"
SkyBox::SkyBox()
{
	m_pSrv = NULL;
}


SkyBox::~SkyBox()
{
	SAFE_RELEASE(m_pSrv);
}

void SkyBox::InitResource()
{
	RendererMaterialDesc desc;
	desc.strHLSLPath = "HLSL\\Skybox.hlsl";
	m_MaterialPtr = std::make_shared<D3D11RendererMaterial>(desc);
	GemoetryRenderPtr = std::make_shared<GemoetryRender>();

	GeoGen::MeshData meshData;
	GeoGen::CreateSphere(1, 5, 5, meshData);
	GeoGen::CreateBox(1, 1, 1, meshData);

	bool bBuild = GemoetryRenderPtr->BuildBuffers(meshData);
	m_pSrv = D3DX11CreateShaderResourceViewFromFile(g_objDeviecManager.GetDevice(), "Data\\SkyBox\\sunsetcube1024.dds");

}

void SkyBox::Render(Matrix MVP, bool bTest)
{
	ID3D11DeviceContext* pImmediateContext = g_objDeviecManager.GetImmediateContext();

	m_MaterialPtr->VSSetConstantBuffers("MVP", &MVP);
	m_MaterialPtr->PSSetShaderResources(TU_CUBE, m_pSrv);
	ID3D11SamplerState* LinearWrap = g_objStates.LinearWrap();
	pImmediateContext->PSSetSamplers(TU_CUBE, 1, &LinearWrap);

	m_MaterialPtr->Apply();

	
	FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
	pImmediateContext->OMSetBlendState(g_objStates.Opaque(), BlendFactor, 0xFFFFFFFF);
	pImmediateContext->OMSetDepthStencilState(g_objStates.DepthDefault(), 0);
	pImmediateContext->RSSetState(g_objStates.CullClockwise());
	//pImmediateContext->RSSetState(g_objStates.Wireframe());
	GemoetryRenderPtr->render(m_MaterialPtr.get());
	pImmediateContext->RSSetState(0);
}
