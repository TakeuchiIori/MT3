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


	Vector3 translates[3] = {
	    {0.2f, 1.0f, 0.0f},
	    {0.4f, 0.0f, 0.0f},
	    {0.3f, 0.0f, 0.0f},
	};

	Vector3 rotates[3] = {
	    {0.0f, 0.0f, -6.8f},
	    {0.0f, 0.0f, -1.4f},
	    {0.0f, 0.0f, 0.0f },
	};

	Vector3 scales[3] = {
	    {1.0f, 1.0f, 1.0f},
	    {1.0f, 1.0f, 1.0f},
	    {1.0f, 1.0f, 1.0f},
	};



	//uint32_t color = BLACK;
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

		
		Matrix4x4 shoulderScaleMatrix = MakeScaleMatrix(scales[0]);
		Matrix4x4 shoulderRotateMatrix = MakeRotateMatrixXYZ(rotates[0]);
		Matrix4x4 shoulderTranslateMatrix = MakeTranslateMatrix(translates[0]);
		Matrix4x4 shoulderWorldMatrix = Multiply(shoulderScaleMatrix, Multiply(shoulderRotateMatrix, shoulderTranslateMatrix));

		// ひじのワールド変換行列を計算
		Matrix4x4 elbowScaleMatrix = MakeScaleMatrix(scales[1]);
		Matrix4x4 elbowRotateMatrix = MakeRotateMatrixXYZ(rotates[1]);
		Matrix4x4 elbowTranslateMatrix = MakeTranslateMatrix(translates[1]);
		Matrix4x4 elbowLocalMatrix = Multiply(elbowScaleMatrix, Multiply(elbowRotateMatrix, elbowTranslateMatrix));
		Matrix4x4 elbowWorldMatrix = Multiply(elbowLocalMatrix, shoulderWorldMatrix);

		// 手のワールド変換行列を計算
		Matrix4x4 handScaleMatrix = MakeScaleMatrix(scales[2]);
		Matrix4x4 handRotateMatrix = MakeRotateMatrixXYZ(rotates[2]);
		Matrix4x4 handTranslateMatrix = MakeTranslateMatrix(translates[2]);
		Matrix4x4 handLocalMatrix = Multiply(handScaleMatrix, Multiply(handRotateMatrix, handTranslateMatrix));
		Matrix4x4 handWorldMatrix = Multiply(handLocalMatrix, elbowWorldMatrix);

		// 肩、ひじ、手の球を定義
		Sphere shoulderSphere{
		    {shoulderWorldMatrix.m[3][0], shoulderWorldMatrix.m[3][1], shoulderWorldMatrix.m[3][2]},
            0.1f
        };
		Sphere elbowSphere{
		    {elbowWorldMatrix.m[3][0], elbowWorldMatrix.m[3][1], elbowWorldMatrix.m[3][2]},
            0.1f
        };
		Sphere handSphere{
		    {handWorldMatrix.m[3][0], handWorldMatrix.m[3][1], handWorldMatrix.m[3][2]},
            0.1f
        };

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// ImGui
		ImGui::Begin("Window");
		// 個別にSliderを配置
		ImGui::SliderFloat3("Translate 0", &translates[0].x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Rotate 0", &rotates[0].x, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale 0", &scales[0].x, 0.1f, 10.0f);

		ImGui::SliderFloat3("Translate 1", &translates[1].x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Rotate 1", &rotates[1].x, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale 1", &scales[1].x, 0.1f, 10.0f);

		ImGui::SliderFloat3("Translate 2", &translates[2].x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Rotate 2", &rotates[2].x, -10.0f, 10.0f);
		ImGui::SliderFloat3("Scale 2", &scales[2].x, 0.1f, 10.0f);

		ImGui::End();
		// 線分の両端をスクリーン座標系まで変換
		DrawGrid(ViewProjectionMatrix, ViewportMatrix);

		DrawSphere(shoulderSphere, ViewProjectionMatrix, ViewportMatrix, RED);
		DrawSphere(elbowSphere, ViewProjectionMatrix, ViewportMatrix, BLUE);
		DrawSphere(handSphere, ViewProjectionMatrix, ViewportMatrix, GREEN);
		Vector3 sphereCenters[3] = {
		    {shoulderSphere.center.x, shoulderSphere.center.y, shoulderSphere.center.z},
		    {elbowSphere.center.x,    elbowSphere.center.y,    elbowSphere.center.z   },
		    {handSphere.center.x,     handSphere.center.y,     handSphere.center.z    },
		};

		for (int i = 0; i < 2; ++i) {
			Vector3 start = Transform(sphereCenters[i], ViewProjectionMatrix);
			start = Transform(start, ViewportMatrix);
			Vector3 end = Transform(sphereCenters[i + 1], ViewProjectionMatrix);
			end = Transform(end, ViewportMatrix);
			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), BLACK);
		}

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
