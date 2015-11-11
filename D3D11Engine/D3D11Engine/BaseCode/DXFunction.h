#pragma once
#include "HpD3D9Type.h"

ID3D11ShaderResourceView* D3DX11CreateShaderResourceViewFromFile(
	ID3D11Device*  pDevice,
	const char*   strFileName);

//获取绘制2D的矩阵
XMMATRIX GetShow2DMatrix(int nWidth, int nHegith);