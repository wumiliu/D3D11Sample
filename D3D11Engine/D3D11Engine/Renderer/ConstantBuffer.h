#pragma once
#include "HpD3D9Type.h"
#include "GraphicsDefs.h"
class ConstantBuffer
{
public:
	ConstantBuffer(UINT StartSlot_, ShaderType type_);
	~ConstantBuffer();

	void Release();
	void SetSize(int size_);
	void* Map();
	void Apply();
	/// Direct3D object.
	ID3D11Buffer* pConstantBuffer;
private:
	bool bMap;
	void* dataPtr;
	UINT StartSlot;
	ShaderType Type;
};
typedef std::shared_ptr<ConstantBuffer>ConstantBufferPtr;
