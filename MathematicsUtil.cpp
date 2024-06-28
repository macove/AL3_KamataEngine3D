#include "MathematicsUtil.h"
#include <iostream>

 
Vector3 MyMathematics::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

Vector3 MyMathematics::Subtract(const Vector3& v1, const Vector3& v2) { 
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

float MyMathematics::Length(const Vector3& v1) { 
	float result;

	result = powf(v1.x, 2.0) + powf(v1.y, 2.0) + powf(v1.z, 2.0);

	return sqrtf(result);
}

Vector3 MyMathematics::Multiply(const Vector3& v1, const float& a) { 
	
	Vector3 result;

	result.x = v1.x * a;
	result.y = v1.y * a;
	result.z = v1.z * a;
	
	return result;
}

Vector3 MyMathematics::Normalize(const Vector3& v) { 
	Vector3 result;

	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;
}

Vector3 MyMathematics::TransFormNormal(const Vector3& v, const Matrix4x4& m) { 
	
	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0], 
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1], 
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]

	};
		        return result;
	
	
	 }

Matrix4x4 MyMathematics::MakeRotateXMatrix(float radian) {
	Matrix4x4 result;

	result = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cosf(radian), sinf(radian), 0.0f, 0.0f, -sinf(radian), cosf(radian), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return result;
}

Matrix4x4 MyMathematics::MakeRotateYMatrix(float radian) {
	Matrix4x4 result;

	result = {cosf(radian), 0.0f, -sinf(radian), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sinf(radian), 0.0f, cosf(radian), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return result;
}

Matrix4x4 MyMathematics::MakeRotateZMatrix(float radian) {
	Matrix4x4 result;

	result = {cosf(radian), sinf(radian), 0.0f, 0.0f, -sinf(radian), cosf(radian), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return result;
}

Matrix4x4 MyMathematics::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 MyMathematics::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 result;
	result = {
	    scale.x * rotateXYZMatrix.m[0][0],
	    scale.x * rotateXYZMatrix.m[0][1],
	    scale.x * rotateXYZMatrix.m[0][2],
	    0.0f,
	    scale.y * rotateXYZMatrix.m[1][0],
	    scale.y * rotateXYZMatrix.m[1][1],
	    scale.y * rotateXYZMatrix.m[1][2],
	    0.0f,
	    scale.z * rotateXYZMatrix.m[2][0],
	    scale.z * rotateXYZMatrix.m[2][1],
	    scale.z * rotateXYZMatrix.m[2][2],
	    0.0f,
	    translate.x,
	    translate.y,
	    translate.z,
	    1.0f};
	return result;
}

; // namespace MyMathematics