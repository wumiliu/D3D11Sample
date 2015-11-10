#include "Frustum.h"


/// Return the larger of two floats.
inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }


Frustum::Frustum()
{
	Vector3 vPos;
	vPos.Length();
	vPos.x = 1.0f;
}


Frustum::~Frustum()
{
}

void Frustum::Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix& transform)
{
	nearZ = Max(nearZ, 0.0f);
	farZ = Max(farZ, nearZ);
	static const float M_DEGTORAD_2 = XM_PI / 360.0f;    // M_DEGTORAD / 2.f
	float halfViewSize = tanf(fov /2.0f) / zoom;
	Vector3 vNear, vFar;

	vNear.z = nearZ;
	vNear.y = vNear.z * halfViewSize;
	vNear.x = vNear.y * aspectRatio;
	vFar.z = farZ;
	vFar.y = vFar.z * halfViewSize;
	vFar.x = vFar.y * aspectRatio;

	Define(vNear, vFar, transform);
}
void Frustum::DefineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix& transform /*= Matrix::Identity*/)
{
	nearZ = Max(nearZ, 0.0f);
	nearZ = 0.0f;
	farZ = Max(farZ, nearZ);
	float halfViewSize = orthoSize * 0.5f / zoom;

	Vector3 vNear, vFar;

	vNear.z = nearZ;
	vFar.z = farZ;

	vFar.y= vNear.y = halfViewSize;
	vFar.x = vNear.x = vNear.y * aspectRatio;

	Define(vNear, vFar, transform);

}

void Frustum::Define(const Vector3& vNear, const Vector3& vFar, const Matrix& transform)
{
	vertices_[0] = Vector3::Transform(vNear, transform); 
	vertices_[1] = Vector3::Transform(Vector3(vNear.x, -vNear.y, vNear.z), transform);
	vertices_[2] = Vector3::Transform(Vector3(-vNear.x, -vNear.y, vNear.z), transform);
	vertices_[3] = Vector3::Transform(Vector3(-vNear.x, vNear.y, vNear.z), transform);
	vertices_[4] = Vector3::Transform(vFar, transform);
	vertices_[5] = Vector3::Transform(Vector3(vFar.x, -vFar.y, vFar.z), transform);
	vertices_[6] = Vector3::Transform(Vector3(-vFar.x, -vFar.y, vFar.z), transform);
	vertices_[7] = Vector3::Transform(Vector3(-vFar.x, vFar.y, vFar.z), transform);
	UpdatePlanes();
}

void Frustum::UpdatePlanes()
{
	planes_[PLANE_NEAR] = Plane(vertices_[2], vertices_[1], vertices_[0]);
	planes_[PLANE_LEFT] = Plane(vertices_[3], vertices_[7], vertices_[6]);
	planes_[PLANE_RIGHT] = Plane(vertices_[1], vertices_[5], vertices_[4]);
	planes_[PLANE_UP] = Plane(vertices_[0], vertices_[4], vertices_[7]);
	planes_[PLANE_DOWN] = Plane(vertices_[6], vertices_[5], vertices_[1]);
	planes_[PLANE_FAR] = Plane(vertices_[5], vertices_[6], vertices_[7]);
	// Check if we ended up with inverted planes (reflected transform) and flip in that case
	if (planes_[PLANE_NEAR].DotCoordinate(vertices_[5]) < 0.0f)
	{
		for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
		{
			planes_[i].Normal(-planes_[i].Normal());
			planes_[i].D(-planes_[i].D());
		}
	}

}

void Frustum::ConstructFrustum(Matrix viewMatrix, Matrix projectionMatrix)
{
	Matrix matrix = viewMatrix * projectionMatrix;
	// Calculate near plane of frustum.
	m_planes[0].x = matrix(0, 3) + matrix(0, 2);
	m_planes[0].y = matrix(1, 3) + matrix(1, 2);
	m_planes[0].z = matrix(2, 3) + matrix(2, 2);
	m_planes[0].w = matrix(3, 3) + matrix(3, 2);
	m_planes[0].Normalize();

	m_planes[0].x = matrix(0, 2);
	m_planes[0].y = matrix(1, 2);
	m_planes[0].z = matrix(2, 2);
	m_planes[0].w = matrix(3, 2);
	m_planes[0].Normalize();

	// Calculate far plane of frustum.
	m_planes[1].x = matrix(0, 3) - matrix(0, 2);
	m_planes[1].y = matrix(1, 3) - matrix(1, 2);
	m_planes[1].z = matrix(2, 3) - matrix(2, 2);
	m_planes[1].w = matrix(3, 3) - matrix(3, 2);
	m_planes[1].Normalize();


	// Calculate left plane of frustum.
	m_planes[2].x = matrix(0, 3) + matrix(0, 0);
	m_planes[2].y = matrix(1, 3) + matrix(1, 0);
	m_planes[2].z = matrix(2, 3) + matrix(2, 0);
	m_planes[2].w = matrix(3, 3) + matrix(3, 0);
	m_planes[2].Normalize();


	// Calculate right plane of frustum.
	m_planes[3].x = matrix(0, 3) - matrix(0, 0);
	m_planes[3].y = matrix(1, 3) - matrix(1, 0);
	m_planes[3].z = matrix(2, 3) - matrix(2, 0);
	m_planes[3].w = matrix(3, 3) - matrix(3, 0);
	m_planes[3].Normalize();


	// Calculate top plane of frustum.
	m_planes[4].x = matrix(0, 3) - matrix(0, 1);
	m_planes[4].y = matrix(1, 3) - matrix(1, 1);
	m_planes[4].z = matrix(2, 3) - matrix(2, 1);
	m_planes[4].w = matrix(3, 3) - matrix(3, 1);
	m_planes[4].Normalize();


	// Calculate bottom plane of frustum.
	m_planes[5].x = matrix(0, 3) + matrix(0, 1);
	m_planes[5].y = matrix(1, 3) + matrix(1, 1);
	m_planes[5].z = matrix(2, 3) + matrix(2, 1);
	m_planes[5].w = matrix(3, 3) + matrix(3, 1);
	m_planes[5].Normalize();
	//ConstructFrustum1(viewMatrix, projectionMatrix);
}

bool Frustum::CheckPoint(float x, float y, float z)
{
	int i;
	// Check if the point is inside all six planes of the view frustum.
	for (i = 0; i < 6; i++)
	{
		float fDinate = planes_[i].DotCoordinate(Vector3(x, y, z));
		if (fDinate < 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i < 6; i++)
	{
		float fDinate = planes_[i].DotCoordinate(Vector3((xCenter - radius), (yCenter - radius), (zCenter - radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}

		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + radius), (yCenter - radius), (zCenter - radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter - radius), (yCenter + radius), (zCenter - radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + radius), (yCenter + radius), (zCenter - radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter - radius), (yCenter - radius), (zCenter + radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + radius), (yCenter - radius), (zCenter + radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter - radius), (yCenter + radius), (zCenter + radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + radius), (yCenter + radius), (zCenter + radius)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		return false;
	}

	return true;
}

bool Frustum::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;
	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i < 6; i++)
	{
		float fDinate = planes_[i].DotCoordinate(Vector3(xCenter, yCenter, zCenter));
		if (fDinate < -radius)
		{
			return false;
		}
	}
	return true;
}

bool Frustum::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;

	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i < 6; i++)
	{
		float fDinate = planes_[i].DotCoordinate(Vector3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		fDinate = planes_[i].DotCoordinate(Vector3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize)));
		if (fDinate >= 0.0f)
		{
			continue;
		}
		return false;
	}

	return true;
}

void Frustum::ConstructFrustum1(Matrix viewMatrix, Matrix projectionMatrix)
{
	Matrix matrix =  projectionMatrix;
	// Calculate near plane of frustum.
	m_planes[0].x = matrix(0, 3) + matrix(0, 2);
	m_planes[0].y = matrix(1, 3) + matrix(1, 2);
	m_planes[0].z = matrix(2, 3) + matrix(2, 2);
	m_planes[0].w = matrix(3, 3) + matrix(3, 2);
	m_planes[0].Normalize();

	m_planes[0].x = matrix(0, 2);
	m_planes[0].y = matrix(1, 2);
	m_planes[0].z = matrix(2, 2);
	m_planes[0].w = matrix(3, 2);
	m_planes[0].Normalize();

	// Calculate far plane of frustum.
	m_planes[1].x = matrix(0, 3) - matrix(0, 2);
	m_planes[1].y = matrix(1, 3) - matrix(1, 2);
	m_planes[1].z = matrix(2, 3) - matrix(2, 2);
	m_planes[1].w = matrix(3, 3) - matrix(3, 2);
	m_planes[1].Normalize();


	// Calculate left plane of frustum.
	m_planes[2].x = matrix(0, 3) + matrix(0, 0);
	m_planes[2].y = matrix(1, 3) + matrix(1, 0);
	m_planes[2].z = matrix(2, 3) + matrix(2, 0);
	m_planes[2].w = matrix(3, 3) + matrix(3, 0);
	m_planes[2].Normalize();


	// Calculate right plane of frustum.
	m_planes[3].x = matrix(0, 3) - matrix(0, 0);
	m_planes[3].y = matrix(1, 3) - matrix(1, 0);
	m_planes[3].z = matrix(2, 3) - matrix(2, 0);
	m_planes[3].w = matrix(3, 3) - matrix(3, 0);
	m_planes[3].Normalize();


	// Calculate top plane of frustum.
	m_planes[4].x = matrix(0, 3) - matrix(0, 1);
	m_planes[4].y = matrix(1, 3) - matrix(1, 1);
	m_planes[4].z = matrix(2, 3) - matrix(2, 1);
	m_planes[4].w = matrix(3, 3) - matrix(3, 1);
	m_planes[4].Normalize();


	// Calculate bottom plane of frustum.
	m_planes[5].x = matrix(0, 3) + matrix(0, 1);
	m_planes[5].y = matrix(1, 3) + matrix(1, 1);
	m_planes[5].z = matrix(2, 3) + matrix(2, 1);
	m_planes[5].w = matrix(3, 3) + matrix(3, 1);
	m_planes[5].Normalize();
}


