#include "MathHelp.h"

Vector4 Normalize(const Vector4& v)
{
    float len = float(v.x * v.x + v.y * v.y + v.z * v.z);
    return { v.x / len,v.y / len,v.z / len, 0.0 };
}

Vector4 Cross(const Vector4& u, const Vector4& v)
{
	return { u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x, 0.0f };
}

float Dot(const Vector4& u, const Vector4& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Matrix4x4 Mul(const Matrix4x4& a, const Matrix4x4& b)
{
    Matrix4x4 r;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            r.m[i][j] = a.m[i][0] * b.m[0][j]
                + a.m[i][1] * b.m[1][j]
                + a.m[i][2] * b.m[2][j]
                + a.m[i][3] * b.m[3][j];
        }
    }
    return r;
}

Vector4 Transform(const Vector4& v, const Matrix4x4& m)
{
    Vector4 r;
    r.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0];
    r.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1];
    r.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2];
    r.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];
    return r;
}

void PerspectiveDivide(Vector4& v)
{
    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;
    v.w = 1.0f;
}

void TransformScreen(Vector4& v, int width, int height)
{
    v.x = (v.x + 1.0f) * width * 0.5f;
    v.y = (1.0f - v.y) * height * 0.5f;
}
