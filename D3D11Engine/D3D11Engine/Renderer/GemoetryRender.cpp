#include "GemoetryRender.h"
#include "DeviceManager.h"
#include "D3D11RendererMaterial.h"

GemoetryRender::GemoetryRender()
{
	m_d3dDevice = g_objDeviecManager.GetDevice();
	m_deviceContext = g_objDeviecManager.GetImmediateContext();
}

GemoetryRender::~GemoetryRender()
{
	SAFE_RELEASE(m_VB);
	SAFE_RELEASE(m_IB);
}

bool GemoetryRender::BuildBuffers(const GeoGen::MeshData& mesh)
{
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = sizeof(VertexPositionNormalTangentUTexC) * mesh.vertices.size();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	vertices.resize(mesh.vertices.size());
	float Infinity = FLT_MAX;
	XMFLOAT3 vMinf3(+Infinity, +Infinity, +Infinity);
	XMFLOAT3 vMaxf3(-Infinity, -Infinity, -Infinity);
	XMVECTOR  vMin = XMLoadFloat3(&vMinf3);
	XMVECTOR vMax = XMLoadFloat3(&vMaxf3);

	for (UINT i = 0; i < mesh.vertices.size(); ++i)
	{
		vertices[i].Position = mesh.vertices[i].pos;
		vertices[i].Normal = mesh.vertices[i].normal;
		vertices[i].TangentU = mesh.vertices[i].tangent;
		vertices[i].TexC = mesh.vertices[i].tex;
		XMVECTOR P = XMLoadFloat3(&vertices[i].Position);
		vMin = XMVectorMin(vMin, P);
		vMax = XMVectorMax(vMax, P);
	}
	D3D11_SUBRESOURCE_DATA vData;
	vData.pSysMem = &vertices[0];
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;
	if (FAILED(m_d3dDevice->CreateBuffer(&desc, &vData, &m_VB)))
	{
		MessageBox(NULL, L"Create Vertex Buffer failed!", L"Error", MB_OK);
		return false;
	}
	D3D11_BUFFER_DESC iDesc = { 0 };
	iDesc.ByteWidth = sizeof(UINT) * mesh.indices.size();
	iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iDesc.Usage = D3D11_USAGE_DEFAULT;
	indices.resize(mesh.indices.size());
	for (UINT i = 0; i < mesh.indices.size(); ++i)
	{
		indices[i] = mesh.indices[i];
	}
	D3D11_SUBRESOURCE_DATA iData;
	iData.pSysMem = &indices[0];
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;
	if (FAILED(m_d3dDevice->CreateBuffer(&iDesc, &iData, &m_IB)))
	{
		MessageBox(NULL, L"Create Index Buffer failed!", L"Error", MB_OK);
		return false;
	}

	XMFLOAT3 Center;            // Center of the box.
	XMFLOAT3 Extents;           // Distance from the center to each side.
	XMStoreFloat3(&m_BoundingBox.Center, 0.5f*(vMin + vMax));
	XMStoreFloat3(&m_BoundingBox.Extents, 0.5f*(vMax - vMin));
	return true;
}

void GemoetryRender::render(D3D11RendererMaterial* pMaterial)
{
	m_deviceContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->IASetInputLayout(pMaterial->getLayout<VertexPositionNormalTangentUTexC>());
	UINT stride = sizeof(VertexPositionNormalTangentUTexC);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset);
	m_deviceContext->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0);
	if (indices.size() <= 0)
	{
		m_deviceContext->Draw(vertices.size(), 0);
	}
	else
	{
		m_deviceContext->DrawIndexed(indices.size(), 0, 0);
	}

}


