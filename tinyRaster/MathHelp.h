#pragma once
#include <vector>

struct Vector4
{
	float x, y, z, w;

	void Normalize()
	{
		float len = float(x * x + y * y + z * z);
		x /= len;
		y /= len;
		z /= len;
	}
};

struct Matrix4x4
{
	float m[4][4];
};

struct Vertex
{
	Vector4 point;
	Vector4 color;
};

Vector4 Normalize(const Vector4& v);

Vector4 Cross(const Vector4& u, const Vector4& v);

float Dot(const Vector4& u, const Vector4& v);

Matrix4x4 Mul(const Matrix4x4& a, const Matrix4x4& b);

Vector4 Transform(const Vector4& v, const Matrix4x4& m);

void PerspectiveDivide(Vector4& v);

void TransformScreen(Vector4& v, int width, int height);

std::vector<Vertex> vertexes = {
    // 近相机面
    {{-1.0f, +1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 0.0f}},
    {{+1.0f, +1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 0.0f}},
    {{+1.0f, -1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 0.0f}},

    // 远相机面
    {{-1.0f, +1.0f, +1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 0.0f}},
    {{+1.0f, +1.0f, +1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 0.0f}},
    {{+1.0f, -1.0f, +1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, +1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 0.0f}}
};