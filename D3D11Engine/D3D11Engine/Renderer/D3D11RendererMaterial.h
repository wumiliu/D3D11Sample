#pragma once
#include "HpD3D9Type.h"

#include "Shader.h"

struct RendererMaterialDesc
{
	RendererMaterialDesc()
	{
		strHLSLPath = "";
		vsDefines = "FXAA_HLSL_4=1,FXAA_HLSL_5=0";
		psDefines = "FXAA_HLSL_4=1,FXAA_HLSL_5=0";
	}
	std::string strHLSLPath;
	std::string vsDefines;
	std::string psDefines;
};

class D3D11RendererMaterial
{
public:
	D3D11RendererMaterial(const RendererMaterialDesc& desc);
	~D3D11RendererMaterial();

	void VSSetConstantBuffers(const char* name, void* pBuffer, int nSize = 0);
	void PSSetConstantBuffers(const char* name, void* pBuffer, int nSize = 0);

	void PSSetShaderResources(TextureUnit texture, ID3D11ShaderResourceView* ppShaderResourceViews);

	void Apply(bool bTest = false);
	template< class VertexTypes >
	ID3D11InputLayout* getLayout();
protected:
	void loadShaders(const RendererMaterialDesc& desc);
	void SetConstantBuffers(ShaderType type_,const char* name, void* pBuffer, int nSize = 0);

private:
	Shader vsShader;
	Shader psShader;
	ID3D11InputLayout * m_pInputLayout;
};

template< class VertexTypes >
ID3D11InputLayout* D3D11RendererMaterial::getLayout()
{
	if (!m_pInputLayout)
	{
		LayoutVector vecLayout;
		for (int i = 0; i < VertexTypes::InputElementCount; ++i)
		{
			vecLayout.push_back(VertexTypes::InputElements[i]);
		}
		g_objDeviecManager.CreateInputLayout(vecLayout, &vsShader.byteCode_[0], vsShader.byteCode_.size(), & m_pInputLayout);
	}
	return m_pInputLayout;
}

