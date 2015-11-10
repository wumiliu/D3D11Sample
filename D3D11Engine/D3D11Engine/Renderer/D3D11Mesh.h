#pragma once
#include "HpD3D9Type.h"
#include "BaseCode/GeometryGenerator.h"


class D3D11Mesh
{
public:
	D3D11Mesh();
	~D3D11Mesh();
	bool BuildBuffers(const GeometryGenerator::MeshData& mesh);
	void Render();
private:


protected:
	ID3D11Buffer	*m_VB;
	ID3D11Buffer	*m_IB;
};

