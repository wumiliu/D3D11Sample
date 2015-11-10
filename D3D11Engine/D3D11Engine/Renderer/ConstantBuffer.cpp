#include "ConstantBuffer.h"
#include "DeviceManager.h"

ConstantBuffer::ConstantBuffer(UINT StartSlot_)
{
	pConstantBuffer = NULL;
	bMap = false;
	dataPtr = NULL;
	StartSlot = StartSlot_;
}


ConstantBuffer::~ConstantBuffer()
{
	Release();
}

void ConstantBuffer::Release()
{
	SAFE_RELEASE(pConstantBuffer);
	bMap = false;
	dataPtr = NULL;
}

void ConstantBuffer::SetSize(int size_)
{
	Release();
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof bufferDesc);

	bufferDesc.ByteWidth = size_;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	g_objDeviecManager.GetDevice()->CreateBuffer(&bufferDesc, 0, (ID3D11Buffer**)&pConstantBuffer);
	if (!pConstantBuffer)
	{
		printf("Failed to create constant buffer");
		return ;
	}
}

void* ConstantBuffer::Map()
{
	if (bMap && dataPtr)
	{
		return dataPtr;
	}
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	g_objDeviecManager.GetImmediateContext()->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	bMap = true;
	dataPtr = mappedResource.pData;
	return mappedResource.pData;
}

void ConstantBuffer::Apply()
{
	if (bMap)
	{
		bMap = false;
		dataPtr = NULL;
		g_objDeviecManager.GetImmediateContext()->Unmap(pConstantBuffer, 0);
	}
	g_objDeviecManager.GetImmediateContext()->VSSetConstantBuffers(StartSlot, 1, &pConstantBuffer);
}
