#pragma once
#include "MathHelp.h"

class Camera
{
public:
	Camera() {};
	Camera(Vector4 pos, Vector4 target, Vector4 up);
	virtual ~Camera() noexcept {}
	void SetPos(const Vector4& pos);
	void SetPerspectiveForLH(float fov, float aspect, float nearZ, float farZ);

	Matrix4x4 mWorldToProjection;

private:
	void CalcMatrix();

	Vector4 mPos;
	Vector4 mPosTmp;
	Vector4 mTarget;
	Vector4 mUp;
	float mFov;
	float mAspect;
	float mNearZ;
	float mFarZ;

	Matrix4x4 mWorldToView;
	Matrix4x4 mViewToProjection;
};