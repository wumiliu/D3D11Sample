#ifndef _GEOMETRY_GENS_H_
#define _GEOMETRY_GENS_H_
#include "HpD3D9Type.h"
#include <vector>

namespace GeoGen
{
	struct Vertex
	{
		Vertex(){}
		Vertex(const XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT3 _tangent, XMFLOAT2 _tex):
			pos(_pos),normal(_normal),tangent(_tangent),tex(_tex){}

		XMFLOAT3	pos;
		XMFLOAT3	normal;
		XMFLOAT3	tangent;
		XMFLOAT2	tex;
	};

	//Mesh data used to store vertex and index infos
	struct MeshData
	{
		std::vector<Vertex>	vertices;
		std::vector<UINT>	indices;
	};

	//Create a cube
	void CreateBox(float width, float height, float depth, MeshData &mesh);
	
	//Create a grid of size:width, height. With m * n sub-grids.
	void CreateGrid(float width, float height, UINT m, UINT n, MeshData &mesh);
	
	//Cylinder
	void CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	//Add top
	void AddCylinderTopCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	//Add bottom
	void AddCylinderBottomCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	
	//Sphere
	void CreateSphere(float radius, int slice, int stack, MeshData &mesh);
};


#endif