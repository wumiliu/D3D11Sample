#pragma once
#include "HpD3D9Type.h"
/************************************************************************/
/* D3D设备创建接口                                                                     */
/************************************************************************/
class  DeviceManager
{
public:
	static DeviceManager* GetInstancePtr();
	static DeviceManager& GetInstance();

	ID3D11Device* GetDevice()
	{
		return m_pd3dDevice;
	}

	IDXGIFactory* GetDXGIFactory()
	{
		return m_pDXGIFactory;
	}

	ID3D11DeviceContext* GetImmediateContext()
	{
		return m_pImmediateContext;
	}
private:
	DeviceManager();
	~DeviceManager();
private:
	ID3D11Device*           m_pd3dDevice;
	ID3D11DeviceContext*    m_pImmediateContext;

	IDXGIFactory*          m_pDXGIFactory;

};

#define g_objDeviecManager  DeviceManager::GetInstance()