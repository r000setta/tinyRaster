#pragma once
#include <memory>
#include <Windows.h>
#include <vector>
#include "camera.h"

class SoftRenderer
{
public:
	enum class RenderMode
	{
		RF_WIREFRAME,
		RF_COLOR,
	};

	SoftRenderer(HWND hwnd, int weight, int height,RenderMode mode=RenderMode::RF_WIREFRAME);
	void Update();
	void ClearBuffer();
	void ShutDown();

	void DrawCube();
	void DrawPlane(int lt, int rt, int rb, int lb);
	void DrawPrimitive(const Vertex& a,const Vertex& b,const Vertex& c);
	void DrawLine(int x1, int y1, int x2, int y2, unsigned int color);

private:
	int mWidth;
	int mHeight;
	HWND mHwnd;
	HDC mTmpDC;
	HBITMAP mTmpBm;
	HBITMAP mOldBm;
	size_t* mFrameBuffer;
	std::unique_ptr<float[]> mDepthBuffer;

	RenderMode mMode;

	Camera mCamera;
	size_t bgColor = ((123 << 16) | (195 << 8) | 221);

	bool Check(const Vector4& v);
};