#include "FollowCamera.h"
#include<Input.h>

using namespace MyMathematics;
void FollowCamera::Initialize(ViewProjection* viewProjection) {



	viewProjection_ = viewProjection;


}

void FollowCamera::Update() {

	if (target_) {
	
	
	Vector3 offset = {0.0f, 2.0f, -30.0f};

		Matrix4x4 rotationMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);

		offset = TransFormNormal(offset, rotationMatrix);

	viewProjection_->translation_ = Add(target_->translation_,offset);
	}



	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	const float kCharacterSpeed = 0.0001f;
		viewProjection_->rotation_.y += ((float)joyState.Gamepad.sThumbRX * kCharacterSpeed)/300;
		
	}




	viewProjection_->UpdateMatrix();


}
