#pragma once
#include <Novice.h>
#include <assert.h>
#include <cmath>
#include <imgui.h>
#include <math.h>
#include <iostream>
#include <vector>
#include<cmath>
#include <algorithm>
#include <corecrt_math_defines.h>
#include "Vector3.h"
#include "Vector4.h"

using namespace std;
struct Matrix4x4 {
	float m[4][4];
};
struct Vector2Int {
	int x;
	int y;
};
struct Sphere {
	Vector3 center; // !< 中心点
	float radius;   // !< 半径
};
struct Plane {
	Vector3 normal; // !<法線
	float Length; // !<距離
};
struct Triangle {
	Vector3 vertex[3];
};
struct Segment {
	Vector3 origin;
	Vector3 diff;
};
struct AABB {
	Vector3 min;
	Vector3 max;
};
struct OBB {
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};
    // Vector3 : 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
// Vector3 : 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;
}

// ベクトルの内積を計算する関数
float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
// ベクトルの外積を計算する関数
Vector3 crossProduct(const Vector3& a, const Vector3& b) { return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
// ベクトルの大きさの2乗を計算する関数
float magnitudeSquared(const Vector3& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
// ベクトルの引き算を行う関数
Vector3 subtract(const Vector3& a, const Vector3& b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
// ベクトルの掛け算を行う関数
Vector3 multiply(const Vector3& v, float scalar) { return {v.x * scalar, v.y * scalar, v.z * scalar}; }
// ベクトルの大きさを計算する関数
float magnitude(const Vector3& v) { return std::sqrt(magnitudeSquared(v)); }
// ベクトルの正規化を行う関数
Vector3 normalize(const Vector3& v) {
	float mag = magnitude(v);
	return {v.x / mag, v.y / mag, v.z / mag};
}
// ベクトル間の距離を計算する関数
float Length(const Vector3& a, const Vector3& b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}
//==================================== 1. 行列の加法 ==============================================
Matrix4x4 Add(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 result;
	result.m[0][0] = matrix1.m[0][0] + matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] + matrix2.m[0][1];
	result.m[0][2] = matrix1.m[0][2] + matrix2.m[0][2];
	result.m[0][3] = matrix1.m[0][3] + matrix2.m[0][3];

	result.m[1][0] = matrix1.m[1][0] + matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] + matrix2.m[1][1];
	result.m[1][2] = matrix1.m[1][2] + matrix2.m[1][2];
	result.m[1][3] = matrix1.m[1][3] + matrix2.m[1][3];

	result.m[2][0] = matrix1.m[2][0] + matrix2.m[2][0];
	result.m[2][1] = matrix1.m[2][1] + matrix2.m[2][1];
	result.m[2][2] = matrix1.m[2][2] + matrix2.m[2][2];
	result.m[2][3] = matrix1.m[2][3] + matrix2.m[2][3];

	result.m[3][0] = matrix1.m[3][0] + matrix2.m[3][0];
	result.m[3][1] = matrix1.m[3][1] + matrix2.m[3][1];
	result.m[3][2] = matrix1.m[3][2] + matrix2.m[3][2];
	result.m[3][3] = matrix1.m[3][3] + matrix2.m[3][3];

	return result;
}
//==================================== 2. 行列の減法 ==============================================
Matrix4x4 Subtract(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 result;
	result.m[0][0] = matrix1.m[0][0] - matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] - matrix2.m[0][1];
	result.m[0][2] = matrix1.m[0][2] - matrix2.m[0][2];
	result.m[0][3] = matrix1.m[0][3] - matrix2.m[0][3];

	result.m[1][0] = matrix1.m[1][0] - matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] - matrix2.m[1][1];
	result.m[1][2] = matrix1.m[1][2] - matrix2.m[1][2];
	result.m[1][3] = matrix1.m[1][3] - matrix2.m[1][3];

	result.m[2][0] = matrix1.m[2][0] - matrix2.m[2][0];
	result.m[2][1] = matrix1.m[2][1] - matrix2.m[2][1];
	result.m[2][2] = matrix1.m[2][2] - matrix2.m[2][2];
	result.m[2][3] = matrix1.m[2][3] - matrix2.m[2][3];

	result.m[3][0] = matrix1.m[3][0] - matrix2.m[3][0];
	result.m[3][1] = matrix1.m[3][1] - matrix2.m[3][1];
	result.m[3][2] = matrix1.m[3][2] - matrix2.m[3][2];
	result.m[3][3] = matrix1.m[3][3] - matrix2.m[3][3];
	return result;
}
//===================================== 3. 行列の積 ===============================================//
Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 result;
	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0] + matrix1.m[0][3] * matrix2.m[3][0];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0] + matrix1.m[1][3] * matrix2.m[3][0];
	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0] + matrix1.m[2][3] * matrix2.m[3][0];
	result.m[3][0] = matrix1.m[3][0] * matrix2.m[0][0] + matrix1.m[3][1] * matrix2.m[1][0] + matrix1.m[3][2] * matrix2.m[2][0] + matrix1.m[3][3] * matrix2.m[3][0];

	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1] + matrix1.m[0][3] * matrix2.m[3][1];
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1] + matrix1.m[1][3] * matrix2.m[3][1];
	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1] + matrix1.m[2][3] * matrix2.m[3][1];
	result.m[3][1] = matrix1.m[3][0] * matrix2.m[0][1] + matrix1.m[3][1] * matrix2.m[1][1] + matrix1.m[3][2] * matrix2.m[2][1] + matrix1.m[3][3] * matrix2.m[3][1];

	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2] + matrix1.m[0][3] * matrix2.m[3][2];
	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2] + matrix1.m[1][3] * matrix2.m[3][2];
	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2] + matrix1.m[2][3] * matrix2.m[3][2];
	result.m[3][2] = matrix1.m[3][0] * matrix2.m[0][2] + matrix1.m[3][1] * matrix2.m[1][2] + matrix1.m[3][2] * matrix2.m[2][2] + matrix1.m[3][3] * matrix2.m[3][2];

	result.m[0][3] = matrix1.m[0][0] * matrix2.m[0][3] + matrix1.m[0][1] * matrix2.m[1][3] + matrix1.m[0][2] * matrix2.m[2][3] + matrix1.m[0][3] * matrix2.m[3][3];
	result.m[1][3] = matrix1.m[1][0] * matrix2.m[0][3] + matrix1.m[1][1] * matrix2.m[1][3] + matrix1.m[1][2] * matrix2.m[2][3] + matrix1.m[1][3] * matrix2.m[3][3];
	result.m[2][3] = matrix1.m[2][0] * matrix2.m[0][3] + matrix1.m[2][1] * matrix2.m[1][3] + matrix1.m[2][2] * matrix2.m[2][3] + matrix1.m[2][3] * matrix2.m[3][3];
	result.m[3][3] = matrix1.m[3][0] * matrix2.m[0][3] + matrix1.m[3][1] * matrix2.m[1][3] + matrix1.m[3][2] * matrix2.m[2][3] + matrix1.m[3][3] * matrix2.m[3][3];

	return result;
}
//===================================== 4. 逆行列 ===============================================//
Matrix4x4 Inverse(Matrix4x4 matrix) {
	Matrix4x4 result;
	float detA = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3]) + (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1]) +
	             (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1]) -
	             (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]) -
	             (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]) -
	             (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2]) + (matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1]) +
	             (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3]) + (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2]) +
	             (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) + (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1]) +
	             (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]) -
	             (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]) -
	             (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0]) - (matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0]) -
	             (matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0]) + (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0]) +
	             (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0]) + (matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0]);
	//=---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	result.m[0][0] = 1 / detA *
	                 (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] + matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
	                  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] - matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] - matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]);

	result.m[0][1] = 1 / detA *
	                 (matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1] + matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3] + matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2] -
	                  matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] - matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1] - matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2]);

	result.m[0][2] = 1 / detA *
	                 (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] + matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1] + matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2] -
	                  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3] - matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2]);

	result.m[0][3] = 1 / detA *
	                 (matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] + matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] + matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] -
	                  matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] - matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] - matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2]);
	//=---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	result.m[1][0] = 1 / detA *
	                 (matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] + matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] + matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] -
	                  matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] - matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] - matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2]);

	result.m[1][1] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0] + matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2] -
	                  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0] - matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2]);

	result.m[1][2] = 1 / detA *
	                 (matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3] + matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2] -
	                  matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] - matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0] - matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2]);

	result.m[1][3] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] + matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] + matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] -
	                  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] - matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] - matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2]);
	//=---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	result.m[2][0] = 1 / detA *
	                 (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] + matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] + matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] -
	                  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] - matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] - matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1]);

	result.m[2][1] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1] + matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3] + matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0] -
	                  matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] - matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0] - matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1]);

	result.m[2][2] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] + matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0] + matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1] -
	                  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3] - matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0]);

	result.m[2][3] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] + matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] + matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] -
	                  matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] - matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] - matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1]);
	//=---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	result.m[3][0] = 1 / detA *
	                 (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] + matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] + matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] -
	                  matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] - matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] - matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1]);

	result.m[3][1] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] + matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0] + matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1] -
	                  matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1] - matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2] - matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0]);

	result.m[3][2] = 1 / detA *
	                 (matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0] + matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2] + matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1] -
	                  matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] - matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0] - matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1]);

	result.m[3][3] = 1 / detA *
	                 (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
	                  matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]);
	return result;
}
//===================================== 5. 転置行列 ===============================================//
Matrix4x4 TransPose(Matrix4x4 matrix) {
	Matrix4x4 result;
	result.m[0][0] = matrix.m[0][0];
	result.m[0][1] = matrix.m[1][0];
	result.m[0][2] = matrix.m[2][0];
	result.m[0][3] = matrix.m[3][0];

	result.m[1][0] = matrix.m[0][1];
	result.m[1][1] = matrix.m[1][1];
	result.m[1][2] = matrix.m[2][1];
	result.m[1][3] = matrix.m[3][1];

	result.m[2][0] = matrix.m[0][2];
	result.m[2][1] = matrix.m[1][2];
	result.m[2][2] = matrix.m[2][2];
	result.m[2][3] = matrix.m[3][2];

	result.m[3][0] = matrix.m[0][3];
	result.m[3][1] = matrix.m[1][3];
	result.m[3][2] = matrix.m[2][3];
	result.m[3][3] = matrix.m[3][3];

	return result;
}
//===================================== 6. 単位行列 ===============================================//
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}
//=====================================7.拡大縮小行列===============================================//
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

//=====================================8.平行移動行列===============================================//
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;

	return result;
}

//=====================================9.座標変換===============================================//
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

//=====================================10.回転行列=====================================//
// 1. X軸回転行列
Matrix4x4 MakeRotateMatrixX(float radian) {
	Matrix4x4 result;
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = -std::sinf(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
};
// 2. Y軸回転行列
Matrix4x4 MakeRotateMatrixY(float radian) {
	Matrix4x4 result;
	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = 0;
	result.m[0][2] = -std::sinf(radian);
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = std::sinf(radian);
	result.m[2][1] = 0;
	result.m[2][2] = std::cosf(radian);
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
};
// 3. Z軸回転行列
Matrix4x4 MakeRotateMatrixZ(float radian) {
	Matrix4x4 result;
	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = -std::sinf(radian);
	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
};
// XYZ軸周りの回転行列を生成する関数
Matrix4x4 MakeRotateMatrixXYZ(Vector3& angle) {
	return Multiply(Multiply(MakeRotateMatrixX(angle.x), MakeRotateMatrixY(angle.y)), MakeRotateMatrixZ(angle.z));
}
//=============================11. 3次元のアフィン変換行列=============================//
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result;
	Matrix4x4 rotateMatrixX = MakeRotateMatrixX(rotate.x);
	Matrix4x4 rotateMatrixY = MakeRotateMatrixY(rotate.y);
	Matrix4x4 rotateMatrixZ = MakeRotateMatrixZ(rotate.z);
	Matrix4x4 rotateMatrixXYZ = Multiply(rotateMatrixX, Multiply(rotateMatrixY, rotateMatrixZ));
	result.m[0][0] = scale.x * rotateMatrixXYZ.m[0][0];
	result.m[0][1] = scale.x * rotateMatrixXYZ.m[0][1];
	result.m[0][2] = scale.x * rotateMatrixXYZ.m[0][2];
	result.m[0][3] = 0;

	result.m[1][0] = scale.y * rotateMatrixXYZ.m[1][0];
	result.m[1][1] = scale.y * rotateMatrixXYZ.m[1][1];
	result.m[1][2] = scale.y * rotateMatrixXYZ.m[1][2];
	result.m[1][3] = 0;

	result.m[2][0] = scale.z * rotateMatrixXYZ.m[2][0];
	result.m[2][1] = scale.z * rotateMatrixXYZ.m[2][1];
	result.m[2][2] = scale.z * rotateMatrixXYZ.m[2][2];
	result.m[2][3] = 0;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;

	return result;
}

//=============================12. レンタリングパイプラインVer2=============================//
// 1. 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = 1 / aspectRatio * (1 / std::tanf(FovY / 2));
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = (1 / std::tanf(FovY / 2));
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
};
// 2. 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;

	return result;
};

//--------------------- Gridを表示するコード ---------------------//
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 3.0f;                                      // グリッドの半分の幅
	const uint32_t kSubdivision = 10;                                       // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 1つの長さ

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// ワールド座標系上の始点と終点を求める
		Vector3 WorldStartPos = {-kGridHalfWidth + xIndex * kGridEvery, 0.0f, -kGridHalfWidth};
		Vector3 WorldEndPos = {-kGridHalfWidth + xIndex * kGridEvery, 0.0f, kGridHalfWidth};
		// クリップ座標系に変換
		Vector3 ClipStartPos = Transform(WorldStartPos, viewProjectionMatrix);
		Vector3 ClipEndPos = Transform(WorldEndPos, viewProjectionMatrix);
		// スクリーン座標系に変換
		Vector3 ScreenStartPos = Transform(ClipStartPos, viewportMatrix);
		Vector3 ScreenEndPos = Transform(ClipEndPos, viewportMatrix);
		if (xIndex == kSubdivision / 2 && kSubdivision % 2 == 0) {
			Novice::DrawLine(int(ScreenStartPos.x), int(ScreenStartPos.y), int(ScreenEndPos.x), int(ScreenEndPos.y), 0x000000FF); // 黒色で描画
		} else {
			Novice::DrawLine(int(ScreenStartPos.x), int(ScreenStartPos.y), int(ScreenEndPos.x), int(ScreenEndPos.y), 0xAAAAAAFF); // グレーで描画
		}
	}
	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		// ワールド座標系上の始点と終点を求める
		Vector3 WorldStartPos = {-kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridEvery};
		Vector3 WorldEndPos = {kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridEvery};
		// クリップ座標系に変換
		Vector3 ClipStartPos = Transform(WorldStartPos, viewProjectionMatrix);
		Vector3 ClipEndPos = Transform(WorldEndPos, viewProjectionMatrix);
		// スクリーン座標系に変換
		Vector3 ScreenStartPos = Transform(ClipStartPos, viewportMatrix);
		Vector3 ScreenEndPos = Transform(ClipEndPos, viewportMatrix);
		if (zIndex == kSubdivision / 2 && kSubdivision % 2 == 0) {
			Novice::DrawLine(int(ScreenStartPos.x), int(ScreenStartPos.y), int(ScreenEndPos.x), int(ScreenEndPos.y), 0x000000FF); // 黒色で描画
		} else {
			Novice::DrawLine(int(ScreenStartPos.x), int(ScreenStartPos.y), int(ScreenEndPos.x), int(ScreenEndPos.y), 0xAAAAAAFF); // グレーで描画
		}
	}
}

//--------------------- Sphereを表示する疑似コード ---------------------//
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMarix, uint32_t color) {
	const uint32_t kSubdivision = 10;                          // 分割数
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision;        // 緯度分割1つ分の角度
	// 緯度の方向に分割　-π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; // 現在の緯度
		// 経度の方向に分割 0 ～ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;					// 現在の経度
			// 現在の点を求める
			float x1 = sphere.center.x + sphere.radius * std::cosf(lat) * std::cosf(lon);
			float y1 = sphere.center.y + sphere.radius * std::sinf(lat);
			float z1 = sphere.center.z + sphere.radius * std::cosf(lat) * std::sinf(lon);
			// 次の点を求める（経度方向）
			float x2 = sphere.center.x + sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery);
			float y2 = sphere.center.y + sphere.radius * std::sinf(lat);
			float z2 = sphere.center.z + sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery);
			// 次の点を求める（緯度方向）
			float x3 = sphere.center.x + sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon);
			float y3 = sphere.center.y + sphere.radius * std::sinf(lat + kLatEvery);
			float z3 = sphere.center.z + sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon);
			// 3D座標をVector3にセット
			Vector3 Start(x1, y1, z1);
			Vector3 End1(x2, y2, z2);
			Vector3 End2(x3, y3, z3);
			// 座標変換を行う
			Start = Transform(Start, viewProjectionMatrix);
			Start = Transform(Start, viewportMarix);
			End1 = Transform(End1, viewProjectionMatrix);
			End1 = Transform(End1, viewportMarix);
			End2 = Transform(End2, viewProjectionMatrix);
			End2 = Transform(End2, viewportMarix);
			// 描画
			Novice::DrawLine(int(Start.x), int(Start.y), int(End1.x), int(End1.y), color);
			Novice::DrawLine(int(Start.x), int(Start.y), int(End2.x), int(End2.y), color);
		}
	}
}
//--------------------- 平面の描画 ---------------------//
Vector3 Perpendicual(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return {-vector.y, vector.x, 0.0f};
	}
	return {0.0f, -vector.z, vector.y};
}
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
    Vector3 center = multiply(plane.normal,plane.Length); // 1. 中心点を決める
	Vector3 perpendiculars[4];
	perpendiculars[0] = normalize(Perpendicual(plane.normal)); // 2. 法線と垂直なベクトルを一つ求める
	perpendiculars[1] = {-perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z}; // 3. 2の逆ベクトルを求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]); // 4. 2と法線とのクロス積を求める
	perpendiculars[3] = {-perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z}; // 5. 4の逆ベクトルを求める
	// 6. 2~5のベクトルを中心点にそれぞれ定数倍して足すと4頂点ができる
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = multiply(perpendiculars[index], 2.0f); 
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	// pointsをそれぞれ結んで矩形を描画
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[0].x), int(points[0].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);

}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 points[3];
	for (int32_t i = 0; i < 3; i++) {
		points[i] = Transform(Transform(triangle.vertex[i], viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawTriangle(int(points[0].x), int(points[0].y), int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y),color,kFillModeWireFrame);

}
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 corners[8];
	corners[0] = {aabb.min.x, aabb.min.y, aabb.min.z};
	corners[1] = {aabb.max.x, aabb.min.y, aabb.min.z};
	corners[2] = {aabb.min.x, aabb.max.y, aabb.min.z};
	corners[3] = {aabb.max.x, aabb.max.y, aabb.min.z};
	corners[4] = {aabb.min.x, aabb.min.y, aabb.max.z};
	corners[5] = {aabb.max.x, aabb.min.y, aabb.max.z};
	corners[6] = {aabb.min.x, aabb.max.y, aabb.max.z};
	corners[7] = {aabb.max.x, aabb.max.y, aabb.max.z};

	Vector3 transformedCorners[8];
	for (int i = 0; i < 8; ++i) {
		// Apply the viewProjectionMatrix
		transformedCorners[i] = Transform(corners[i], viewProjectionMatrix);
		// Apply the viewportMatrix
		transformedCorners[i] = Transform(transformedCorners[i], viewportMatrix);
	}

	// Draw the edges of the AABB
	Novice::DrawLine(int(transformedCorners[0].x), int(transformedCorners[0].y), int(transformedCorners[1].x), int(transformedCorners[1].y), color);
	Novice::DrawLine(int(transformedCorners[1].x), int(transformedCorners[1].y), int(transformedCorners[3].x), int(transformedCorners[3].y), color);
	Novice::DrawLine(int(transformedCorners[3].x), int(transformedCorners[3].y), int(transformedCorners[2].x), int(transformedCorners[2].y), color);
	Novice::DrawLine(int(transformedCorners[2].x), int(transformedCorners[2].y), int(transformedCorners[0].x), int(transformedCorners[0].y), color);

	Novice::DrawLine(int(transformedCorners[4].x), int(transformedCorners[4].y), int(transformedCorners[5].x), int(transformedCorners[5].y), color);
	Novice::DrawLine(int(transformedCorners[5].x), int(transformedCorners[5].y), int(transformedCorners[7].x), int(transformedCorners[7].y), color);
	Novice::DrawLine(int(transformedCorners[7].x), int(transformedCorners[7].y), int(transformedCorners[6].x), int(transformedCorners[6].y), color);
	Novice::DrawLine(int(transformedCorners[6].x), int(transformedCorners[6].y), int(transformedCorners[4].x), int(transformedCorners[4].y), color);

	Novice::DrawLine(int(transformedCorners[0].x), int(transformedCorners[0].y), int(transformedCorners[4].x), int(transformedCorners[4].y), color);
	Novice::DrawLine(int(transformedCorners[1].x), int(transformedCorners[1].y), int(transformedCorners[5].x), int(transformedCorners[5].y), color);
	Novice::DrawLine(int(transformedCorners[2].x), int(transformedCorners[2].y), int(transformedCorners[6].x), int(transformedCorners[6].y), color);
	Novice::DrawLine(int(transformedCorners[3].x), int(transformedCorners[3].y), int(transformedCorners[7].x), int(transformedCorners[7].y), color);
}

void AB( AABB& aabb) {
	
	aabb.min.x = (min)(aabb.min.x, aabb.max.x);
	aabb.max.x = (max)(aabb.min.x, aabb.max.x);

	aabb.min.y = (min)(aabb.min.y, aabb.max.y);
	aabb.max.y = (max)(aabb.min.y, aabb.max.y);

	aabb.min.z = (min)(aabb.min.z, aabb.max.z);
	aabb.max.z = (max)(aabb.min.z, aabb.max.z);
}
    // 3. ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -height / 2;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
};

//------------- 3次元ベクトル a をベクトル b に正射影する関数 -------------//
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float dot = Dot(v1, v2);
	float magSquared = magnitudeSquared(v2);
	float scalar = dot / magSquared;
	return {v2.x * scalar, v2.y * scalar, v2.z * scalar};
}
//--------------------- 最近接点を計算する関数 ---------------------//
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 pointOnLine = segment.origin; // 直線上の任意の点はセグメントの始点と同じと仮定
	float dot = Dot(segment.diff, subtract(point, pointOnLine));
	float magSquared = magnitudeSquared(segment.diff);
	float t = dot / magSquared;
	return {pointOnLine.x + segment.diff.x * t, pointOnLine.y + segment.diff.y * t, pointOnLine.z + segment.diff.z * t};
}
//--------------------- 円の当たり判定 ---------------------//
bool IsCollision(const Sphere& s1, const Sphere& s2) {
	// 2つの円の中心間の距離を計算
	float Length = float(std::sqrt(std::pow(s2.center.x - s1.center.x, 2) + std::pow(s2.center.y - s1.center.y, 2) + std::pow(s2.center.z - s1.center.z, 2)));
	// 中心間の距離が2つの円の半径の合計よりも小さい場合、衝突しているとみなす
	if (Length <= (s1.radius + s2.radius)) {
		return true;
	} else {
		return false;
	}
}
//--------------------- 円と平面の当たり判定 ---------------------//
bool IsCollisionPlane(const Sphere& s1, const Plane& plane) {
	Vector3 center = multiply(plane.normal, plane.Length);
	// 2つの円の中心間の距離を計算
	float Length = float(std::sqrt(std::pow(center.x - s1.center.x, 2) + std::pow(center.y - s1.center.y, 2) + std::pow(center.z - s1.center.z, 2)));
	// 中心間の距離が2つの円の半径の合計よりも小さい場合、衝突しているとみなす
	if (Length <= (s1.radius + plane.Length)) {
		return true;
	} else {
		return false;
	}
}
//--------------------- 線と平面の当たり判定 ---------------------//
bool IsCollisionLine(const Segment& line, const Plane& plane) {
	// 平面と線分の始点からの距離を計算
	float dot = Dot(plane.normal, line.diff);
	if (dot == 0.0f) {
		// 平行なので衝突なし
		return false;
	}

	// t を計算
	float t = (plane.Length - Dot(line.origin, plane.normal)) / dot;

	// t の値が [0, 1] の範囲内にあるかどうかで判断
	if (t >= -1.0f && t >= 0.0f && t <= 1.0f ) {
		// 線分のどこかで交差している
		return true;
	} else {
		// 線分が平面を横切っていない
		return false;
	}
	
}
//--------------------- 線と三角形の当たり判定 ---------------------//
bool isCollisionTriangle(const Segment& segment, const Triangle& triangle) {
	// ベクトルの定義
	Vector3 AB = Vector3(triangle.vertex[1].x - triangle.vertex[0].x, triangle.vertex[1].y - triangle.vertex[0].y, triangle.vertex[1].z - triangle.vertex[0].z);
	Vector3 AC = Vector3(triangle.vertex[2].x - triangle.vertex[0].x, triangle.vertex[2].y - triangle.vertex[0].y, triangle.vertex[2].z - triangle.vertex[0].z);
	Vector3 direction = segment.diff;

	// 法線ベクトルと平面方程式
	Vector3 normal = Cross(AB, AC);
	float D = -Dot(normal, triangle.vertex[0]);

	// 線分が平面と交差するtの計算
	float numerator = -(Dot(normal, segment.origin) + D);
	float denominator = Dot(normal, direction);

	if (denominator == 0) {
		return false; // 線分が平面と平行であるため交差しない
	}

	float t = numerator / denominator;
	if (t < 0 || t > 1) {
		return false; // 線分が三角形の平面と交差しない
	}

	// 交点の計算
	Vector3 intersectionPoint = segment.origin + direction * t;

	// バリデーション
	Vector3 C = intersectionPoint - triangle.vertex[0];

	Vector3 crossAB_C = Cross(AB, C);
	float u = Dot(crossAB_C, normal);

	Vector3 crossC_AC = Cross(C, AC);
	float v = Dot(crossC_AC, normal);

	float normSquared = Dot(normal, normal);

	return (u >= 0 && v >= 0 && (u + v) <= normSquared);
}
bool isCollision(const AABB& aabb, const Segment& segment) {
	Vector3 invDir = {1.0f / segment.diff.x, 1.0f / segment.diff.y, 1.0f / segment.diff.z};

	float tmin = (aabb.min.x - segment.origin.x) * invDir.x;
	float tmax = (aabb.max.x - segment.origin.x) * invDir.x;
	if (tmin > tmax) {
		std::swap(tmin, tmax);
	}
	float tymin = (aabb.min.y - segment.origin.y) * invDir.y;
	float tymax = (aabb.max.y - segment.origin.y) * invDir.y;
	if (tymin > tymax)
		std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (aabb.min.z - segment.origin.z) * invDir.z;
	float tzmax = (aabb.max.z - segment.origin.z) * invDir.z;
	if (tzmin > tzmax)
		std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return (tmin < 1.0f) && (tmax > 0.0f);
}
//-------------------- OBB --------------------//
bool IsCollision(const OBB& obb, const Sphere& sphere) {
	// 球の中心をOBBのローカル座標系に変換
	Vector3 d = sphere.center - obb.center;
	float localX = d.dot(obb.orientations[0]);
	float localY = d.dot(obb.orientations[1]);
	float localZ = d.dot(obb.orientations[2]);

	// 球の半径を使ってOBBの範囲内にあるかどうかを判定
	if (std::abs(localX) > (obb.size.x * 0.5f + sphere.radius))
		return false;
	if (std::abs(localY) > (obb.size.y * 0.5f + sphere.radius))
		return false;
	if (std::abs(localZ) > (obb.size.z * 0.5f + sphere.radius))
		return false;

	// 距離の計算
	float distanceSq = 0.0f;
	float excess;

	excess = std::abs(localX) - obb.size.x * 0.5f;
	if (excess > 0.0f)
		distanceSq += excess * excess;

	excess = std::abs(localY) - obb.size.y * 0.5f;
	if (excess > 0.0f)
		distanceSq += excess * excess;

	excess = std::abs(localZ) - obb.size.z * 0.5f;
	if (excess > 0.0f)
		distanceSq += excess * excess;

	return distanceSq <= sphere.radius * sphere.radius;
}

bool IsCollision(const Segment& segment, const OBB& obb) {
	// 線分の始点をOBBのローカル座標系に変換
	Vector3 localOrigin = segment.origin - obb.center;

	// 線分の方向ベクトルをOBBのローカル座標系に変換
	float localDir[3] = {segment.diff.dot(obb.orientations[0]), segment.diff.dot(obb.orientations[1]), segment.diff.dot(obb.orientations[2])};

	float localStart[3] = {localOrigin.dot(obb.orientations[0]), localOrigin.dot(obb.orientations[1]), localOrigin.dot(obb.orientations[2])};

	// OBBの半サイズ
	float halfSize[3] = {obb.size.x * 0.5f, obb.size.y * 0.5f, obb.size.z * 0.5f};

	float tMin = 0.0f;
	float tMax = 1.0f;

	// 各軸に対してスラブ法でチェック
	for (int i = 0; i < 3; ++i) {
		float e = localStart[i];
		float f = localDir[i];
		float halfExtent = halfSize[i];

		if (fabs(f) > 0.00001f) {
			float t1 = (-halfExtent - e) / f;
			float t2 = (halfExtent - e) / f;

			if (t1 > t2)
				std::swap(t1, t2);

			tMin = max(tMin, t1);
			tMax = min(tMax, t2);

			if (tMin > tMax)
				return false;
		} else if (-e - halfExtent > 0.0f || -e + halfExtent < 0.0f) {
			return false;
		}
	}

	return true;
}

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {
	// OBBの8つの頂点を計算
	Vector3 vertices[8];
	Vector3 halfSize = obb.size * 0.5f;

	// 各頂点を計算
	vertices[0] = obb.center - obb.orientations[0] * halfSize.x - obb.orientations[1] * halfSize.y - obb.orientations[2] * halfSize.z;
	vertices[1] = obb.center + obb.orientations[0] * halfSize.x - obb.orientations[1] * halfSize.y - obb.orientations[2] * halfSize.z;
	vertices[2] = obb.center - obb.orientations[0] * halfSize.x + obb.orientations[1] * halfSize.y - obb.orientations[2] * halfSize.z;
	vertices[3] = obb.center + obb.orientations[0] * halfSize.x + obb.orientations[1] * halfSize.y - obb.orientations[2] * halfSize.z;
	vertices[4] = obb.center - obb.orientations[0] * halfSize.x - obb.orientations[1] * halfSize.y + obb.orientations[2] * halfSize.z;
	vertices[5] = obb.center + obb.orientations[0] * halfSize.x - obb.orientations[1] * halfSize.y + obb.orientations[2] * halfSize.z;
	vertices[6] = obb.center - obb.orientations[0] * halfSize.x + obb.orientations[1] * halfSize.y + obb.orientations[2] * halfSize.z;
	vertices[7] = obb.center + obb.orientations[0] * halfSize.x + obb.orientations[1] * halfSize.y + obb.orientations[2] * halfSize.z;

	// 頂点をビュー・プロジェクション行列を使って変換
	Vector3 transformedVertices[8];
	for (int i = 0; i < 8; ++i) {
		transformedVertices[i] = Transform(vertices[i], viewProjectionMatrix);
		transformedVertices[i] = Transform(transformedVertices[i], viewPortMatrix);
	}

	// OBBのエッジを描画
	int points[8][2];
	for (int i = 0; i < 8; ++i) {
		points[i][0] = static_cast<int>(transformedVertices[i].x);
		points[i][1] = static_cast<int>(transformedVertices[i].y);
	}

	// 下部四角形
	Novice::DrawLine(points[0][0], points[0][1], points[1][0], points[1][1], color); // Edge 0-1
	Novice::DrawLine(points[1][0], points[1][1], points[3][0], points[3][1], color); // Edge 1-3
	Novice::DrawLine(points[3][0], points[3][1], points[2][0], points[2][1], color); // Edge 3-2
	Novice::DrawLine(points[2][0], points[2][1], points[0][0], points[0][1], color); // Edge 2-0

	// 上部四角形
	Novice::DrawLine(points[4][0], points[4][1], points[5][0], points[5][1], color); // Edge 4-5
	Novice::DrawLine(points[5][0], points[5][1], points[7][0], points[7][1], color); // Edge 5-7
	Novice::DrawLine(points[7][0], points[7][1], points[6][0], points[6][1], color); // Edge 7-6
	Novice::DrawLine(points[6][0], points[6][1], points[4][0], points[4][1], color); // Edge 6-4

	// 垂直エッジ
	Novice::DrawLine(points[0][0], points[0][1], points[4][0], points[4][1], color); // Edge 0-4
	Novice::DrawLine(points[1][0], points[1][1], points[5][0], points[5][1], color); // Edge 1-5
	Novice::DrawLine(points[2][0], points[2][1], points[6][0], points[6][1], color); // Edge 2-6
	Novice::DrawLine(points[3][0], points[3][1], points[7][0], points[7][1], color);
}
	void CameraMove(Vector3& cameraRotate, Vector3& cameraTranslate, Vector2Int& clickPosition, char* keys, char* preKeys) {
	// カーソルを動かすときの感度
	const float mouseSensitivity = 0.003f;
	// カメラの移動速度
	const float moveSpeed = 0.005f;

	// 各フラグ
	static bool isLeftClicked = false;
	static bool isWheelClicked = false;
	static bool isDebugCamera = false;

	// 回転を考慮する
	Matrix4x4 rotationMatrix = MakeRotateMatrixXYZ(cameraRotate);
	Vector3 X = {1.0f, 0.0f, 0.0f};
	Vector3 Y = {0.0f, 1.0f, 0.0f};
	Vector3 Z = {0.0f, 0.0f, -1.0f};

	Vector3 rotatedX = Transform(X, rotationMatrix);
	Vector3 rotatedY = Transform(Y, rotationMatrix);
	Vector3 rotatedZ = Transform(Z, rotationMatrix);

	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		isDebugCamera = !isDebugCamera;
	}

	if (isDebugCamera) {

		/// ========カメラ操作========
		// カメラの回転を更新する
		if (Novice::IsPressMouse(0) == 1) {
			if (!isLeftClicked) {
				// マウスがクリックされたときに現在のマウス位置を保存する
				Novice::GetMousePosition(&clickPosition.x, &clickPosition.y);
				isLeftClicked = true;
			} else {
				// マウスがクリックされている間はカメラの回転を更新する
				Vector2Int currentMousePos;
				Novice::GetMousePosition(&currentMousePos.x, &currentMousePos.y);

				float deltaX = static_cast<float>(currentMousePos.x - clickPosition.x);
				float deltaY = static_cast<float>(currentMousePos.y - clickPosition.y);

				cameraRotate.x += deltaY * mouseSensitivity;
				cameraRotate.y += deltaX * mouseSensitivity;

				// 現在のマウス位置を保存する
				clickPosition = currentMousePos;
			}
		} else {
			// マウスがクリックされていない場合はフラグをリセットする
			isLeftClicked = false;
		}

		// カメラの位置を更新する
		if (Novice::IsPressMouse(2) == 1) {
			if (!isWheelClicked) {
				// マウスがクリックされたときに現在のマウス位置を保存する
				Novice::GetMousePosition(&clickPosition.x, &clickPosition.y);
				isWheelClicked = true;
			} else {
				// マウスがクリックされている間はカメラの位置を更新する
				Vector2Int currentMousePos;
				Novice::GetMousePosition(&currentMousePos.x, &currentMousePos.y);

				float deltaX = static_cast<float>(currentMousePos.x - clickPosition.x);
				float deltaY = static_cast<float>(currentMousePos.y - clickPosition.y);

				cameraTranslate -= rotatedX * deltaX * mouseSensitivity;
				cameraTranslate += rotatedY * deltaY * mouseSensitivity;

				// 現在のマウス位置を保存する
				clickPosition = currentMousePos;
			}
		} else {
			// マウスがクリックされていない場合はフラグをリセットする
			isWheelClicked = false;
		}

		// マウスホイールの移動量を取得する
		int wheelDelta = -Novice::GetWheel();

		// マウスホイールの移動量に応じてカメラの移動を更新する
		cameraTranslate += rotatedZ * float(wheelDelta) * moveSpeed;
		/// =====================
	}
	ImGui::Begin("camera explanation");
	ImGui::Text("SPACE : DebugCamera on:off\nDebugCamera = %d (0 = false , 1 = true)\nPressingMouseLeftbutton : moveCameraRotate\nPressingMouseWheelbutton : moveCameraTranslate", isDebugCamera);
	ImGui::End();
}
//--------------------- 矩形の当たり判定 ---------------------//
bool IsCollisionRect(const AABB& aabb1, const AABB& aabb2) {
	if((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && 
	   (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
	   (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	else {
		return false;
	}
}

bool isCollision(const AABB& aabb, const Sphere& sphere) {
	Vector3 closestPoint{
	    std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
	    std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
	    std::clamp(sphere.center.z, aabb.min.z, aabb.max.z),
	};
	float distance = Length(closestPoint , sphere.center);
	if (distance <= sphere.radius) {
		return true;
	} else {

		return false;
	}
}
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* name) {
	Novice::ScreenPrintf(x, y, "%s", name);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 25, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}