#include "Sprite.h"
#include "DeviceManager.h"
#include "BaseCode/DXFunction.h"
#include "MaterialMgr.h"
#include "CommonStates.h"
#include "BaseCode/Texture/TextureMgr.h"
Sprite& Sprite::GetInstance()
{
	static Sprite _instance;
	return *(&_instance);
}


Sprite::Sprite(int initialBufferCapacity /*= 1024*/, int maxBufferSizePerPrimitive /*= 32768*/)
{
	m_strShaderPath = "HLSL\\Sprite.hlsl";
	m_initialBufferCapacity = initialBufferCapacity;
	m_maxBufferSizePerPrimitive = maxBufferSizePerPrimitive;
	m_d3dDevice = g_objDeviecManager.GetDevice();
	m_deviceContext = g_objDeviecManager.GetImmediateContext();
	CreateIndexBuffer(0, 0);
	CreateVertexBuffer(0, 0);
}

Sprite::~Sprite()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);

}

void Sprite::ResetSize(int nWidth, int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void Sprite::CreateIndexBuffer(int nType, int nSize)
{
	D3D11_BUFFER_DESC  indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufferDesc.ByteWidth = sizeof(UINT)* m_initialBufferCapacity;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	HRESULT result = S_FALSE;
	result = m_d3dDevice->CreateBuffer(&indexBufferDesc, NULL, &m_indexBuffer);
	if (FAILED(result))
	{
		return;
	}
}

void Sprite::CreateVertexBuffer(int nType, int nSize)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC; //动态缓存
	vertexBufferDesc.ByteWidth = sizeof(VertexPositionColorTexture)* m_maxBufferSizePerPrimitive;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //CPU 可写
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	HRESULT result = S_FALSE;
	result = m_d3dDevice->CreateBuffer(&vertexBufferDesc, NULL, &m_vertexBuffer);
}

void Sprite::ShowRect(int x1, int y1, int x2, int y2, const XMFLOAT4& color, float dt /*= 0*/)
{
	float x = (float)x1;
	float y = (float)y1;
	float h = (float)y2 - y1;
	float w = (float)x2 - x1;

	XMFLOAT3 LeftTop = XMFLOAT3(x, y, 0.0f);
	XMFLOAT3 RightTop = XMFLOAT3(x + w, y, 0.0f);

	XMFLOAT3 LeftBottom = XMFLOAT3(x, (y + h), 0.0f);
	XMFLOAT3 RightBottom = XMFLOAT3(x + w, (y + h), 0.0f);

	VertexPositionColorTexture vertices[8] =
	{
		//正面的四个点
		{ LeftBottom, color, XMFLOAT2(0, 1) },
		{ LeftTop, color, XMFLOAT2(0, 0) },

		{ LeftTop, color, XMFLOAT2(0, 0) },
		{ RightTop, color, XMFLOAT2(1, 0) },

		{ RightTop, color, XMFLOAT2(1, 0) },
		{ RightBottom, color, XMFLOAT2(1, 1) },

		{ RightBottom, color, XMFLOAT2(1, 1) },
		{ LeftBottom, color, XMFLOAT2(0, 1) }
	};

	XMMATRIX rz = XMMatrixRotationZ(XM_PI *dt);
	//先平移为原点，绕着原点旋转, 转换到平行投影的中点为（w/2,h/2）坐标系。Y 是颠倒的，在旋转
	XMMATRIX rTmp = XMMatrixTranslation(-x, -y, 0.0)* rz * XMMatrixTranslation(x, y, 0.0);

	XMMATRIX toTexSpace = GetShow2DMatrix(m_nWidth, m_nHeight);
	toTexSpace = rTmp * toTexSpace;
	//	m_MaterialPtr->SetbUseGeometry(bDot);
	DrawPrimitiveUP(PRIMITIVE_LINELIST, 8, vertices, toTexSpace, NULL, SpriteType::ONLY_COLOR);
}

void Sprite::ShowBlock(int x1, int y1, int x2, int y2, const XMFLOAT4& color, float dt /*= 0*/)
{
	ShowTexture(x1, y1, x2, y2,NULL,color,dt,ONLY_COLOR);
}
void Sprite::ShowTexture(int x, int y, const char*pszName)
{
	CTexture* pTexture = g_objTextureMgr.GetTexture(pszName);
	if (pTexture)
	{
		ShowTexture(x, y, x + pTexture->GetWidth(), y + pTexture->GetHegith(), pTexture->GetShaderResourceView());
	}
}

void Sprite::ShowTexture(int x1, int y1, int x2, int y2, const char*pszName)
{
	ShowTexture(x1, y1, x2, y2, g_objTextureMgr.CreateTexture(pszName));
}

void Sprite::ShowTexture(int x1, int y1, int x2, int y2, ID3D11ShaderResourceView*pTexture, const XMFLOAT4& color, float dt, SpriteType spriteType)
{
	float x = (float)x1;
	float y = (float)y1;
	float h = (float)y2 - y1;
	float w = (float)x2 - x1;

	XMFLOAT3 LeftTop = XMFLOAT3(x, y, 0.0f);
	XMFLOAT3 RightTop = XMFLOAT3(x + w, y, 0.0f);

	XMFLOAT3 LeftBottom = XMFLOAT3(x, (y + h), 0.0f);
	XMFLOAT3 RightBottom = XMFLOAT3(x + w, (y + h), 0.0f);


	VertexPositionColorTexture vertices[] =
	{
		//正面的四个点
		{ LeftBottom, color, XMFLOAT2(0, 1) },
		{ LeftTop, color, XMFLOAT2(0, 0) },
		{ RightTop, color, XMFLOAT2(1, 0) },
		{ LeftBottom, color, XMFLOAT2(0, 1) },
		{ RightTop, color, XMFLOAT2(1, 0) },
		{ RightBottom, color, XMFLOAT2(1, 1) }
	};
	XMMATRIX rz = XMMatrixRotationZ(XM_PI *dt);
	//先平移为原点，绕着原点旋转, 转换到平行投影的中点为（w/2,h/2）坐标系。Y 是颠倒的，在旋转
	XMMATRIX rTmp = XMMatrixTranslation(-x, -y, 0.0)* rz * XMMatrixTranslation(x, y, 0.0);

	XMMATRIX toTexSpace = GetShow2DMatrix(m_nWidth, m_nHeight);
	toTexSpace = rTmp * toTexSpace;
	DrawPrimitiveUP(PRIMITIVE_TRIANGLELIST, 6, vertices, toTexSpace, pTexture, SpriteType::COLOR_TEX);
}

void Sprite::CalcCircleDot(VertexPositionColorTexture vCenter, VertexPositionColorTexture& vDot, float nRadius, float fAlpha)
{
	// 角度=弧度除以π再乘以180
	float x = nRadius * cosf(fAlpha);
	float y = nRadius * sinf(fAlpha);
	vDot.position.x = vCenter.position.x + x;
	vDot.position.y = vCenter.position.y + y;
	vDot.position.z = vCenter.position.z;
	vDot.color = vCenter.color;
}
void Sprite::DrawCircle(float nX, float nY, float nRadius, const XMFLOAT4& color)
{
	VertexPositionColorTexture verts[150];
	float fDetaAngle = 3.1415927f / 25;
	verts[0].position = { nX, nY, 0.0f };
	verts[0].color = color;
	verts[1].position = { nRadius + nX, nY, 0.0f };
	verts[1].color = color;

	float fAngle = fDetaAngle;
	this->CalcCircleDot(verts[0], verts[2], nRadius, fAngle);
	for (int i = 1; i < 50; i++)
	{
		verts[i * 3] = verts[0];
		verts[i * 3 + 1] = verts[(i - 1) * 3 + 2];
		fAngle += fDetaAngle;
		this->CalcCircleDot(verts[0], verts[i * 3 + 2], nRadius, fAngle);
	}
	XMMATRIX toTexSpace = GetShow2DMatrix(m_nWidth, m_nHeight);
	DrawPrimitiveUP(PRIMITIVE_TRIANGLELIST, 150, verts, toTexSpace,NULL, SpriteType::ONLY_COLOR);


}

void Sprite::DrawPrimitiveUP(PrimitiveType PrimitiveType, unsigned int PrimitiveCount, 
	VertexPositionColorTexture *pVertexs,  Matrix model /*= XMMatrixIdentity()*/,
	ID3D11ShaderResourceView*pTexture /*= NULL*/, SpriteType spriteType)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	m_deviceContext->Map(m_vertexBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource);
	//	Update the vertex buffer here.
	int nSize = PrimitiveCount;
	if (nSize > m_maxBufferSizePerPrimitive)
	{
		nSize = m_maxBufferSizePerPrimitive;
	}
	memcpy(mappedResource.pData, pVertexs, nSize * sizeof(VertexPositionColorTexture));
	//	Reenable GPU access to the vertex buffer data.
	m_deviceContext->Unmap(m_vertexBuffer, 0);

	unsigned int stride;
	unsigned int offset;
	stride = sizeof(VertexPositionColorTexture);
	offset = 0;
	MaterialPtr nMaterialPtr = g_objMaterial.GetShader(m_strShaderPath.c_str());
	if (nMaterialPtr != NULL)
	{
		m_deviceContext->IASetInputLayout(nMaterialPtr->getLayout<VertexPositionColorTexture>());
		m_deviceContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)PrimitiveType);
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		nMaterialPtr->VSSetConstantBuffers("worldMatrix", &model);
		nMaterialPtr->PSSetConstantBuffers("SpriteType", &spriteType);
		if (pTexture)
		{
			nMaterialPtr->PSSetShaderResources(TU_DIFFUSE, pTexture);
		}

		nMaterialPtr->Apply();

		ID3D11SamplerState* LinearWrap = g_objStates.LinearWrap();
		FLOAT BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_deviceContext->OMSetBlendState(g_objStates.AlphaBlend(), BlendFactor, 0xFFFFFFFF);
		m_deviceContext->PSSetSamplers(0, 1, &LinearWrap);
		m_deviceContext->RSSetState(g_objStates.CullCounterClockwise());

		m_deviceContext->Draw(PrimitiveCount, 0);
	}
}

