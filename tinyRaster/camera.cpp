#include "camera.h"

Camera::Camera(Vector4 pos, Vector4 target, Vector4 up)
	:mPos(pos), mTarget(target), mUp(up)
{
}

void Camera::SetPos(const Vector4& pos)
{
	mPos = pos;
	CalcMatrix();
}

void Camera::SetPerspectiveForLH(float fov, float aspect, float nearZ, float farZ)
{
	mFov = fov;
	mAspect = aspect;
	mNearZ = nearZ;
	mFarZ = farZ;
	CalcMatrix();
}

void Camera::CalcMatrix()
{
	Vector4 dir = { mTarget.x - mPos.x,mTarget.y - mPos.y,mTarget.z - mPos.z,0.0f };
	Vector4 w = Normalize(dir);
	Vector4 u = Normalize(Cross(mUp, w));
	Vector4 v = Cross(w, u);

	mWorldToView = {
		u.x, v.x, w.x, 0.0f,
		u.y, v.y, w.y, 0.0f,
		u.z, v.z, w.z, 0.0f,
		-Dot(mPos, u), -Dot(mPos, v), -Dot(mPos, w), 1.0
	};

	float f = 1.0f / (float)tan(mFov * 0.5f);
	mViewToProjection = {
		f / mAspect,0.0f,0.0f,0.0f,
		0.0f,f,0.0f,0.0f,
		0.0f,0.0f,mFarZ / (mFarZ - mNearZ),1.0f,
		0.0f,0.0f,-mNearZ * mFarZ / (mFarZ - mNearZ),0.0f
	};

	mWorldToProjection = Mul(mWorldToView, mViewToProjection);
}


