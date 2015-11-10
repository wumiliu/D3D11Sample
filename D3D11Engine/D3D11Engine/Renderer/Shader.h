#pragma once
#include "HpD3D9Type.h"
#include "GraphicsDefs.h"
#include "ConstantBuffer.h"

struct ShaderParameter
{
	ShaderParameter() :
		type_(VS),
		buffer_(0),
		offset_(0),
		size_(0),
		bufferPtr_(0)
	{
	}
	ShaderParameter(ShaderType type, const String& name, unsigned buffer, unsigned offset, unsigned size, ConstantBufferPtr ptr = 0) :
		type_(type),
		name_(name),
		buffer_(buffer),
		offset_(offset),
		size_(size),
		bufferPtr_(ptr)
	{

	}
	/// %Shader type.
	ShaderType type_;
	/// Name of the parameter.
	String name_;
	/// Constant buffer index.
	unsigned buffer_;
	/// Offset in constant buffer.
	unsigned offset_;
	/// Size of parameter in bytes.
	unsigned size_;
	/// Constant buffer pointer. Defined only in shader programs.
	ConstantBufferPtr bufferPtr_;
};
class Shader
{
	friend class D3D11RendererMaterial;
public:
	Shader();
	~Shader();
	bool Compile(const String& binaryShaderName,const char* pszName, ShaderType type_, std::string defines_);
private:
	/// Inspect the constant parameters and input layout (if applicable) from the shader bytecode.
	void ParseParameters(unsigned char* bufData, unsigned bufSize, ShaderType type_);
	void CalculateConstantBufferSizes(ShaderType type_);
	HRESULT CreateGPUBuffer(ShaderType type_);

private:
	/// Source code adapted for vertex shader.
	String sourceCode;
	/// Bytecode. Needed for inspecting the input signature and parameters.
	std::vector<unsigned char> byteCode_;
	HP_HashMap<unsigned, ShaderParameter> parameters_;
	/// Texture unit use flags.
	bool useTextureUnit_[MAX_TEXTURE_UNITS];
	/// Constant buffer sizes. 0 if a constant buffer slot is not in use.
	unsigned constantBufferSizes_[MAX_SHADER_PARAMETER_GROUPS];
	ConstantBufferPtr constantBufferShaders[MAX_SHADER_PARAMETER_GROUPS];
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

};

