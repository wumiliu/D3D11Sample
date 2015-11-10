#pragma once
#include "HpD3D9Type.h"
#include "BaseCode/GeometryGens.h"
#include "VertexTypes.h"
class D3D11RendererMaterial;
class GemoetryRender
{
public:
	GemoetryRender();
	~GemoetryRender();
	bool BuildBuffers(const GeoGen::MeshData& mesh);
	void         render(D3D11RendererMaterial* pMaterial);
private:
	std::vector<VertexPositionNormalTangentUTexC> vertices;
	std::vector<UINT> indices;
protected:

	BoundingBox    m_BoundingBox;

	ID3D11Buffer	*m_VB;
	ID3D11Buffer	*m_IB;
	ID3D11Device			*m_d3dDevice;				//D3D11设备
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文

};

