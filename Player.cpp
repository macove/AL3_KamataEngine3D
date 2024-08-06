#include "Player.h"
#include <cassert>
#include "TextureManager.h"
#include <Input.h>
#include <ImGui.h>

using namespace MyMathematics;
Player::Player() {
}

Player::~Player() {



}

void Player::Initialize(Model* model, ViewProjection* viewProjection) { 
	

	assert(model); 

	this->model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	
}

void Player::Update() { 
	
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.4f;
	const float kPlayerRotationSpeed = 0.05f; 
	const float kMaxPlayerRotation = 0.3f;    
	const float kPlayerReturnSpeed = 0.02f; 

	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// Move the player based on joystick input
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	if (move.x != 0.0f || move.z != 0.0f) {
		move = Multiply(Normalize(move), kCharacterSpeed);
		if (viewProjection_) {
			worldTransform_.rotation_.y += move.x * kPlayerRotationSpeed;
			
			if (worldTransform_.rotation_.y > kMaxPlayerRotation) {
				worldTransform_.rotation_.y = kMaxPlayerRotation;
			} else if (worldTransform_.rotation_.y < -kMaxPlayerRotation) {
				worldTransform_.rotation_.y = -kMaxPlayerRotation;
			}
		}
	} else {
		
		if (worldTransform_.rotation_.y > 0) {
			worldTransform_.rotation_.y -= kPlayerReturnSpeed;
			if (worldTransform_.rotation_.y < 0) {
				worldTransform_.rotation_.y = 0;
			}
		} else if (worldTransform_.rotation_.y < 0) {
			worldTransform_.rotation_.y += kPlayerReturnSpeed;
			if (worldTransform_.rotation_.y > 0) {
				worldTransform_.rotation_.y = 0;
			}
		}
	}


	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.UpdateMatrix();

	ImGui::Begin("moveca");
	ImGui::Text("move %f", move.x);
	ImGui::End();
	
}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);
	

}

const WorldTransform& Player::GetWorldTransform() const { return worldTransform_; }



