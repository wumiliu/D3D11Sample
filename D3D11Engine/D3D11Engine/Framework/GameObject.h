#pragma once
#include "HpD3D9Type.h"
enum GEOMETRY_TYPE
{
	GEOMETRY_TYPE_BOX,
	GEOMETRY_TYPE_SPHERE,
	GEOMETRY_TYPE_GRID,
	GEOMETRY_TYPE_BOX_EX,
};

class GameObject
{
public:
	GameObject();
	bool GetInitState(){ return m_bInitState; }
	void InitResource(GEOMETRY_TYPE type = GEOMETRY_TYPE_BOX);
	void SetTexture(const char* pszName);
	void SetLightBuffer(Vector3 lightPosition, Vector4 ambientColor, Vector4 diffuseColor);
	void Render(Matrix world, Matrix view, Matrix proj, Matrix lightViewMatrix,
		Matrix lightProjectionMatrix, ID3D11ShaderResourceView* depthMapTexture);
	void Render(Matrix world, Matrix view, Matrix proj, bool bTest = false);
	void SetMaterial(std::shared_ptr<class D3D11RendererMaterial> material);
	void SetPosition(Vector3 pos){ m_Pos = pos; }
	Vector3 GetPos(){ return m_Pos; }
	Vector3 Pick(DirectX::SimpleMath::Ray ray);
private:
	std::shared_ptr<class GemoetryRender> GemoetryRenderPtr;
	std::shared_ptr<class D3D11RendererMaterial> m_MaterialPtr;
	std::string m_strName;
	Vector3 m_Pos;
	bool m_bInitState;


};