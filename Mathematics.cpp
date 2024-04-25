#include "Mathematics.h"

Matrix4x4 Mathematics::MakeRotateXMatrix(float radian) {

	Matrix4x4 result;

	result = {1.0f, 0.0f, 0.0f, 0.0f, 
		      0.0f, cosf(radian), sinf(radian), 0.0f, 
		      0.0f, -sinf(radian), cosf(radian), 0.0f,
		      0.0f, 0.0f, 0.0f, 1.0f};
	return result;

}

Matrix4x4 Mathematics::MakeRotateYMatrix(float radian) {

	Matrix4x4 result;

	result = {cosf(radian), 0.0f, -sinf(radian), 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f, 
		sinf(radian), 0.0f, cosf(radian), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};
	return result;

}

Matrix4x4 Mathematics::MakeRotateZMatrix(float radian) { 
	
	
	Matrix4x4 result;

	result = {cosf(radian), sinf(radian), 0.0f, 0.0f, 
		-sinf(radian), cosf(radian), 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f};
	return result;

}

Matrix4x4 Mathematics::Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

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








Matrix4x4 Mathematics::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 result;
	result = {
	    scale.x * rotateXYZMatrix.m[0][0],scale.x * rotateXYZMatrix.m[0][1], scale.x * rotateXYZMatrix.m[0][2], 0.0f,
	    scale.y * rotateXYZMatrix.m[1][0],scale.y * rotateXYZMatrix.m[1][1],scale.y * rotateXYZMatrix.m[1][2],0.0f,
	    scale.z * rotateXYZMatrix.m[2][0],scale.z * rotateXYZMatrix.m[2][1],scale.z * rotateXYZMatrix.m[2][2],0.0f,
	    translate.x,translate.y,translate.z,1.0f};
	return result;



}
