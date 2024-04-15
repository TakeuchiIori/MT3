#include <Novice.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include "Vector3.h"

const char kWindowTitle[] = "LE2B_14_タケウチ_イオリ";

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 ans;
	ans.x = v1.x + v2.x;
	ans.y = v1.y + v2.y;
	ans.z = v1.z + v2.z;
	return ans;
}
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 ans;
	ans.x = v1.x - v2.x;
	ans.y = v1.y - v2.y;
	ans.z = v1.z - v2.z;
	return ans;
}
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 ans;
	ans.x = scalar * v.x;
	ans.y = scalar * v.y;
	ans.z = scalar * v.z;
	return ans;
}
// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float ans;
	ans = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return ans;
}
// 長さ(ノルム)
float Length(const Vector3& v) {
	float ans;
	ans = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return ans;
}
// 正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 ans;
	ans.x = v.x / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	ans.y = v.y / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	ans.z = v.z / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return ans;
}

static const int kColumnwidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnwidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnwidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnwidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1{1.0f, 3.0f, -5.0f};
	Vector3 v2{4.0f, -1.0f, 2.0f};
	float k = {4.0f};
	int kRowHeight = 30;

	Vector3 resultAdd = Add(v1, v2);
	Vector3 resultSubtract = Subtract(v1, v2);
	Vector3 resultMultiply = Multiply(k, v1);
	float resultDot = Dot(v1, v2);
	float resultLength = Length(v1);
	Vector3 resultNormalize = Normalize(v2);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, resultAdd, "  : Add");
		VectorScreenPrintf(0, kRowHeight, resultSubtract, "  : Subtract");
		VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, "  : Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f  : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f  : Length", resultLength);
		VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, "  : Normalize");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
