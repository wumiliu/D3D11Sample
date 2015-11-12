#include "D3D11RendererMaterial.h"
#include "BaseCode/BaseFunc.h"
#include "DeviceManager.h"




D3D11RendererMaterial::D3D11RendererMaterial(const RendererMaterialDesc& desc)
{
	m_pInputLayout = NULL;
	loadShaders(desc);
}


D3D11RendererMaterial::~D3D11RendererMaterial()
{
	SAFE_RELEASE(m_pInputLayout);
}

void D3D11RendererMaterial::loadShaders(const RendererMaterialDesc& desc)
{
	FILE * m_IFileRead = NULL;
	const char* strFileName = desc.strHLSLPath.c_str();
	fopen_s(&m_IFileRead, strFileName, "rb");
	if (m_IFileRead == NULL)
	{
		printf("not find file %s\n", strFileName);
		return;
	}
	fseek(m_IFileRead, 0, SEEK_END);
	int fileSize = ftell(m_IFileRead);
	unsigned char* sourceBuffer = new unsigned char[fileSize + 1];
	memset(sourceBuffer, 0, fileSize + 1);
	fseek(m_IFileRead, 0, SEEK_SET);
	fread(sourceBuffer, sizeof(char), fileSize, m_IFileRead);
	fclose(m_IFileRead);
	// Comment out the unneeded shader function
	string vsSourceCode_ = (char*)sourceBuffer;
	string psSourceCode_ = (char*)sourceBuffer;
	delete sourceBuffer;
	sourceBuffer = NULL;

	CommentOutFunction(vsSourceCode_, "void PS(");
	CommentOutFunction(psSourceCode_, "void VS(");
	vsShader.Compile(vsSourceCode_, strFileName, VS, "");
	psShader.Compile(psSourceCode_, strFileName, PS, "");

}

void D3D11RendererMaterial::SetConstantBuffers(ShaderType type_, const char* name, void* pBuffer, int nSize /*= 0*/)
{
	StringHash varName(name);
	Shader& shader_ = type_ == VS ? vsShader : psShader;
	HP_HashMap<unsigned, ShaderParameter>::iterator iter = shader_.parameters_.find(varName);
	if (iter != shader_.parameters_.end())
	{
		ShaderParameter parameter = iter->second;
		ConstantBufferPtr buffer_ = shader_.constantBufferShaders[parameter.buffer_];
		if (buffer_ != NULL)
		{
			if (nSize == 0)
			{
				nSize = parameter.size_;
			}
			void* dataPtr = buffer_->Map();
			unsigned char*  pDataBuffer = (unsigned char*)dataPtr;
			memcpy_s(pDataBuffer + parameter.offset_, nSize, pBuffer, nSize);
		}
	}
}

void D3D11RendererMaterial::VSSetConstantBuffers(const char* name, void* pBuffer, int nSize /*= 0*/)
{
	SetConstantBuffers(VS, name, pBuffer, nSize);
}
void D3D11RendererMaterial::PSSetConstantBuffers(const char* name, void* pBuffer, int nSize /*= 0*/)
{
	SetConstantBuffers(PS, name, pBuffer, nSize);
}

void D3D11RendererMaterial::Apply(bool bTest)
{
	for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
	{
		if (vsShader.constantBufferShaders[i] > 0)
		{
			vsShader.constantBufferShaders[i]->Apply();
		}
		if (psShader.constantBufferShaders[i] > 0)
		{
			psShader.constantBufferShaders[i]->Apply();
		}
	}

	g_objDeviecManager.GetImmediateContext()->VSSetShader(vsShader.m_vertexShader, NULL, 0);
	if (bTest)
	{
		g_objDeviecManager.GetImmediateContext()->PSSetShader(NULL, NULL, 0);
	}
	else
	{
		g_objDeviecManager.GetImmediateContext()->PSSetShader(psShader.m_pixelShader, NULL, 0);
	}


}

void D3D11RendererMaterial::PSSetShaderResources(TextureUnit texture, ID3D11ShaderResourceView* pShaderResourceViews)
{
	bool bTexture = psShader.useTextureUnit_[texture];
	if (bTexture)
	{
		if (pShaderResourceViews)
		{
			g_objDeviecManager.GetImmediateContext()->PSSetShaderResources(texture, 1, &pShaderResourceViews);
		}
		else
		{
			printf("pShaderResourceViews is null");
		}
	}
	else
	{
		printf("PSSetShaderResources not texture");
	}
}



