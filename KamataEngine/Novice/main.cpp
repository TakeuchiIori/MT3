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


	Vector3 rotate1{0.0f, 0.0f, 0.0f};
	Vector3 rotate2{-0.05f, -2.49f, 0.15f};
	OBB obb1{
		.center {0.0f,0.0f,0.0f},
		    .orientations = {
			    {1.0f, 0.0f, 0.0f},
			    {0.0f, 1.0f, 1.0f},
				{0.0f,0.0f,1.0f}},
			.size{0.53f,0.26f,0.24f}
	};
		OBB obb2{
		.center {0.9f,0.66f,0.78f},
		    .orientations = {
			    {1.0f, 0.0f, 0.0f},
			    {0.0f, 1.0f, 1.0f},
				{0.0f,0.0f,1.0f}},
			.size{0.5f,0.37f,0.5f}
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
		Matrix4x4 rotateMatrix1 = MakeRotateMatrixXYZ(rotate1);
		Matrix4x4 rotateMatrix2 = MakeRotateMatrixXYZ(rotate2);
		obb1.orientations[0].x = rotateMatrix1.m[0][0];
		obb1.orientations[0].y = rotateMatrix1.m[0][1];
		obb1.orientations[0].z = rotateMatrix1.m[0][2];
		   									 
		obb1.orientations[1].x = rotateMatrix1.m[1][0];
		obb1.orientations[1].y = rotateMatrix1.m[1][1];
		obb1.orientations[1].z = rotateMatrix1.m[1][2];
		   									 
		obb1.orientations[2].x = rotateMatrix1.m[2][0];
		obb1.orientations[2].y = rotateMatrix1.m[2][1];
		obb1.orientations[2].z = rotateMatrix1.m[2][2];

		obb2.orientations[0].x = rotateMatrix2.m[0][0];
		obb2.orientations[0].y = rotateMatrix2.m[0][1];
		obb2.orientations[0].z = rotateMatrix2.m[0][2];
									 
		obb2.orientations[1].x = rotateMatrix2.m[1][0];
		obb2.orientations[1].y = rotateMatrix2.m[1][1];
		obb2.orientations[1].z = rotateMatrix2.m[1][2];
								 
		obb2.orientations[2].x = rotateMatrix2.m[2][0];
		obb2.orientations[2].y = rotateMatrix2.m[2][1];
		obb2.orientations[2].z = rotateMatrix2.m[2][2];

		Matrix4x4 CameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, Add(cameraPosition, cameraTranslate));
		Matrix4x4 ViewMatrix = Inverse(CameraMatrix);
		Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 ViewProjectionMatrix = Multiply(ViewMatrix, ProjectionMatrix);
		Matrix4x4 ViewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		CameraMove(cameraRotate, cameraTranslate, clickPosition, keys, preKeys);
		if (IsCollision(obb1,obb2)) {
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
		ImGui::Text("OBB1 Settings");
		ImGui::DragFloat3("obb1.x", &obb1.center.x, 0.01f);
		ImGui::DragFloat("rotateX1", &rotate1.x, 0.01f);
		ImGui::DragFloat("rotateY1", &rotate1.y, 0.01f);
		ImGui::DragFloat("rotateZ1", &rotate1.z, 0.01f);
		ImGui::Text("Orientations");

		ImGui::DragFloat3("obb1.orientations1", &obb1.orientations[0].x, 0.01f);
		ImGui::DragFloat3("obb1.orientations2", &obb1.orientations[1].x, 0.01f);
		ImGui::DragFloat3("obb1.orientations3", &obb1.orientations[2].x, 0.01f);

		ImGui::DragFloat3("obb1.size", &obb1.size.x, 0.01f);
		ImGui::Text("OBB2 Settings");

		ImGui::DragFloat3("obb2.x", &obb2.center.x, 0.01f);
		ImGui::DragFloat("rotateX2", &rotate2.x, 0.01f);
		ImGui::DragFloat("rotateY2", &rotate2.y, 0.01f);
		ImGui::DragFloat("rotateZ2", &rotate2.z, 0.01f);
		ImGui::Text("Orientations");
		ImGui::DragFloat3("obb2.orientations1", &obb2.orientations[0].x, 0.01f);
		ImGui::DragFloat3("obb2.orientations2", &obb2.orientations[1].x, 0.01f);
		ImGui::DragFloat3("obb2.orientations3", &obb2.orientations[2].x, 0.01f);

		ImGui::DragFloat3("obb2.size", &obb2.size.x, 0.01f);
	

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
	/*	Vector3 start = Transform(Transform(segment.origin, ViewProjectionMatrix), ViewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), ViewProjectionMatrix), ViewportMatrix);
		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, BLACK);*/
		// 矩形の描画
		//DrawAABB(aabb1, ViewProjectionMatrix, ViewportMatrix, rectColor);
		DrawOBB(obb1, ViewProjectionMatrix, ViewportMatrix, color);
		DrawOBB(obb2, ViewProjectionMatrix, ViewportMatrix, WHITE);
		
		// 平面の描画
		//DrawPlane(plane, ViewProjectionMatrix, ViewportMatrix,WHITE);
		// 円の描画
		// DrawSphere(sphere, ViewProjectionMatrix, ViewportMatrix, WHITE);
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
