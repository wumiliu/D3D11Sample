#include "MaterialMgr.h"
#include "StringHash.h"

MaterialMgr& MaterialMgr::GetInstance()
{
	static MaterialMgr _instance;
	return *(&_instance);
}

MaterialMgr::MaterialMgr()
{
}


MaterialMgr::~MaterialMgr()
{
}

MaterialPtr MaterialMgr::GetShader(const char* pszName)
{
	StringHash key(pszName);
	MAP_MATERIALS::iterator iter = mapMaterialPtrs.find(key);
	if (iter != mapMaterialPtrs.end())
	{
		return iter->second;
	}
	else
	{
		RendererMaterialDesc desc;
		desc.strHLSLPath = pszName;
		D3D11RendererMaterial* pMaterial = new D3D11RendererMaterial(desc);
		MaterialPtr newShader(pMaterial);
		mapMaterialPtrs[key] = newShader;
		return newShader;
	}
	return NULL;
}


