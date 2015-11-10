
#include "Renderer/DeviceManager.h"
#include "TextureMgr.h"
#include "FreeImage.h"
#include "BaseCode/BaseFunc.h"
#pragma comment(lib,"FreeImage.lib")
#include "DDSTextureLoader.h"





#define HR(x) (x)
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
#define SafeDelete(x) { delete x; x = 0; }

#define MAX_SHARE_MEMORY  (4*4*1024*1024)
long TextureMgr::SHARE_MEMORY_SIZE = 0;
unsigned char* TextureMgr::m_ShareMemory = NULL;

TextureMgr::TextureMgr() : md3dDevice(0)
{
	SHARE_MEMORY_SIZE = MAX_SHARE_MEMORY;
	m_ShareMemory = (unsigned char*)malloc(SHARE_MEMORY_SIZE);
	Init(g_objDeviecManager.GetDevice());

}
void TextureMgr::Relesese()
{
	for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		CTexture* pTexture = (CTexture*)it->second;
		if (pTexture)
		{
			//ID3D11ShaderResourceView* pTextureView = pTexture->GetShaderResourceView();
			//ReleaseCOM(pTextureView);
			delete pTexture;
			pTexture = NULL;
		}
	}
	m_Textures.clear();
}
TextureMgr::~TextureMgr()
{
	if (m_ShareMemory)
	{
		free(m_ShareMemory);
		m_ShareMemory = NULL;
	}
	Relesese();
}

TextureMgr* TextureMgr::GetInstancePtr()
{
	static TextureMgr _instance;
	return &_instance;
}

TextureMgr& TextureMgr::GetInstance()
{
	return *GetInstancePtr();
}

void TextureMgr::Init(ID3D11Device* device)
{
	md3dDevice = device;
}

CTexture* TextureMgr::GetTexture(std::wstring filename)
{
	return GetTexture((UnicodeToANSI(filename.c_str())));
}

CTexture* TextureMgr::GetTexture(std::string filename)
{
	//filename = BaseFunction::trim(filename);
	CTexture* pTexture = NULL;
	// Does it already exist?
	if (m_Textures.find(filename) != m_Textures.end())
	{
		pTexture = m_Textures[filename];
	}
	else
	{
		int nWidth = 0;
		int  nHeight = 0;
		ID3D11ShaderResourceView* srv = CreateShaderResourceViewFromFile(md3dDevice, filename.c_str(), nWidth, nHeight);
		if (srv)
		{
			pTexture = new CTexture(srv, nWidth, nHeight);
			m_Textures[filename] = pTexture;
		}
	}
	return pTexture;
}

ID3D11ShaderResourceView* TextureMgr::CreateTexture(std::wstring filename)
{
	return CreateTexture((UnicodeToANSI(filename.c_str())));
}

ID3D11ShaderResourceView* TextureMgr::CreateTexture(std::string filename)
{
	CTexture* pTexture = GetTexture(filename);
	if (pTexture)
	{
		return pTexture->GetShaderResourceView();
	}
	return NULL;
}

ID3D11ShaderResourceView* TextureMgr::CreateShaderResourceViewFromFile(ID3D11Device* pDevice, const char* strFileName, int & nWidth, int & nHeight)
{
	// Generate a new image Id and bind it with the
	// current image.
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(strFileName);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(strFileName);
	// Load the file data in the current image.
	FIBITMAP *dib0;
	dib0 = FreeImage_Load(fif, strFileName, 0);
	FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(dib0);
	if (dib0 == NULL)
	{
		return NULL;
	}
	int bpp = FreeImage_GetBPP(dib0);
	FIBITMAP* dib = FreeImage_ConvertTo32Bits(dib0);
	FreeImage_Unload(dib0);
	bpp = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);
	// Store the data in our STextureData structure.
	int newSize = FreeImage_GetDIBSize(dib);
	nWidth = FreeImage_GetWidth(dib);
	nHeight = FreeImage_GetHeight(dib);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = static_cast<UINT>(nWidth);
	desc.Height = static_cast<UINT>(nHeight);
	desc.MipLevels = static_cast<UINT>(1);
	desc.ArraySize = static_cast<UINT>(1);
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D *tex = NULL;
	D3D11_SUBRESOURCE_DATA tbsd;

	if (pitch * nHeight > MAX_SHARE_MEMORY)
	{
		int i = (pitch * nHeight) / (MAX_SHARE_MEMORY);
		SHARE_MEMORY_SIZE = 2 * (i)*MAX_SHARE_MEMORY;

		m_ShareMemory = (unsigned char*)realloc(m_ShareMemory, SHARE_MEMORY_SIZE);
	}
	memset(m_ShareMemory, 0, SHARE_MEMORY_SIZE);


	unsigned char* pDst = m_ShareMemory;
	for (int y = 0; y < nHeight; y++)
	{
		BYTE *bits = pDst + y*pitch;// FreeImage_GetScanLine(bitmap, FreeImage_GetHeight(bitmap) - 1 - y);
		BYTE* src = FreeImage_GetScanLine(dib, nHeight - 1 - y);//, FreeImage_GetScanLine(dib, rows), 
		int kk = FI_RGBA_RED;
		//bgra
		//// Little Endian (x86 / MS Windows, Linux) : BGR(A) order
		for (int x = 0; x < nWidth; x++)
		{
			//Texture -> RGBA to ->BGRA
			bits[0] = src[2]; //r -> 
			bits[1] = src[1]; //a ->
			bits[2] = src[0]; //g
			bits[3] = src[3]; //b
			bits += 4;
			src += 4;
		}
	}
	int ffff = FreeImage_GetPitch(dib);
	tbsd.pSysMem = (void *)m_ShareMemory;// FreeImage_GetBits(dib);
	tbsd.SysMemPitch = FreeImage_GetPitch(dib);
	tbsd.SysMemSlicePitch = 0;// FreeImage_GetPitch(dib); // Not needed since this is a 2d texture
	FreeImage_Unload(dib);
	

	HRESULT hr = pDevice->CreateTexture2D(&desc, &tbsd, &tex);
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	memset(&SRVDesc, 0, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;
	ID3D11ShaderResourceView* m_pTexture = 0;
	hr = pDevice->CreateShaderResourceView(tex, &SRVDesc, &m_pTexture);
	SAFE_RELEASE(tex);
	return m_pTexture;
}


void TextureMgr::Save(ID3D11Texture2D* pBuffer, const char* filename)
{
	D3D11_TEXTURE2D_DESC pDest;
	pBuffer->GetDesc(&pDest);
	int nWidth = pDest.Width;
	int nHeight = pDest.Height;
	int bpp = 4 * 8;
	FIBITMAP *newDib = FreeImage_AllocateT(FIT_BITMAP, nWidth, nHeight, bpp);
	UINT pDataSize = sizeof(ID3D11Texture2D);
	D3D11_MAPPED_SUBRESOURCE mapped;
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文
	m_deviceContext = g_objDeviecManager.GetImmediateContext();


	D3D11_TEXTURE2D_DESC desc;
	desc.Width = static_cast<UINT>(nWidth);
	desc.Height = static_cast<UINT>(nHeight);
	desc.MipLevels = static_cast<UINT>(1);
	desc.ArraySize = static_cast<UINT>(1);
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	//	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;

	desc.BindFlags = 0;


	ID3D11Texture2D*  texEx;

	HRESULT hr = g_objDeviecManager.GetDevice()->CreateTexture2D(&desc, NULL, &texEx);


	//CaptureTexture(m_deviceContext, pBuffer, desc,&pBffer1);
	m_deviceContext->CopyResource(texEx, pBuffer);
	hr = m_deviceContext->Map(texEx, 0, D3D11_MAP_READ, 0, &mapped);
	int pitch = 4 * nWidth;
	if (hr == S_OK)
	{
		unsigned char* pSrcBuf = (unsigned char *)mapped.pData;
		for (int i = 0; i < (int)desc.Height; ++i)
		{
			BYTE *bits = FreeImage_GetBits(newDib) + (desc.Height - i - 1)*pitch;// FreeImage_GetScanLine(bitmap, FreeImage_GetHeight(bitmap) - 1 - y);
			BYTE* src = pSrcBuf + i*mapped.RowPitch;
			int kk = FI_RGBA_RED;
			for (uint32 x = 0; x < desc.Width; x++)
			{
				//Texture -> RGBA to ->BGRA
				//Texture -> RGBA to ->BGRA
				bits[0] = src[2]; //r -> 
				bits[1] = src[1]; //a ->
				bits[2] = src[0]; //g
				bits[3] = src[3]; //b
				bits += 4;
				src += 4;
			}
		}
		FreeImage_Save(FIF_PNG, newDib, filename);
		FreeImage_Unload(newDib);
	}
	m_deviceContext->Unmap(texEx, 0);
	SAFE_RELEASE(texEx);
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	memset(&SRVDesc, 0, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;
}

void TextureMgr::Save(ID3D11ShaderResourceView* pViewBuffer, const char* filename)
{
	ID3D11Resource* ppResource;
	pViewBuffer->GetResource(&ppResource);
	ID3D11Texture2D*  texEx;
	HRESULT hr = ppResource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texEx));
	Save(texEx, filename);
}

void TextureMgr::Save(ID3D11ShaderResourceView* pViewBuffer, const RECT& pSrc, const char* filename)
{
	ID3D11Resource* ppResource;
	pViewBuffer->GetResource(&ppResource);
	ID3D11Texture2D*  texEx;
	HRESULT hr = ppResource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&texEx));
	Save(texEx, pSrc, filename);
}

void TextureMgr::Save(ID3D11Texture2D* pBuffer, const RECT& pSrc, const char* filename)
{
	D3D11_TEXTURE2D_DESC pDest;
	pBuffer->GetDesc(&pDest);
	int nWidth = pDest.Width;
	int nHeight = pDest.Height;

	int nWidthDst = pSrc.right - pSrc.left;
	int nHeightDst = pSrc.bottom - pSrc.top;
	int bpp = 4 * 8;
	FIBITMAP *newDib = FreeImage_AllocateT(FIT_BITMAP, nWidthDst, nHeightDst, bpp);
	UINT pDataSize = sizeof(ID3D11Texture2D);
	D3D11_MAPPED_SUBRESOURCE mapped;
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文
	m_deviceContext = g_objDeviecManager.GetImmediateContext();


	D3D11_TEXTURE2D_DESC desc;
	desc.Width = static_cast<UINT>(nWidth);
	desc.Height = static_cast<UINT>(nHeight);
	desc.MipLevels = static_cast<UINT>(1);
	desc.ArraySize = static_cast<UINT>(1);
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	//	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;

	desc.BindFlags = 0;


	ID3D11Texture2D*  texEx;

	HRESULT hr = g_objDeviecManager.GetDevice()->CreateTexture2D(&desc, NULL, &texEx);


	//CaptureTexture(m_deviceContext, pBuffer, desc,&pBffer1);
	m_deviceContext->CopyResource(texEx, pBuffer);
	hr = m_deviceContext->Map(texEx, 0, D3D11_MAP_READ, 0, &mapped);
	int pitch = 4 * nWidthDst;
	if (hr == S_OK)
	{
		unsigned char* pSrcBuf = (unsigned char *)mapped.pData;
		int ii = 0;
		for (int i = pSrc.top; i < (int)pSrc.bottom; ++i, ++ii)
		{
			BYTE *bits = FreeImage_GetBits(newDib) + (nHeightDst - ii - 1)*pitch;// FreeImage_GetScanLine(bitmap, FreeImage_GetHeight(bitmap) - 1 - y);
			BYTE* src = pSrcBuf + i*mapped.RowPitch;
			int kk = FI_RGBA_RED;
			for (int x = pSrc.left; x < pSrc.right; x++)
			{
				//Texture -> RGBA to ->BGRA
				//Texture -> RGBA to ->BGRA
				bits[0] = src[x * 4 + 2]; //r -> 
				bits[1] = src[x * 4 + 1]; //a ->
				bits[2] = src[x * 4 + 0]; //g
				bits[3] = src[x * 4 + 3]; //b
				bits += 4;
				//src += 4;
			}
		}
		FreeImage_Save(FIF_PNG, newDib, filename);
		FreeImage_Unload(newDib);
	}
	m_deviceContext->Unmap(texEx, 0);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	memset(&SRVDesc, 0, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MostDetailedMip = 0;
	SRVDesc.Texture2D.MipLevels = 1;
}

float RandF()
{
	return (float)(rand()) / (float)RAND_MAX;
}
// Returns random float in [a, b).
float RandF(float a, float b)
{
	return a + RandF()*(b - a);
}

ID3D11ShaderResourceView* TextureMgr::CreateRandomTexture1DSRV()
{
	// 
	// Create the random data.
	//
	XMFLOAT4 randomValues[1024];
	srand(timeGetTime());

/*

	for (int i = 0; i < 1024; ++i)
	{
		randomValues[i].x = RandF(-1.0f, 1.0f);
		randomValues[i].y = RandF(-1.0f, 1.0f);
		randomValues[i].z = RandF(-1.0f, 1.0f);
		randomValues[i].w = RandF(-1.0f, 1.0f);
	}
*/

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = randomValues;
	initData.SysMemPitch = 1024 * sizeof(XMFLOAT4);
	initData.SysMemSlicePitch = 0;
	for (int i = 0; i < 1024 * 4; i++)
	{
		((float*)initData.pSysMem)[i] = float((rand() % 10000) - 5000);
	}
	//
	// Create the texture.
	//
	D3D11_TEXTURE1D_DESC texDesc;
	texDesc.Width = 1024;
	texDesc.MipLevels = 1;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.Usage = D3D11_USAGE_IMMUTABLE;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;
	texDesc.ArraySize = 1;

	ID3D11Texture1D* randomTex = 0;
	HR(md3dDevice->CreateTexture1D(&texDesc, &initData, &randomTex));


	//
	// Create the resource view.
	//
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = texDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
	viewDesc.Texture1D.MipLevels = texDesc.MipLevels;
	viewDesc.Texture1D.MostDetailedMip = 0;

	ID3D11ShaderResourceView* randomTexSRV = 0;
	HR(md3dDevice->CreateShaderResourceView(randomTex, &viewDesc, &randomTexSRV));

	ReleaseCOM(randomTex);

	return randomTexSRV;
}

ID3D11ShaderResourceView* TextureMgr::CreateTextureDDs(std::string filename)
{
	filename = trim(filename);
	CTexture* pTexture = NULL;
	// Does it already exist?
	if (m_Textures.find(filename) != m_Textures.end())
	{
		pTexture = m_Textures[filename];
	}
	else
	{
		int nWidth = 0;
		int  nHeight = 0;
		ID3D11ShaderResourceView* srv;
		wchar_t* pszName =gAnsiToUnicode(filename.c_str());
		ID3D11Texture2D* pTexture2D;
		HRESULT ret = DirectX::CreateDDSTextureFromFile(
			md3dDevice,
			pszName,
			(ID3D11Resource**)&pTexture2D,
			&srv
			);
		if (srv)
		{
			pTexture = new CTexture(srv, nWidth, nHeight);
			m_Textures[filename] = pTexture;
		}
		delete pszName;
		pszName = NULL;
	}
	if (pTexture)
	{
		return pTexture->GetShaderResourceView();
	}
	return NULL;
}

void TextureMgr::SaveEx(ID3D11Texture2D* pBuffer, const char* filename)
{
	D3D11_TEXTURE2D_DESC pDest;
	pBuffer->GetDesc(&pDest);
	int nWidth = pDest.Width;
	int nHeight = pDest.Height;
	int bpp = 4 * 8;
	FIBITMAP *newDib = FreeImage_AllocateT(FIT_BITMAP, nWidth, nHeight, bpp);
	UINT pDataSize = sizeof(ID3D11Texture2D);
	D3D11_MAPPED_SUBRESOURCE mapped;
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文
	m_deviceContext = g_objDeviecManager.GetImmediateContext();


	D3D11_TEXTURE2D_DESC desc;
	desc.Width = static_cast<UINT>(nWidth);
	desc.Height = static_cast<UINT>(nHeight);

	HRESULT hr = m_deviceContext->Map(pBuffer, 0, D3D11_MAP_READ, 0, &mapped);
	int pitch = 4 * nWidth;
	unsigned char* pSrcBuf = (unsigned char *)mapped.pData;
	unsigned char* pDestBuf =FreeImage_GetBits(newDib);

	memcpy_s(pDestBuf, pitch * desc.Height * sizeof(unsigned char), pSrcBuf, pitch * desc.Height * sizeof(unsigned char));
	FreeImage_Save(FIF_PNG, newDib, filename);
	FreeImage_Unload(newDib);
	m_deviceContext->Unmap(pBuffer, 0);
	return;
	if (hr == S_OK)
	{
		unsigned char* pSrcBuf = (unsigned char *)mapped.pData;
		for (int i = 0; i < (int)desc.Height; ++i)
		{
			BYTE *bits = FreeImage_GetBits(newDib) + (desc.Height - i - 1)*pitch;// FreeImage_GetScanLine(bitmap, FreeImage_GetHeight(bitmap) - 1 - y);
			BYTE* src = pSrcBuf + i*mapped.RowPitch;
			int kk = FI_RGBA_RED;
			for (uint32 x = 0; x < desc.Width; x++)
			{
				//Texture -> RGBA to ->BGRA
				//Texture -> RGBA to ->BGRA
				bits[0] = src[2]; //r -> 
				bits[1] = src[1]; //a ->
				bits[2] = src[0]; //g
				bits[3] = src[3]; //b
				bits += 4;
				src += 4;
			}
		}
		FreeImage_Save(FIF_PNG, newDib, filename);
		FreeImage_Unload(newDib);
	}
	m_deviceContext->Unmap(pBuffer, 0);

}

