#include <Novice.h>
#include "MathFunch.h"
const char kWindowTitle[] = "LE2B_14_タケウチ_イオリ";

int kWindowWidth = 1280;
int kWindowHeight = 720;

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

	Plane plane;
	plane.normal = Normalize({-0.2f, 0.9f, -0.3f});
	plane.distance = 0.0f;

	Ball ball{};
	ball.position = {0.0f, 1.2f, 0.3f};
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;
	ball.acceleration = {0.0f, -9.8f, 0.0f};
	float deltaTime = 1.0f / 60.0f;

	bool Update = false;
	float e = 1.0f;


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
		
		if (IsCollision(Sphere{ball.position, ball.radius}, plane)) {
			Vector3 reflected = Reflect(ball.velocity, plane.normal);
			Vector3 projectToNomarl = Project(reflected, plane.normal);
			Vector3 movingDirection = reflected - projectToNomarl;
			ball.velocity = projectToNomarl * e + movingDirection;
		}
		if (Update) {
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;
		}
		





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// ImGui
		
		ImGui::Begin("Window");
		ImGui::DragFloat3("plane", &plane.normal.x, 0.01f);
		plane.normal = Normalize(plane.normal);
		ImGui::DragFloat("planedistance", &plane.distance, 0.01f);
		ImGui::Checkbox("Update", &Update);
		ImGui::End();
		// 線分の両端をスクリーン座標系まで変換
		DrawGrid(ViewProjectionMatrix, ViewportMatrix);
		DrawSphere(ball, ViewProjectionMatrix, ViewportMatrix);

		// 矩形の描画
		DrawPlane(plane, ViewProjectionMatrix, ViewportMatrix, WHITE);


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
