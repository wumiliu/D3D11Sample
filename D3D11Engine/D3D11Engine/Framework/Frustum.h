#pragma once
#include "HpD3D9Type.h"


/// Frustum planes.
enum FrustumPlane
{
	PLANE_NEAR = 0,
	PLANE_FAR,
	PLANE_LEFT,
	PLANE_RIGHT,
	PLANE_UP,
	PLANE_DOWN,

};

static const unsigned NUM_FRUSTUM_PLANES = 6;
static const unsigned NUM_FRUSTUM_VERTICES = 8;

class Frustum
{
public:
	Frustum();
	~Frustum();
	void Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix& transform = Matrix::Identity);
	void Define(const Vector3& vNear, const Vector3& vFar, const Matrix& transform);
	void UpdatePlanes();
	void ConstructFrustum(Matrix viewMatrix, Matrix projectionMatrix);
	void ConstructFrustum1(Matrix viewMatrix, Matrix projectionMatrix);

	void DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix& transform = Matrix::Identity);



	bool CheckPoint(float x, float y, float z);
	bool CheckCube(float xCenter, float yCenter, float zCenter, float radius);
	bool CheckSphere(float xCenter, float yCenter, float zCenter, float radius);
	bool CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize);


	/// Frustum vertices.
	Vector3 vertices_[NUM_FRUSTUM_VERTICES];
	/// Frustum planes.
	Plane planes_[NUM_FRUSTUM_PLANES];
	Plane m_planes[6];
	Plane m_planes1[6];

};

