#include "Texture.h"
#include "TextureMgr.h"
#include <string>

#include "TextureMgr.h"

CTexture::CTexture(ID3D11ShaderResourceView* pShaderResource, int nWidth, int nHeight)
: m_pTexture(pShaderResource), m_nWidth(nWidth), m_nHeight(nHeight)
{


}

CTexture::~CTexture()
{
	SAFE_RELEASE(m_pTexture);

}

void CTexture::Show(int x, int y)
{
	//g_objSprite.ShowTexture(x, y, x + m_nWidth, y + m_nHeight, m_pTexture);
}

void CTexture::ShowEx(int x1, int y1, int x2, int y2)
{
	//g_objSprite.ShowTexture(x1,y1,x2,y2, m_pTexture);
}

void CTexture::ShowEx(int x, int y, RECT* pSrc, int nWidth, int nHeight, bool bRotate)
{
	if (nWidth == 0)
	{
		nWidth = m_nWidth;
	}
	if (nHeight == 0)
	{
		nHeight = m_nHeight;
	}
	if (pSrc == NULL)
	{
		RECT  pSrcTmp;
		pSrcTmp.left = 0;
		pSrcTmp.right = m_nWidth;
		pSrcTmp.top = 0;
		pSrcTmp.bottom = m_nHeight;
		//g_objSprite.ShowTexEx(x, y, &pSrcTmp, nWidth, nHeight, this);
	/*	ID3D11ShaderResourceView *ppShaderResourceView = NULL;
		m_deviceContext->VSGetShaderResources(0, 1, &ppShaderResourceView);
		if (ppShaderResourceView)
		{
			g_objTextureMgr.Save(ppShaderResourceView, "view.png");
		}*/
	}
	else
	{
		//g_objSprite.ShowTexEx(x, y, pSrc, nWidth, nHeight, this);
	}
}



void CTexture::Save()
{

	g_objTextureMgr.Save(m_pTexture, "view.png");
}
