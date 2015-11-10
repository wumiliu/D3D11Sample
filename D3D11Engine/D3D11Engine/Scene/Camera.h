#pragma once

#include "HpD3D9Type.h"
#include "Framework/Frustum.h"
#include "Component.h"

class Camera : public Component
{
	OBJECT(Camera);

public:
	Camera();
	~Camera();

	void setAspectRatio(float fAspectRatio){ mAspectRatio = fAspectRatio; mDirtyProj = true; }
	float getAspectRatio(){ return mAspectRatio; }
	void SetOrthographic(bool enable){ orthographic_ = enable; }
	void SetOrthoSize(float fSize){ orthoSize_ = fSize; mDirtyProj = true; }
	float getOrthoSize(){ return orthoSize_; }

	void setFOV(float fov){ mFOV = fov; mDirtyProj = true; }
	float getFOV(){ return mFOV; }

	void setNearPlane(float d){ mNearPlane = d; mDirtyProj = true; }
	float getNearPlane(){ return mNearPlane; }

	void setFarPlane(float d){ mFarPlane = d; mDirtyProj = true; }
	float getFarPlane(){ return mFarPlane; }
	void SetViewSize(int nWidth, int nHeight){ mClientWidth = nWidth; mClientHeight = nHeight; }
	void ProjParams(float fov, float aspect, float near_plane, float far_plane)
	{
		setFOV(fov);
		setAspectRatio(aspect);
		setNearPlane(near_plane);
		setFarPlane(far_plane);
	}
	void LookAt(Vector3 pos, Vector3 target, Vector3 up=Vector3::Up);
	const 		Matrix& getProjMatrix()		const
	{
		if (mDirtyProj)
			const_cast<Camera*>(this)->updateInternals();
		return mProjMatrix;
	}
	const Matrix& getViewMatrix()const
	{
		if (mDirtyView)
			const_cast<Camera*>(this)->updateInternals();
		//if (orthographic_)
		//	return Matrix::Identity;
		return mViewMatrix;
	}
	/// Return view matrix.
	const Matrix& GetView() const;
	Matrix GetEffectiveWorldTransform()const;
	const Frustum& GetFrustum();
	const Matrix& GetProjection() const{ return getProjMatrix(); }

	void DrawDebugGeometry(bool bShowClip = false, Vector4 color = { 1, 0, 0, 1 });
	void Pick(int x, int y);
	DirectX::SimpleMath::Ray CalcPickingRay(int x, int y, Matrix W = Matrix::Identity);

	/// Return ray corresponding to normalized screen coordinates (0.0 - 1.0).
	Ray GetScreenRay(float x, float y) const;

	// Convert normalized screen coordinates (0.0 - 1.0) and depth to a world space point.
	Vector3 ScreenToWorldPoint(const Vector3& screenPos) const;

public:
	// 沿各分量平移的三个函数   
	void MoveAlongRightVec(float fUnits);   // 沿right向量移动   
	void MoveAlongUpVec(float fUnits);      // 沿up向量移动   
	void MoveAlongLookVec(float fUnits);    // 沿look向量移动   

private:
	void						updateInternals();

protected:
	/// Handle node being assigned.
	virtual void OnNodeSet(HpNode * node);
	/// Handle node transform being dirtied.
	virtual void OnMarkedDirty(HpNode* node);

public:
	Vector3 m_Pos;
	Vector3 m_Target;
	Vector3 m_Up;

	Vector3             m_vRightVector;        // 右分量向量   
	Vector3             m_vUpVector;           // 上分量向量   
	Vector3             m_vLookVector;         // 观察方向向量   


	float						mFOV;
	//// Aspect Ratio (Width/Height)
	float						mAspectRatio;
	float						mNearPlane;
	float						mFarPlane;

	mutable Matrix mProjMatrix;
	mutable Matrix mViewMatrix;
	mutable Matrix mInvViewMatrix;


	bool						mDirtyProj;
	mutable bool						mDirtyView;
	/// Frustum dirty flag.
	mutable bool frustumDirty_;
	Frustum	frustum_;
	bool orthographic_;
	float orthoSize_;
	int mClientWidth;
	int mClientHeight;
};

