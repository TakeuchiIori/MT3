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

	Vector3 rotate{0.0f, 0.0f, 0.0f};
	OBB obb{
		.center {-1.0f,0.0f,0.0f},
		    .orientations = {
			    {1.0f, 0.0f, 0.0f},
			    {0.0f, 1.0f, 1.0f},
				{0.0f,0.0f,1.0f}},
			.size{1.5f,1.5f,1.5f}
	};
	Sphere sphere{
	    .center{0.0f, 0.0f, 0.0f},
        .radius{0.5f}
    };

	uint32_t color = WHITE;
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
		Matrix4x4 rotateMatrix = MakeRotateMatrixXYZ(rotate);
		obb.orientations[0].x = rotateMatrix.m[0][0];
		obb.orientations[0].y = rotateMatrix.m[0][1];
		obb.orientations[0].z = rotateMatrix.m[0][2];

		obb.orientations[1].x = rotateMatrix.m[1][0];
		obb.orientations[1].y = rotateMatrix.m[1][1];
		obb.orientations[1].z = rotateMatrix.m[1][2];

		obb.orientations[2].x = rotateMatrix.m[2][0];
		obb.orientations[2].y = rotateMatrix.m[2][1];
		obb.orientations[2].z = rotateMatrix.m[2][2];
		Matrix4x4 CameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, Add(cameraPosition, cameraTranslate));
		Matrix4x4 ViewMatrix = Inverse(CameraMatrix);
		Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 ViewProjectionMatrix = Multiply(ViewMatrix, ProjectionMatrix);
		Matrix4x4 ViewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		CameraMove(cameraRotate, cameraTranslate, clickPosition, keys, preKeys);
		if (IsCollision(obb, sphere)) {
			color = RED;
		} else {
			color = WHITE;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// ImGui
		ImGui::Begin("Window");
		ImGui::DragFloat3("obb.x", &obb.center.x, 0.01f);
		ImGui::DragFloat("rotateX", &rotate.x, 0.01f);
		ImGui::DragFloat("rotateY", &rotate.y, 0.01f);
		ImGui::DragFloat("rotateZ", &rotate.z, 0.01f);

		ImGui::DragFloat3("obb.orientations1", &obb.orientations[0].x, 0.01f);
		ImGui::DragFloat3("obb.orientations2", &obb.orientations[1].x, 0.01f);
		ImGui::DragFloat3("obb.orientations3", &obb.orientations[2].x, 0.01f);

		ImGui::DragFloat3("obb.size", &obb.size.x, 0.01f);

		ImGui::DragFloat3("sphere.center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("sphere.radius", &sphere.radius, 0.01f);

		ImGui::End();
		//--------------------- コメントアウト -----------------------//
		// ImGui::DragFloat3("sphere",&sphere.center.x, 0.01f);
		// ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		// ImGui::DragFloat3("plane", &plane.normal.x,0.01f);
		// plane.normal = normalize(plane.normal);
		// ImGui::DragFloat("planedistance", &plane.distance, 0.01f);
		//----------------------------------------------------------//
		// 線分の両端をスクリーン座標系まで変換
		DrawGrid(ViewProjectionMatrix, ViewportMatrix);
		// 線の描画
		//Vector3 start = Transform(Transform(segment.origin, ViewProjectionMatrix), ViewportMatrix);
		//Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), ViewProjectionMatrix), ViewportMatrix);
		//Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, lineColor);
		// 矩形の描画
		//DrawAABB(aabb1, ViewProjectionMatrix, ViewportMatrix, rectColor);
		DrawOBB(obb, ViewProjectionMatrix, ViewportMatrix, color);
		
		// 平面の描画
		//DrawPlane(plane, ViewProjectionMatrix, ViewportMatrix,WHITE);
		// 円の描画
		 DrawSphere(sphere, ViewProjectionMatrix, ViewportMatrix, WHITE);
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
