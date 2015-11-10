#pragma once
#include <d3d11.h>

class CommonStates
{
public:
	static CommonStates* GetInstancePtr()
	{
		static CommonStates _instance;
		return &_instance;
	}
	static CommonStates& CommonStates::GetInstance()
	{
		return *GetInstancePtr();
	}

	ID3D11BlendState*  Add() ;
	ID3D11BlendState*  Opaque() ;
	ID3D11BlendState*  AlphaBlend() ;
	ID3D11BlendState*  Additive() ;
	ID3D11BlendState*  NonPremultiplied() ;


	// Rasterizer states.
	ID3D11RasterizerState*  CullNone() ;
	ID3D11RasterizerState*  CullClockwise() ;
	ID3D11RasterizerState*  CullCounterClockwise() ;
	ID3D11RasterizerState*  Wireframe();


	ID3D11SamplerState*  PointWrap() ;
	ID3D11SamplerState*  PointClamp() ;
	ID3D11SamplerState*  LinearWrap() ;
	ID3D11SamplerState*  LinearClamp() ;
	ID3D11SamplerState*  AnisotropicWrap() ;
	ID3D11SamplerState*  AnisotropicClamp() ;

	ID3D11DepthStencilState*  DepthNone() ;
	ID3D11DepthStencilState*  DepthDefault() ;
	ID3D11DepthStencilState*  DepthRead() ;

	void ReleaseAll();
private:
	explicit CommonStates();
	virtual ~CommonStates();
	HRESULT CreateBlendState(D3D11_BLEND srcBlend, D3D11_BLEND destBlend, _Out_ ID3D11BlendState** pResult);
	HRESULT CreateDepthStencilState(bool enable, bool writeEnable, _Out_ ID3D11DepthStencilState** pResult);
	HRESULT CreateRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, _Out_ ID3D11RasterizerState** pResult);
	HRESULT CreateSamplerState(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode, _Out_ ID3D11SamplerState** pResult);

private:
	ID3D11BlendState* add;
	ID3D11BlendState* opaque;
	ID3D11BlendState* alphaBlend;
	ID3D11BlendState* additive;
	ID3D11BlendState* nonPremultiplied;



	ID3D11RasterizerState* cullNone;
	ID3D11RasterizerState* cullClockwise;
	ID3D11RasterizerState* cullCounterClockwise;
	ID3D11RasterizerState* wireframe;

	
	ID3D11SamplerState* pointWrap;
	ID3D11SamplerState* pointClamp;
	ID3D11SamplerState* linearWrap;
	ID3D11SamplerState* linearClamp;
	ID3D11SamplerState* anisotropicWrap;
	ID3D11SamplerState* anisotropicClamp;

	
	ID3D11DepthStencilState*	depthNone;
	ID3D11DepthStencilState*	depthDefault;
	ID3D11DepthStencilState*	depthRead;


	ID3D11Device* device;
};
#define  g_objStates CommonStates::GetInstance()