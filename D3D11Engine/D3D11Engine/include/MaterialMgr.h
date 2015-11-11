#pragma once
#include "HpD3D9Type.h"
#include "Renderer/D3D11RendererMaterial.h"
typedef std::shared_ptr<class D3D11RendererMaterial> MaterialPtr;
class MaterialMgr
{
public:
	static  MaterialMgr& GetInstance();
	MaterialPtr GetShader(const char* pszName);
private:
	MaterialMgr();
	~MaterialMgr();
	typedef std::map<uint32, MaterialPtr> MAP_MATERIALS;
	MAP_MATERIALS mapMaterialPtrs;
};

#define  g_objMaterial MaterialMgr::GetInstance()
