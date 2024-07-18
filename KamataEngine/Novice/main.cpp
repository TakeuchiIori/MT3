#include <Novice.h>
#include "MathFunch.h"
const char kWindowTitle[] = "LE2B_14_タケウチ_イオリ";

int kWindowWidth = 1280;
int kWindowHeight = 720;
Vector3 Project(const Vector3& vec, const Matrix4x4& mat) {
	Vector3 result;
	float w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3];
	result.x = (vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0]) / w;
	result.y = (vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1]) / w;
	result.z = (vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2]) / w;
	return result;
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Vector3 cameraTranslate{0.0f, 1.9f, -6.49f};
	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};
	Vector3 cameraPosition{0.0f, 1.0f, -4.0f};
	Vector2Int clickPosition;

    /*====================================================*/

	Pendulum pendulum;
	
	pendulum.anchor = {0.0f, 1.0f, 0.0f};
	pendulum.length = 0.8f;
	pendulum.angle = 0.7f;
	pendulum.angularVelocity = 0.0f;
	pendulum.angularAcceleration = 0.0f;

	Ball ball{};
	ball.position = {1.2f, 0.0f, 0.0f};
	ball.mass = 2.0f;
	ball.radius = 0.08f;
	ball.color = BLUE;

	float deltaTime = 1.0f / 60.0f;

	bool Update = false;



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

		Matrix4x4 CameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, Add(cameraPosition, cameraTranslate));
		Matrix4x4 ViewMatrix = Inverse(CameraMatrix);
		Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 ViewProjectionMatrix = Multiply(ViewMatrix, ProjectionMatrix);
		Matrix4x4 ViewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		CameraMove(cameraRotate, cameraTranslate, clickPosition, keys, preKeys);

		/*=============================================================================*/
		// 更新処理
		if (Update) {
			pendulum.angularAcceleration = -(9.8f / pendulum.length) * std::sin(pendulum.angle);
			pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
			pendulum.angle += pendulum.angularVelocity * deltaTime;

			ball.position.x = pendulum.anchor.x + sin(pendulum.angle) * pendulum.length;
			ball.position.y = pendulum.anchor.y - cos(pendulum.angle) * pendulum.length;
			ball.position.z = pendulum.anchor.z; // z座標も更新
		}







		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// ImGui
		
		ImGui::Begin("Window");
		ImGui::Checkbox("Update", &Update);
		ImGui::End();
		// 線分の両端をスクリーン座標系まで変換
		DrawGrid(ViewProjectionMatrix, ViewportMatrix);

		DrawSphere(ball, ViewProjectionMatrix, ViewportMatrix);
		
	// 3D座標を2Dスクリーン座標に変換する関数


		// 描画処理
	
		Matrix4x4 VPMatrix = Multiply(ViewProjectionMatrix, ViewportMatrix);

		Vector3 screenAnchor = Project(pendulum.anchor, VPMatrix);
		Vector3 screenBallPos = Project(ball.position, VPMatrix);

		Novice::DrawLine((int)screenAnchor.x, (int)screenAnchor.y, (int)screenBallPos.x, (int)screenBallPos.y, WHITE);


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
