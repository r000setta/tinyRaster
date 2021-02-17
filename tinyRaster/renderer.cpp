#include "renderer.h"

SoftRenderer::SoftRenderer(HWND hwnd, int width, int height, RenderMode mode = RenderMode::RF_WIREFRAME)
	:mWidth(width), mHeight(height), mHwnd(hwnd), mMode(mode)
{
	HDC hdc = GetDC(hwnd);
	mTmpDC = CreateCompatibleDC(hdc);
	ReleaseDC(hwnd, hdc);
	
	BITMAPINFO bi = { {sizeof(BITMAPINFOHEADER),width,height,1,32,BI_RGB,(DWORD)width * height * 4,0,0,0,0} };
	mTmpBm = CreateDIBSection(mTmpDC, &bi, DIB_RGB_COLORS, (void**)&mFrameBuffer, 0, 0);
	mOldBm = (HBITMAP)SelectObject(mTmpDC, mTmpBm);

	mDepthBuffer.reset(new float[width * height]);

	ClearBuffer();

	mCamera=Camera(
		{ 5.0f, 5.0f, -5.0f, 1.0f },  // 位置
		{ 0.0f, 0.0f, 0.0f, 1.0f },   // 朝向 原点
		{ 0.0f, 1.0f, 0.0f, 0.0f }    // 摄像机上方向
	);

	mCamera.SetPerspectiveForLH(
		3.1415926f * 0.25f,       // 上下45度视野
		(float)mWidth / (float)mHeight,    // 长宽比
		1.0f,
		200.0f
	);
}

void SoftRenderer::Update()
{
	ClearBuffer();
	HDC hdc = GetDC(mHwnd);
	BitBlt(hdc, 0, 0, mWidth, mHeight, mTmpDC, 0, 0, SRCCOPY);
	ReleaseDC(mHwnd, hdc);
}

void SoftRenderer::ClearBuffer()
{
	for (int r = 0; r < mHeight; ++r)
	{
		for (int c = 0; c < mWidth; ++c)
		{
			int idx = r * mWidth + c;
			mFrameBuffer[idx] = bgColor;
			mDepthBuffer[idx] = 1.0f;
		}
	}
}

void SoftRenderer::ShutDown()
{
	if (mTmpDC)
	{
		if (mOldBm)
		{
			SelectObject(mTmpDC, mOldBm);
			mOldBm = nullptr;
		}
		DeleteDC(mTmpDC);
		mTmpDC = nullptr;
	}
	if (mTmpBm)
	{
		DeleteObject(mTmpBm);
		mTmpBm = nullptr;
	}
}

void SoftRenderer::DrawCube()
{
	DrawPlane(0, 1, 2, 3);
}

void SoftRenderer::DrawPlane(int lt, int rt, int rb, int lb)
{
	DrawPrimitive(vertexes[lt], vertexes[rt], vertexes[rb]);
	DrawPrimitive(vertexes[lt], vertexes[rb], vertexes[lb]);
}

void SoftRenderer::DrawPrimitive(const Vertex& a, const Vertex& b, const Vertex& c)
{
	Matrix4x4 m = mCamera.mWorldToProjection;
	Vector4 p1 = Transform(a.point, m);
	if (Check(p1)) return;
	Vector4 p2 = Transform(b.point, m);
	if (Check(p2)) return;
	Vector4 p3 = Transform(c.point, m);
	if (Check(p3)) return;

	PerspectiveDivide(p1);
	PerspectiveDivide(p2);
	PerspectiveDivide(p3);

	TransformScreen(p1, mWidth, mHeight);
	TransformScreen(p2, mWidth, mHeight);
	TransformScreen(p2, mWidth, mHeight);

	if (mMode == RenderMode::RF_WIREFRAME)
	{

	}
}

void SoftRenderer::DrawLine(int x1, int y1, int x2, int y2, unsigned int color)
{
}

bool SoftRenderer::Check(const Vector4& v)
{
	if (v.z < 0.0f) return true;
	if (v.z > v.w) return true;
	if (v.x < -v.w) return true;
	if (v.x > v.w) return true;
	if (v.y < -v.w) return true;
	if (v.y > v.w) return true;
	return false;
}


