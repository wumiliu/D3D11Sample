#include "Shader.h"
#include "BaseCode/BaseFunc.h"
#include "DeviceManager.h"

#pragma comment(lib,"D3DCompiler.lib")
#pragma comment(lib,"dxguid.lib")

Shader::Shader()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
	for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
		useTextureUnit_[i] = false;
	for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
		constantBufferSizes_[i] = 0;
}

Shader::~Shader()
{
	SAFE_RELEASE(m_vertexShader);
	SAFE_RELEASE(m_pixelShader);
	for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
	{
		if (constantBufferShaders[i] != NULL)
		{
			constantBufferShaders[i]->Release();
		}
	}
}

bool Shader::Compile(const String& binaryShaderName, const char* pszName, ShaderType type_, std::string defines_)
{
	sourceCode = binaryShaderName;
	const char* entryPoint = 0;
	const char* profile = 0;
	if (type_ == VS)
	{
		entryPoint = "VS";
		profile = "vs_4_0";
	}
	else if (type_ == PS)
	{
		entryPoint = "PS";
		profile = "ps_4_0";
	}
	vector<string> defines;
	Split(defines_, defines, ',');
	unsigned flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
	flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	std::vector<D3D_SHADER_MACRO> macros;
	for (unsigned i = 0; i < defines.size(); ++i)
	{
		D3D_SHADER_MACRO macro;
		macro.Name = defines[i].c_str();
		macro.Definition = "1";
		macros.push_back(macro);
	}
	D3D_SHADER_MACRO endMacro;
	endMacro.Name = 0;
	endMacro.Definition = 0;
	macros.push_back(endMacro);
	ID3DBlob* shaderCode = 0;
	ID3DBlob* errorMsgs = 0;
	HRESULT result =
		D3DCompile(sourceCode.c_str(), sourceCode.size(),
		pszName,
		&macros[0],
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		profile,
		flags,
		0,
		&shaderCode, &errorMsgs);
	if (result != S_OK)
	{
		printf("Error compiling shader.  Check shader-error.txt for message.\n");
		printf("%s\n", (char*)(errorMsgs->GetBufferPointer()));
		return false;
	}
	unsigned char* bufData = (unsigned char*)shaderCode->GetBufferPointer();
	unsigned bufSize = (unsigned)shaderCode->GetBufferSize();
	ParseParameters(bufData, bufSize, type_);
	CalculateConstantBufferSizes(type_);
	byteCode_.resize((unsigned)shaderCode->GetBufferSize());
	memcpy(&byteCode_[0], shaderCode->GetBufferPointer(), byteCode_.size());
	shaderCode->Release();
	CreateGPUBuffer(type_);

	return true;
}

void Shader::ParseParameters(unsigned char* bufData, unsigned bufSize, ShaderType type_)
{
	ID3D11ShaderReflection* reflection = 0;
	D3D11_SHADER_DESC shaderDesc;

	D3DReflect(bufData, bufSize, IID_ID3D11ShaderReflection, (void**)&reflection);
	if (!reflection)
	{
		printf("Failed to reflect vertex shader's input signature");
		return;
	}

	reflection->GetDesc(&shaderDesc);

	HP_HashMap<String, unsigned> cbRegisterMap;

	for (unsigned i = 0; i < shaderDesc.BoundResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		reflection->GetResourceBindingDesc(i, &resourceDesc);
		String resourceName(resourceDesc.Name);
		if (resourceDesc.Type == D3D_SIT_CBUFFER)
			cbRegisterMap[resourceName] = resourceDesc.BindPoint;
		else if (resourceDesc.Type == D3D_SIT_SAMPLER && resourceDesc.BindPoint < MAX_TEXTURE_UNITS)
			useTextureUnit_[resourceDesc.BindPoint] = true;
	}

	for (unsigned i = 0; i < shaderDesc.ConstantBuffers; ++i)
	{
		ID3D11ShaderReflectionConstantBuffer* cb = reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC cbDesc;
		cb->GetDesc(&cbDesc);
		unsigned cbRegister = cbRegisterMap[String(cbDesc.Name)];

		for (unsigned j = 0; j < cbDesc.Variables; ++j)
		{
			ID3D11ShaderReflectionVariable* var = cb->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC varDesc;
			var->GetDesc(&varDesc);
			String varName(varDesc.Name);
			parameters_[StringHash(varName)] = ShaderParameter(type_, varName, cbRegister, varDesc.StartOffset, varDesc.Size);
		}
	}
	reflection->Release();
}

void Shader::CalculateConstantBufferSizes(ShaderType type_)
{
	for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
	{
		constantBufferSizes_[i] = 0;
		constantBufferShaders[i] = NULL;
	}
	for (HP_HashMap<unsigned, ShaderParameter>::iterator i = parameters_.begin(); i != parameters_.end(); ++i)
	{
		int nSize = i->second.buffer_;
		if (i->second.buffer_ < MAX_SHADER_PARAMETER_GROUPS)
		{
			unsigned oldSize = constantBufferSizes_[i->second.buffer_];
			unsigned paramEnd = i->second.offset_ + i->second.size_;
			if (paramEnd > oldSize)
				constantBufferSizes_[i->second.buffer_] = paramEnd;
		}
	}
	for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
	{
		if (constantBufferSizes_[i] > 0)
		{
			ConstantBufferPtr newShader(new ConstantBuffer(i,type_));
			newShader->SetSize(constantBufferSizes_[i]);
			constantBufferShaders[i] = newShader;
		}
	}
}

HRESULT Shader::CreateGPUBuffer(ShaderType type_)
{
	if (type_ == VS)
	{
		HRESULT result = g_objDeviecManager.GetDevice()->CreateVertexShader(
			&byteCode_[0],
			byteCode_.size(),
			(ID3D11ClassLinkage *)NULL,
			&m_vertexShader);
		return result;
	}
	else if (type_ == PS)
	{
		HRESULT result = g_objDeviecManager.GetDevice()->CreatePixelShader(
			&byteCode_[0],
			byteCode_.size(),
			(ID3D11ClassLinkage *)NULL,
			&m_pixelShader);
		return result;
	}
	return S_FALSE;
}
