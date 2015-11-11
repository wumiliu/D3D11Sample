#include "DXFunction.h"
#include "Texture/DDSTextureLoader.h"
#include "BaseFunc.h"
ID3D11ShaderResourceView* D3DX11CreateShaderResourceViewFromFile(ID3D11Device* pDevice, const char* strFileName)
{
	ID3D11Texture2D* pTexture2D;
	ID3D11ShaderResourceView* srv;

	wchar_t* pszName = gAnsiToUnicode(strFileName);
	HRESULT ret = DirectX::CreateDDSTextureFromFile(
		pDevice,
		pszName,
		(ID3D11Resource**)&pTexture2D,
		&srv
		);
	SAFE_RELEASE(pTexture2D);
	SAFE_DELETE_ARRAY(pszName);

	return srv;
}

DirectX::XMMATRIX GetShow2DMatrix(int nWidth, int nHegith)
{
	// Transform NDC space [-1,+1]^2 to screen space [0,1]^2
	XMMATRIX toTexSpace(
		0.5f * nWidth, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f * nHegith, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f * nWidth, 0.5f * nHegith, 0.0f, 1.0f);
	return XMMatrixInverse(NULL, toTexSpace);
}
