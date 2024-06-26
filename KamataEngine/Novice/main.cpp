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
	//Sphere sphere;
	//sphere.center = {0.0f, 0.0f, 0.0f};
	//sphere.radius = 1.0f;

	//Plane plane{
	//	1.0f,0.0f,1.0f,
	//	0.0f
	//};
	Segment segment{
	    {-2.0f, -1.0f, 0.0f},
        {3.0f,  2.0f,  2.0f}
    };
	Triangle triangle{
	    {{-1.0f, 0.0f, 0.0f}, // 頂点1の座標
	     {0.0f, 1.0f, 0.0f},  // 頂点2の座標
	     {1.0f, 0.0f, 0.0f}}   // 頂点3の座標
 
	};
	Vector2Int clickPosition;
	uint32_t lineColor = WHITE;
	uint32_t TraiangleColor = WHITE;
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
		if (isCollisionTriangle(segment, triangle) == true) {
			TraiangleColor = RED;
		} else {
			TraiangleColor = WHITE;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// ImGui
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("segment origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segment diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("Triangle : v0", &triangle.vertex->x, 0.01f);
		ImGui::DragFloat3("Triangle : v0", &triangle.vertex->x, 0.01f);

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
		Vector3 start = Transform(Transform(segment.origin, ViewProjectionMatrix), ViewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), ViewProjectionMatrix), ViewportMatrix);
		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, lineColor);
		// 三角形の描画
		DrawTriangle(triangle, ViewProjectionMatrix, ViewportMatrix, TraiangleColor);
		
		
		
		// 平面の描画
		//DrawPlane(plane, ViewProjectionMatrix, ViewportMatrix,WHITE);
		// 円の描画
		// DrawSphere(sphere, ViewProjectionMatrix, ViewportMatrix, SphreColor);
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
