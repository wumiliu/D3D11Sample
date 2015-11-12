#include "GameObject.h"
#include "Renderer/D3D11RendererMaterial.h"
#include "Renderer/GemoetryRender.h"
#include "Basecode/DXFunction.h"
#include "Renderer/DeviceManager.h"
#include "Renderer/CommonStates.h"
#include "BaseCode/Texture/TextureMgr.h"
#include "Renderer/DeviceManager.h"

GameObject::GameObject()
{
	m_strName = "";
	m_bInitState = false;
	//	_CrtSetBreakAlloc(531); // 设置在第几次内存分配的时候程序暂停执行，并回复现场

	//_CrtDumpMemoryLeaks(); // 检查当前有哪些内存没有释放.
}

void GameObject::SetMaterial(std::shared_ptr<class D3D11RendererMaterial> material)
{
	m_MaterialPtr = material;
}

void GameObject::InitResource(GEOMETRY_TYPE type)
{
	RendererMaterialDesc desc;
	desc.strHLSLPath = "HLSL\\GameObject.hlsl";
	m_MaterialPtr = std::make_shared<D3D11RendererMaterial>(desc);
	GemoetryRenderPtr = std::make_shared<GemoetryRender>();

	GeoGen::MeshData meshData;
	switch (type)
	{
	case GEOMETRY_TYPE_BOX:
	{
		GeoGen::CreateBox(2, 2, 2, meshData);

	}
	break;
	case GEOMETRY_TYPE_SPHERE:
	{
		GeoGen::CreateSphere(1, 50, 50, meshData);

	}
	break;
	case GEOMETRY_TYPE_GRID:
	{
		GeoGen::CreateGrid(20.0f, 20.0f, 20, 20, meshData);
	}
	break;
	case GEOMETRY_TYPE_BOX_EX:
	{
		GeoGen::CreateBox(10, 1, 1, meshData);
	}
	break;
	}
	bool bBuild = GemoetryRenderPtr->BuildBuffers(meshData);
	m_bInitState = true;


}

void GameObject::SetTexture(const char* pszName)
{
	m_strName = pszName;
}

void GameObject::Render(Matrix world, Matrix view, Matrix proj, bool bTest)
{
	ID3D11DeviceContext* pImmediateContext = g_objDeviecManager.GetImmediateContext();
	m_MaterialPtr->VSSetConstantBuffers("worldMatrix", &world);
	if (!bTest)
	{
		m_MaterialPtr->VSSetConstantBuffers("viewMatrix", &view);
		m_MaterialPtr->VSSetConstantBuffers("projectionMatrix", &proj);
	}

	CTexture* pTexture = g_objTextureMgr.GetTexture(m_strName);
	if (pTexture)
	{
		ID3D11ShaderResourceView* pSrv = pTexture->GetShaderResourceView();
		m_MaterialPtr->PSSetShaderResources(TU_DIFFUSE, pSrv);

		ID3D11SamplerState* LinearWrap = g_objStates.LinearWrap();
		pImmediateContext->PSSetSamplers(TU_DIFFUSE, 1, &LinearWrap);
		//pImmediateContext->OMSetDepthStencilState(g_objStates.DepthDefault(), 1);
		//pImmediateContext->RSSetState(g_objStates.CullNone());
		FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };// 0xFFFFFFFF
		//pImmediateContext->OMSetBlendState(g_objStates.AlphaBlend(), BlendFactor, 0xFFFFFFFF);
	}
	m_MaterialPtr->Apply();
	GemoetryRenderPtr->render(m_MaterialPtr.get());
}



void GameObject::SetLightBuffer(Vector3 lightPosition, Vector4 ambientColor, Vector4 diffuseColor)
{
	m_MaterialPtr->VSSetConstantBuffers("lightPosition", &lightPosition);
	m_MaterialPtr->PSSetConstantBuffers("ambientColor", &ambientColor);
	m_MaterialPtr->PSSetConstantBuffers("diffuseColor", &diffuseColor);

}


