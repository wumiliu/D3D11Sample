#pragma once
#include "HpD3D9Type.h"
#include <functional>
#include <memory>
using namespace DirectX;
class D3D11RendererMaterial;
class  GeometricPrimitive
{
public:
	GeometricPrimitive();
	~GeometricPrimitive();
	static std::unique_ptr<GeometricPrimitive> CreateCube(float size = 1, bool rhcoords = true);
	
	//圆
	static std::unique_ptr<GeometricPrimitive> CreateSphere( float diameter = 1, size_t tessellation = 16, bool rhcoords = true);
	static std::unique_ptr<GeometricPrimitive> CreateGeoSphere( float diameter = 1, size_t tessellation = 3, bool rhcoords = true);

	//圆柱
	static std::unique_ptr<GeometricPrimitive> CreateCylinder( float height = 1, float diameter = 1, size_t tessellation = 32, bool rhcoords = true);
	//圆锥
	static std::unique_ptr<GeometricPrimitive> CreateCone( float diameter = 1, float height = 1, size_t tessellation = 32, bool rhcoords = true);
	
	//圆环
	static std::unique_ptr<GeometricPrimitive> CreateTorus( float diameter = 1, float thickness = 0.333f, size_t tessellation = 32, bool rhcoords = true);
	
	//四面体
	static std::unique_ptr<GeometricPrimitive> CreateTetrahedron( float size = 1, bool rhcoords = true);
	//八面体
	static std::unique_ptr<GeometricPrimitive> CreateOctahedron( float size = 1, bool rhcoords = true);
	//12面体
	static std::unique_ptr<GeometricPrimitive> CreateDodecahedron(float size = 1, bool rhcoords = true);
	//20面体
	static std::unique_ptr<GeometricPrimitive> CreateIcosahedron( float size = 1, bool rhcoords = true);
	//茶壶
	static GeometricPrimitivePtr CreateTeapot(float size = 1, size_t tessellation = 8, bool rhcoords = true);

	void Render(D3D11RendererMaterial* pMaterial);
	// Private implementation.
	class Impl;

	std::unique_ptr<Impl> pImpl;
};

