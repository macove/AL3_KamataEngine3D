#define NOMINMAX

#include "RailCamera.h"
#include "MathematicsUtil.h"
#include <Xinput.h>
#include <algorithm>

using namespace MyMathematics;

void RailCamera::Initialize() {

	//viewProjection_ = viewProjection;
	
	//worldTransform_.translation_ = Vector3(0.0f, 0.0f, 0.0f);
	//worldTransform_.rotation_ = Vector3(0.0f, 0.0f, 0.0f);

	worldTransform_.Initialize();
	  viewProjection_.Initialize();
	  viewProjection_.farZ = 1000.0f;
	  //preButtons = 0;
}

void RailCamera::Update() {


	// Vector3 cameraLengthPos[4];
	// Vector3 cameraWidthPos[4];

	// Vector3 cameraPos[6];
	//
	// cameraPos[0] = {0.0f, 0.0f, -50.0f};
	// cameraPos[1] = {0.0f, -50.0f, 0.0f};
	// cameraPos[2] = {0.0f, 0.0f, 50.0f};
	// cameraPos[3] = {0.0f, 50.0f, 0.0f};
	// cameraPos[4] = {-50.0f, 0.0f, 0.0f};
	// cameraPos[5] = {50.0f, 0.0f, 0.0f};
	//
	// cameraLengthPos[0] = {0.0f, 0.0f, -50.0f};
	// cameraLengthPos[1] = {0.0f, -50.0f, 0.0f};
	// cameraLengthPos[2] = {0.0f, 0.0f, 50.0f};
	// cameraLengthPos[3] = {0.0f, 50.0f, 0.0f};
	//
	// cameraWidthPos[0] = {0.0f, 0.0f, -50.0f};
	// cameraWidthPos[1] = {-50.0f, 0.0f, 0.0f};
	// cameraWidthPos[2] = {0.0f, 50.0f, 0.0f};
	// cameraWidthPos[3] = {50.0f, 0.0f, 0.0f};
	 

	//XINPUT_STATE state;
	//
	// //rot.x = std::clamp(rot.x, -1.25f, 1.25f);
	// //rot.y = std::clamp(rot.y, -1.25f, 1.25f);
	//
	//if (XInputGetState(0, &state) == ERROR_SUCCESS) {
	//	WORD currentButtons = state.Gamepad.wButtons;
	//
	//	if ((preButtons & XINPUT_GAMEPAD_DPAD_UP) == 0 && (currentButtons & XINPUT_GAMEPAD_DPAD_UP) != 0) {
	//		//countUp++;
	//		if (rot.x > -1.25f) { 
	//			rot.x -= 1.25f;
	//		}
	//	}
	//
	//	if ((preButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0 && (currentButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0) {
	//		//countDown++;
	//		if (rot.x < 1.25f) {
	//			rot.x += 1.25f;
	//		}
	//	}
	//	if ((preButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0 && (currentButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0) {
	//		if (rot.y > -1.25f) { 
	//			rot.y -= 1.25f;
	//		}
	//	}
	//	if ((preButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0 && (currentButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0) {
	//		if (rot.y < 1.25f) { 
	//			rot.y += 1.25f;
	//		}
	//	}
	//	preButtons = static_cast<BYTE>(currentButtons); 
	//	 worldTransform_.rotation_.x = std::clamp(worldTransform_.rotation_.x, -1.25f, 1.25f);
	//	worldTransform_.rotation_.y = std::clamp(worldTransform_.rotation_.y, -1.25f, 1.25f);
	//}

	
	
	

	//ImGui::Begin("camera");
	//ImGui::PushItemWidth(300);
	//ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	//ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	////ImGui::DragInt("countU", &countUp, 1);
	////ImGui::DragInt("countD", &countDown, 1);
	//ImGui::End();
	
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	worldTransform_.TransferMatrix();
	
	viewProjection_.TransferMatrix();

}

const WorldTransform& RailCamera::GetWorldTransform() const { return worldTransform_; }

const ViewProjection& RailCamera::GetViewProjection() const { return viewProjection_; }


