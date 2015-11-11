#include "CommonStates.h"
#include "DeviceManager.h"
#include "DirectXHelpers.h"

HRESULT CommonStates::CreateBlendState(D3D11_BLEND srcBlend, D3D11_BLEND destBlend, _Out_ ID3D11BlendState** pResult)
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) ||
		(destBlend != D3D11_BLEND_ZERO);

	desc.RenderTarget[0].SrcBlend = desc.RenderTarget[0].SrcBlendAlpha = srcBlend;
	desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
	desc.RenderTarget[0].BlendOp = desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = device->CreateBlendState(&desc, pResult);

	if (SUCCEEDED(hr))
		SetDebugObjectName(*pResult, "DirectXTK:CommonStates");

	return hr;
}

HRESULT CommonStates::CreateDepthStencilState(bool enable, bool writeEnable, _Out_ ID3D11DepthStencilState** pResult)
{
	D3D11_DEPTH_STENCIL_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.DepthEnable = enable; //是否使用深度缓冲区，显然大多数数情况下为true
	//深度值写入掩码值，大多数情况下我们把整个深度值完整写入，因此掩码值为D3D11_DEPTH_WRITE_MASK_ALL；
	desc.DepthWriteMask = writeEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	//：深度判断值，即本文第二部分中提到的比较函数，大多数情况下我们使用LESS，即更小的深度（更靠前）通过测试；
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	//是否使用模板缓冲区，我们就是要开启模板缓冲区，因此为true
	desc.StencilEnable = true;
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	desc.BackFace = desc.FrontFace;

	HRESULT hr = device->CreateDepthStencilState(&desc, pResult);

	if (SUCCEEDED(hr))
		SetDebugObjectName(*pResult, "DirectXTK:CommonStates");

	return hr;
}

HRESULT CommonStates::CreateRasterizerState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode, _Out_ ID3D11RasterizerState** pResult)
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.CullMode = cullMode;
	desc.FillMode = fillMode;
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;
	//表示按顺时针方向环绕的三角形（相对于观察者）是朝前的
	desc.FrontCounterClockwise = FALSE;
	//顺时针为正面
	//  D3D11_CULL_NONE	= 1, 不进行任何剔除
	//	D3D11_CULL_FRONT = 2, 按顺时针方向进行剔除
	//	D3D11_CULL_BACK = 3   按逆时针方向进行剔除（这是DX的默认剔除方式）
	HRESULT hr = device->CreateRasterizerState(&desc, pResult);

	if (SUCCEEDED(hr))
		SetDebugObjectName(*pResult, "DirectXTK:CommonStates");

	return hr;
}

HRESULT CommonStates::CreateSamplerState(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE addressMode, _Out_ ID3D11SamplerState** pResult)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Filter = filter;

	desc.AddressU = addressMode;
	desc.AddressV = addressMode;
	desc.AddressW = addressMode;

	desc.MaxAnisotropy = (device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? 16 : 2;

	desc.MaxLOD = FLT_MAX;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;

	HRESULT hr = device->CreateSamplerState(&desc, pResult);

	if (SUCCEEDED(hr))
		SetDebugObjectName(*pResult, "DirectXTK:CommonStates");

	return hr;
}

CommonStates::CommonStates()
{
	add = NULL;
	opaque = NULL;
	alphaBlend = NULL;
	additive = NULL;
	nonPremultiplied = NULL;

	cullNone = NULL;
	cullClockwise = NULL;
	cullCounterClockwise = NULL;
	wireframe = NULL;


	pointWrap = NULL;
	pointClamp = NULL;
	linearWrap = NULL;
	linearClamp = NULL;
	anisotropicWrap = NULL;
	anisotropicClamp = NULL;

	device = g_objDeviecManager.GetDevice();

}

CommonStates::~CommonStates()
{
	ReleaseAll();
}

void CommonStates::ReleaseAll()
{
	SAFE_RELEASE(add);
	SAFE_RELEASE(opaque);
	SAFE_RELEASE(alphaBlend);
	SAFE_RELEASE(additive);
	SAFE_RELEASE(nonPremultiplied);

	SAFE_RELEASE(cullNone);
	SAFE_RELEASE(cullClockwise);
	SAFE_RELEASE(cullCounterClockwise);
	SAFE_RELEASE(wireframe);


	SAFE_RELEASE(pointWrap);
	SAFE_RELEASE(pointClamp);
	SAFE_RELEASE(linearWrap);
	SAFE_RELEASE(linearClamp);
	SAFE_RELEASE(anisotropicWrap);
	SAFE_RELEASE(anisotropicClamp);

	SAFE_RELEASE(depthNone);
	SAFE_RELEASE(depthDefault);
	SAFE_RELEASE(depthRead);

}

ID3D11BlendState* CommonStates::Add() 
{
	if (add == NULL)
	{
		CreateBlendState(D3D11_BLEND_ONE, D3D11_BLEND_ZERO, &add);
	}
	return add;
}

ID3D11BlendState* CommonStates::Opaque() 
{
	if (opaque == NULL)
	{
		CreateBlendState(D3D11_BLEND_ONE, D3D11_BLEND_ZERO, &opaque);
	}
	return opaque;
}

ID3D11BlendState* CommonStates::AlphaBlend() 
{
	if (alphaBlend == NULL)
	{
		CreateBlendState(D3D11_BLEND_ONE, D3D11_BLEND_INV_SRC_ALPHA, &alphaBlend);
	}
	return alphaBlend;
}

ID3D11BlendState* CommonStates::Additive() 
{
	if (additive == NULL)
	{
		CreateBlendState(D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE, &additive);
	}
	return additive;
}

ID3D11BlendState* CommonStates::NonPremultiplied() 
{
	if (nonPremultiplied == NULL)
	{
		CreateBlendState(D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, &nonPremultiplied);
	}
	return nonPremultiplied;
}



ID3D11RasterizerState* CommonStates::CullNone()
{
	if (cullNone == NULL)
	{
		CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_SOLID, &cullNone);
	}
	return cullNone;
}

ID3D11RasterizerState* CommonStates::CullClockwise()
{
	if (cullClockwise == NULL)
	{
		CreateRasterizerState(D3D11_CULL_FRONT, D3D11_FILL_SOLID, &cullClockwise);
	}
	return cullClockwise;

}

ID3D11RasterizerState* CommonStates::CullCounterClockwise()
{
	if (cullCounterClockwise == NULL)
	{
		CreateRasterizerState(D3D11_CULL_BACK, D3D11_FILL_SOLID, &cullCounterClockwise);
	}
	return cullCounterClockwise;
}

ID3D11RasterizerState* CommonStates::Wireframe()
{
	if (wireframe == NULL)
	{
		CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_WIREFRAME, &wireframe);
	}
	return wireframe;
}

ID3D11SamplerState* CommonStates::PointWrap()
{
	if (pointWrap == NULL)
	{
		CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP, &pointWrap);
	}
	return pointWrap;
}

ID3D11SamplerState* CommonStates::PointClamp()
{
	if (pointClamp == NULL)
	{
		CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP, &pointClamp);
	}
	return pointClamp;
}

ID3D11SamplerState* CommonStates::LinearWrap()
{
	if (linearWrap == NULL)
	{
		CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, &linearWrap);
	}
	return linearWrap;
}

ID3D11SamplerState* CommonStates::LinearClamp()
{
	if (linearClamp == NULL)
	{
		CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP, &linearClamp);
	}
	return linearClamp;
}

ID3D11SamplerState* CommonStates::AnisotropicWrap()
{
	if (anisotropicWrap == NULL)
	{
		CreateSamplerState(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_BORDER, &anisotropicWrap);
	}
	return anisotropicWrap;
}

ID3D11SamplerState* CommonStates::AnisotropicClamp()
{
	if (anisotropicClamp == NULL)
	{
		CreateSamplerState(D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_CLAMP, &anisotropicClamp);
	}
	return anisotropicClamp;
}

ID3D11DepthStencilState* CommonStates::DepthNone()
{
	if (depthNone == NULL)
	{
		CreateDepthStencilState(false, false, &depthNone);
	}
	return depthNone;
}

ID3D11DepthStencilState* CommonStates::DepthDefault()
{
	if (depthDefault == NULL)
	{
		CreateDepthStencilState(true, true, &depthDefault);
	}
	return depthDefault;
}

ID3D11DepthStencilState* CommonStates::DepthRead()
{
	if (depthRead == NULL)
	{
		CreateDepthStencilState(true, false, &depthRead);
	}
	return depthRead;
}

