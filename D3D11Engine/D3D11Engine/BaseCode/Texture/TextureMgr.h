#ifndef TEXTUREMGR_H
#define TEXTUREMGR_H

#include "HpD3D9Type.h"
#include "Texture.h"
#include <map>
#include <vector>
///<summary>
/// Simple texture manager to avoid loading duplicate textures from file.  That can
/// happen, for example, if multiple meshes reference the same texture filename. 
///</summary>
class  TextureMgr
{
public:
	static TextureMgr* GetInstancePtr();
	static TextureMgr& GetInstance();
	CTexture* GetTexture(std::wstring filename);
	CTexture* GetTexture(std::string filename);
	ID3D11ShaderResourceView* CreateTexture(std::wstring filename);
	ID3D11ShaderResourceView* CreateTexture(std::string filename);
	static void Save(ID3D11Texture2D* pBuffer, const char* filename);
	static void Save(ID3D11ShaderResourceView* pViewBuffer, const char* filename);

	static void Save(ID3D11Texture2D* pBuffer, const RECT& pSrc,const char* filename);
	static void Save(ID3D11ShaderResourceView* pViewBuffer, const RECT& pSrc, const char* filename);

	static void SaveEx(ID3D11Texture2D* pBuffer, const char* filename);

	ID3D11ShaderResourceView* CreateTextureDDs(std::string filename);
	ID3D11ShaderResourceView* CreateRandomTexture1DSRV();
	 void Relesese();
private:
	TextureMgr(const TextureMgr& rhs);
	TextureMgr& operator=(const TextureMgr& rhs);
	TextureMgr();
	~TextureMgr();
	void Init(ID3D11Device* device);
private:
	ID3D11ShaderResourceView* CreateShaderResourceViewFromFile(ID3D11Device*  pDevice, const char*   strFileName,int & nWidth, int & nHeight);
private:
	ID3D11Device* md3dDevice;
	static unsigned char* m_ShareMemory;
	static long SHARE_MEMORY_SIZE;
private:
	typedef std::map<std::string, CTexture*> TTextureMap;
	// The map of already loaded textures. There are indexed
	// using their filename.
	TTextureMap m_Textures;


};
#define  g_objTextureMgr TextureMgr::GetInstance()
#endif // TEXTUREMGR_H