#pragma once
#include "HpD3D9Type.h"
#include "VertexTypes.h"
/************************************************************************/
/* 2D绘制精灵                                                                     */
/************************************************************************/

enum PrimitiveType
{
	PRIMITIVE_UNDEFINED = 0,
	PRIMITIVE_POINTLIST = 1,
	PRIMITIVE_LINELIST = 2,
	PRIMITIVE_LINESTRIP = 3,
	PRIMITIVE_TRIANGLELIST = 4,
	PRIMITIVE_TRIANGLESTRIP = 5,
};

enum SpriteType
{
	ONLY_COLOR = 0,
	ONLY_TEX = 1,
	COLOR_TEX = 2
};

class Sprite
{
public:
	static Sprite& GetInstance();
	Sprite(int initialBufferCapacity = 1024, int maxBufferSizePerPrimitive = 32768);
	~Sprite();
	//必须设置画布大小
	void ResetSize(int nWidth, int nHeight);
	void ShowRect(int x1, int y1, int x2, int y2, const XMFLOAT4& color, float dt = 0);
	void ShowBlock(int x1, int y1, int x2, int y2, const XMFLOAT4& color, float dt = 0);
	void	DrawCircle(float nX, float nY, float nRadius, const XMFLOAT4& color = { 1, 0, 0, 1 });
	void ShowTexture(int x, int y, const char*pszName);
	void ShowTexture(int x1, int y1, int x2, int y2, const char*pszName);

	void ShowTexture(int x1, int y1, int x2, int y2, ID3D11ShaderResourceView*pTexture, 
		const XMFLOAT4& color = { 1, 1, 1, 1 }, float dt = 0, SpriteType spriteType = COLOR_TEX);
	void DrawPrimitiveUP(PrimitiveType PrimitiveType, unsigned int PrimitiveCount,
		VertexPositionColorTexture *pVertexs, Matrix model = XMMatrixIdentity(),
		ID3D11ShaderResourceView*pTexture = NULL, SpriteType spriteType = COLOR_TEX);
	void SetShader(const char* pszName){ m_strShaderPath = pszName; }
	void SetAlphaBlend(bool bBlend = false){ m_bBlend = bBlend; }
protected:
	void CreateVertexBuffer(int nType, int nSize);
	void CreateIndexBuffer(int nType, int nSize);
	void	CalcCircleDot(VertexPositionColorTexture vCenter, VertexPositionColorTexture& vDot, float nRadius, float fAlpha);
private:
	ID3D11Buffer *m_vertexBuffer;
	ID3D11Buffer	*m_indexBuffer;
	ID3D11Device			*m_d3dDevice;				//D3D11设备
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文
	int m_maxBufferSizePerPrimitive;
	int m_initialBufferCapacity;
	int					m_nWidth;
	int					m_nHeight;
	std::string m_strShaderPath;
	bool m_bBlend;
};

#define g_objSprite Sprite::GetInstance()