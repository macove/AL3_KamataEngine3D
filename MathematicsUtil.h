#pragma once
#include <cmath>
#include "Vector3.h"
#include <Matrix4x4.h>

namespace MyMathematics {

    Vector3 Add(const Vector3& v1, const Vector3& v2);
    Vector3 Subtract(const Vector3& v1, const Vector3& v2);
    float Length(const Vector3& v1);
    Vector3 Multiply(const Vector3& v1, const float& a);
    Vector3 Normalize(const Vector3& v);
    Vector3 TransFormNormal(const Vector3& v, const Matrix4x4& m);
    Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
    Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
    Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	Matrix4x4 MakeRotateXMatrix(float radian);
	Matrix4x4 MakeRotateYMatrix(float radian);
	Matrix4x4 MakeRotateZMatrix(float radian);
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
    Matrix4x4 Inverse(const Matrix4x4& m);
    Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
    }

