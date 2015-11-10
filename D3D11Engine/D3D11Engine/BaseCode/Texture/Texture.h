#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <string>
#include "HpD3D9Type.h"

class TextureMgr;
// Class that wraps information about a texture. This class 
// won't be used directly by the users. Instead, they will
// manipulate the CImage class.
class   CTexture
{
	friend class TextureMgr;
public:
	ID3D11ShaderResourceView* GetShaderResourceView(){ return m_pTexture; }
	void Show(int x, int y);
	void ShowEx(int x1, int y1, int x2, int y2);

	//x,y: 图像要显示的左上角位置 
	//pSrc: 要显示的图像的来源矩形区域,传入为NULL表示显示整张图像. 对调C3_RECT的left/right变量可以左右颠倒显示图像 
	//	对调RECT的top / bottom变量可以上下颠倒显示图像
	//nWidth, nHeight: 图像要显示到屏幕的目标矩形大小.
	//若为0,表示按图像的原始资源尺寸显示 
	//若dwWidth, dwHeight不等于指定图像的原始尺寸大小, 图像会自动进行缩放显示.
	//////////////////////////////////////////////////////////////////////////
	void ShowEx(int x, int y, RECT* pSrc = NULL, int nWidth = 0, int nHeight = 0,bool bRotate = false);

	int  GetWidth(){ return m_nWidth; }
	int  GetHegith(){ return m_nHeight; }
	void Save();
protected:
	// Constructor which takes the filename as argument.
	// It loads the file and throw an exception if the load
	// failed.
	CTexture(ID3D11ShaderResourceView* pShaderResource,int nWidth,int nHeight);
	~CTexture();
private:
	ID3D11ShaderResourceView* m_pTexture;                                //纹理指针
	ID3D11Device			*m_d3dDevice;				//D3D11设备
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文
	int m_nWidth;
	int m_nHeight;
};

#endif  // _TEXTURE_H_