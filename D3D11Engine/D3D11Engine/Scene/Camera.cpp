#include "Camera.h"

#include "HpNode.h"

#include "Renderer/VertexTypes.h"
#include "Renderer/Sprite.h"
Camera::Camera() :
mDirtyProj(true),
mDirtyView(true),
orthographic_(false),
frustumDirty_(true)
{
//	SetType("Camera");
}


Camera::~Camera()
{

}

void Camera::LookAt(Vector3 pos, Vector3 target, Vector3 up)
{
	m_Pos = pos;
	m_Target = target;
	m_Up = up;
	mDirtyView = true;
	frustumDirty_ = true;
}

void Camera::updateInternals()
{
	if (mDirtyView)
	{

		m_vLookVector = (m_Target - m_Pos);
		m_vLookVector.Normalize();
		m_vRightVector = (m_Up.Cross(m_vLookVector));
		m_vRightVector.Normalize();
		m_vUpVector = m_vLookVector.Cross(m_vRightVector);

		//	把摄像机 平移回原点，在旋转根坐标轴重合
		// Rx  Ry  Rz									1 0 0
		// Ux  Uy Uz    * M == >				0 1 0
		// Lx  Ly   Lz									1 0 1
		//
		// M 为旋转的逆矩阵， 由于旋转矩阵是正交矩阵， 正交矩阵的逆矩阵 就是 它的转置矩阵
		//
		Matrix ViewMatrix(m_vRightVector, m_vUpVector, m_vLookVector);
		Matrix m = Matrix::CreateTranslation(-m_Pos);
		mViewMatrix = m * ViewMatrix.Transpose();


		mInvViewMatrix = mViewMatrix.Invert();
		mDirtyView = false;
	}
	if (mDirtyProj)
	{
		if(orthographic_)
		{
			float h = (1.0f / (orthoSize_ * 0.5f)) * 1.0f;
			float w = h / mAspectRatio;
			float q, r;

			if (false)
			{
				q = 2.0f / mFarPlane;
				r = -1.0f;
			}
			else
			{
				q = 1.0f / mFarPlane;
				r = 0.0f;
			}

			mProjMatrix.m[0][0] = w;
			mProjMatrix.m[0][3] = 0.0f;
			mProjMatrix.m[1][1] = h;
			mProjMatrix.m[1][3] = 0.0f;
			mProjMatrix.m[2][2] = q;
			mProjMatrix.m[2][3] = r;
			mProjMatrix.m[3][3] = 1.0f;

			//float h = (1.0f / (orthoSize_ * 0.5f));
			//float w = h ;
			//mProjMatrix = XMMatrixOrthographicLH(w, h, mNearPlane, mFarPlane);
		}
		else
		{
			float    SinFov;
			float    CosFov;
			XMScalarSinCos(&SinFov, &CosFov, 0.5f * mFOV);

			float Height = CosFov / SinFov;
			float Width = Height / mAspectRatio;
			float fRange = mFarPlane / (mFarPlane - mNearPlane);

			mProjMatrix.m[0][0] = Width;
			mProjMatrix.m[0][1] = 0.0f;
			mProjMatrix.m[0][2] = 0.0f;
			mProjMatrix.m[0][3] = 0.0f;

			mProjMatrix.m[1][0] = 0.0f;
			mProjMatrix.m[1][1] = Height;
			mProjMatrix.m[1][2] = 0.0f;
			mProjMatrix.m[1][3] = 0.0f;

			mProjMatrix.m[2][0] = 0.0f;
			mProjMatrix.m[2][1] = 0.0f;
			mProjMatrix.m[2][2] = fRange;
			mProjMatrix.m[2][3] = 1.0f;

			mProjMatrix.m[3][0] = 0.0f;
			mProjMatrix.m[3][1] = 0.0f;
			mProjMatrix.m[3][2] = -fRange * mNearPlane;
			mProjMatrix.m[3][3] = 0.0f;

			//mProjMatrix = XMMatrixPerspectiveFovLH(mFOV, mAspectRatio, mNearPlane, mFarPlane);
		}
		mDirtyProj = false;
	}
}

void Camera::MoveAlongRightVec(float fUnits)
{
	//直接乘以fUnits的量来累加就行了
	m_Pos += m_vRightVector * fUnits;
	m_Target += m_vRightVector * fUnits;
	mDirtyView = true;
}

void Camera::MoveAlongUpVec(float fUnits)
{
	m_Pos += m_vUpVector * fUnits;
	m_Target += m_vUpVector * fUnits;
	mDirtyView = true;

}

void Camera::MoveAlongLookVec(float fUnits)
{
	m_Pos += m_vLookVector * fUnits;
	m_Target += m_vLookVector * fUnits;
	mDirtyView = true;
}

const Frustum& Camera::GetFrustum()
{
	if (frustumDirty_)
	{
		GetView();
		Vector3 eyePos = m_Pos;
		if (!orthographic_)
		{
			frustum_.Define(mFOV, mAspectRatio, 1.0f, mNearPlane, mFarPlane, mInvViewMatrix);
			frustum_.ConstructFrustum(mViewMatrix, mProjMatrix);
		}
		else
		{
			frustum_.DefineOrtho(orthoSize_, mAspectRatio, 1.0f, mNearPlane, mFarPlane, mInvViewMatrix);
		}
		frustumDirty_ = false;
	}
	return frustum_;
}


DirectX::SimpleMath::Ray Camera::CalcPickingRay(int x, int y, Matrix W /*= Matrix::Identity*/)
{

	XMMATRIX view = GetView();// g_objTrackballCameraController.View();
	//投影变换
	Matrix P = GetProjection();// g_objTrackballCameraController.Proj();

	float vx = (+2.0f*x / mClientWidth - 1.0f) / (P(0, 0));
	float vy = (-2.0f*y / mClientHeight + 1.0f) / (P(1, 1));
	// Ray definition in view space.
	XMVECTOR rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR rayDir = XMVectorSet(vx, vy, 1.0f, 0.0f);

	XMMATRIX invP = XMMatrixInverse(&XMMatrixDeterminant(P), P);

	// Tranform ray to local space of Mesh.
	XMMATRIX V = view;
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(V), V);


	XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

	XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);


	rayOrigin = XMVector3TransformCoord(rayOrigin, toLocal);
	rayDir = XMVector3TransformNormal(rayDir, toLocal);

	// Make the ray direction unit length for the intersection tests.
	rayDir = XMVector3Normalize(rayDir);

	DirectX::SimpleMath::Ray ray(rayOrigin, rayDir);
	return ray;
}

const Matrix& Camera::GetView() const
{
	if (mDirtyView)
	{
		// Note: view matrix is unaffected by node or parent scale
		mInvViewMatrix = GetEffectiveWorldTransform();
		mViewMatrix = mInvViewMatrix.Invert();
		mDirtyView = false;
	}

	return mViewMatrix;
}

Matrix Camera::GetEffectiveWorldTransform() const
{
	if (node_)
	{
		return node_->GetWorldTransform();
	}
	return Matrix::Identity;
}

void Camera::OnNodeSet(HpNode * node)
{
	if (node)
		node->AddListener(this);
}

void Camera::OnMarkedDirty(HpNode* node)
{
	mDirtyView = true;
	frustumDirty_ = true;
}

DirectX::SimpleMath::Vector3 Camera::ScreenToWorldPoint(const Vector3& screenPos) const
{
	Ray ray = GetScreenRay(screenPos.x, screenPos.y);
	return ray.position +ray.direction * screenPos.z;
}

DirectX::SimpleMath::Ray Camera::GetScreenRay(float x, float y) const
{
	Ray ret;
	Matrix mInvProMatrix = mProjMatrix.Invert();

	Matrix viewProjInverse = mInvProMatrix* mInvViewMatrix;
	// The parameters range from 0.0 to 1.0. Expand to normalized device coordinates (-1.0 to 1.0) & flip Y axis


	x = 2.0f * x - 1.0f;
	y = 1.0f - 2.0f * y;
	Vector3 vNear(x, y, 0.0f);
	Vector3 vFar(x, y, 1.0f);
	Vector3 VText = Vector3::Transform(vNear, mInvProMatrix);
	ret.position = Vector3::Transform(vNear, viewProjInverse);
	ret.direction = Vector3::Transform(vFar, viewProjInverse) - ret.position;
	ret.direction.Normalize();
	return ret;

}

void Camera::DrawDebugGeometry(Matrix VP, bool bShowClip /*= false*/, Vector4 color /*= Vector4::One*/)
{
	GetFrustum();
	const Vector3* vertices = frustum_.vertices_;
	//XMFLOAT4 color = { 1, 1, 1, 1 };
	VertexPositionColorTexture posVertices[24] =
	{
		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[1], color, XMFLOAT2(0, 1) },
		{ vertices[1], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[0], color, XMFLOAT2(0, 1) },

		{ vertices[4], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[7], color, XMFLOAT2(0, 1) },
		{ vertices[7], color, XMFLOAT2(0, 1) },
		{ vertices[4], color, XMFLOAT2(0, 1) },

		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[4], color, XMFLOAT2(0, 1) },
		{ vertices[1], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[7], color, XMFLOAT2(0, 1) },
	};
	Matrix mWorld;
	color = { 1.0f, 0.0f, 0.0f, 0.1f };
	VertexPositionColorTexture pVertices[36] =
	{
		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[1], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[3], color, XMFLOAT2(0, 1) },


		{ vertices[4], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[4], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[7], color, XMFLOAT2(0, 1) },


		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) },
		{ vertices[7], color, XMFLOAT2(0, 1) },


		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[1], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[4], color, XMFLOAT2(0, 1) },

		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[0], color, XMFLOAT2(0, 1) },
		{ vertices[4], color, XMFLOAT2(0, 1) },
		{ vertices[3], color, XMFLOAT2(0, 1) },
		{ vertices[4], color, XMFLOAT2(0, 1) },
		{ vertices[7], color, XMFLOAT2(0, 1) },

		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[1], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[2], color, XMFLOAT2(0, 1) },
		{ vertices[5], color, XMFLOAT2(0, 1) },
		{ vertices[6], color, XMFLOAT2(0, 1) } };


	Matrix WVP = VP;
	g_objSprite.DrawPrimitiveUP(PRIMITIVE_LINELIST, 24, posVertices, WVP);
	if (bShowClip)
	{
		g_objSprite.DrawPrimitiveUP(PRIMITIVE_TRIANGLELIST, 36, pVertices, WVP);
	}

	if (!_debug.GetInitState())
	{
		_debug.InitResource(GEOMETRY_TYPE_BOX);
		_debug.SetTexture("Data\\Texture\\ice.dds");

	}
	_debug.Render(Matrix::Identity, Matrix::Identity, mInvViewMatrix*WVP);
}

void Camera::GetFrustumSize(Vector3& fNear, Vector3& fFar) const
{
	fNear.z = mNearPlane;
	fFar.z = mFarPlane;

	float halfViewSize = tanf(mFOV / 2.0f);
	Vector3 vNear, vFar;

	fNear.y = fNear.z * halfViewSize;
	fNear.x = fNear.y* mAspectRatio;

	fFar.y = fFar.z * halfViewSize;
	fFar.x = fFar.y* mAspectRatio;

}

