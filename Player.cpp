#include "Player.h"
#include <cassert>
#include "TextureManager.h"
#include <Input.h>
#include <ImGui.h>
#define _USE_MATH_DEFINES
#include <math.h>

float Player::attackTime = 0.0f;

using namespace MyMathematics;
Player::Player() {
}

Player::~Player() {



}

void Player::Initialize(const std::vector<Model*>& models) { 
	

	//assert(modelBody); 
	//assert(modelHead);
	//assert(modelL_arm);
	//assert(modelR_arm);
	//
	//
	//this->modelBody_ = modelBody;
	//this->modelHead_ = modelHead;
	//this->modelL_arm_ = modelL_arm;
	//this->modelR_arm_ = modelR_arm;
	//
	//viewProjection_ = viewProjection;
	//
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformBase_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	worldTransformHammer_.Initialize();
	//
	//
	worldTransformBase_.parent_ = &worldTransformBody_;
	worldTransformHead_.parent_ = &worldTransformBody_;  // Head inherits the body transform
	worldTransformL_arm_.parent_ = &worldTransformBody_; // Left arm inherits the body transform
	worldTransformR_arm_.parent_ = &worldTransformBody_; 
	worldTransformHammer_.parent_ = &worldTransformBody_; 
	


	 BaseCharacter::Initialize(models);
	InitializeFloatingGimmick();
}

void Player::Update() { 
	
		XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}
	
	  if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		BehaviorAttackUpdate(); 
	} else {
		
		if (isAttacking) {
			ResetWeaponPosition();
			isAttacking = false;   
		}
		attackExecuted = false;
		BehaviorRootUpdate(); 
	}
		
	

	 UpdateFloatingGimmick();

	
	 worldTransformHead_.UpdateMatrix();
	 worldTransformL_arm_.UpdateMatrix();
	 worldTransformR_arm_.UpdateMatrix();
	worldTransformBase_.UpdateMatrix();

	worldTransform_.UpdateMatrix();

	ImGui::Begin("moveca");
	ImGui::Text("Floating Parameter: %f", floatingParameter_);
	//ImGui::Text("move %f", move.x);
	ImGui::Text("Base Position: %f, %f, %f", worldTransformBase_.translation_.x, worldTransformBase_.translation_.y, worldTransformBase_.translation_.z);
	ImGui::Text("Body Position: %f, %f, %f", worldTransformBody_.translation_.x, worldTransformBody_.translation_.y, worldTransformBody_.translation_.z);
	ImGui::Text("ArmL Position: %f, %f, %f", worldTransformL_arm_.translation_.x, worldTransformL_arm_.translation_.y, worldTransformL_arm_.translation_.z);
	ImGui::Text("ArmR Position: %f, %f, %f", worldTransformR_arm_.translation_.x, worldTransformR_arm_.translation_.y, worldTransformR_arm_.translation_.z);
	ImGui::Text("isAtt %d", isAttacking);
	ImGui::Text("attackTime %f", attackTime);
	ImGui::Text("worldTransformHammer_.rotation_.x %f", worldTransformHammer_.rotation_.x);
	ImGui::End();
	
}

void Player::Draw(const ViewProjection& viewProjection) {



	models_[kModelIndexBody]->Draw(worldTransformBody_, viewProjection);
	models_[kModelIndexHead]->Draw(worldTransformHead_, viewProjection);
	models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
	models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);
	if (isAttacking) {
	models_[kModelIndexHammer]->Draw(worldTransformHammer_, viewProjection);
	}

}

const WorldTransform& Player::GetWorldTransform() const { return worldTransform_; }

void Player::InitializeFloatingGimmick() {


	 floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() {

  const uint16_t kCycleFrame = 60; // Animation cycle in frames
  const float kStep = 2.0f * float(M_PI) / kCycleFrame; // Increment per frame

  // Increment parameter by step for smooth floating
  floatingParameter_ += kStep;

  floatingParameter_ = std::fmod(floatingParameter_, 2.0f * float(M_PI));

   const float kAmplitude = 0.2f;
  const float kLowerArmAmplitude = 0.03f;

  worldTransformBody_.translation_.y = std::sin(floatingParameter_) * kAmplitude;
 

   worldTransformL_arm_.translation_.z = std::cos(floatingParameter_) * kAmplitude;
  worldTransformR_arm_.translation_.z = std::cos(floatingParameter_ + float(M_PI)) * kAmplitude; 

   worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * kLowerArmAmplitude; // Lower arm movement for left arm
  worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_ + float(M_PI)) * kLowerArmAmplitude; // Lower arm movement for right arm
   
}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::BehaviorRootUpdate() {

	  Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.4f;
	const float kPlayerRotationSpeed = 0.05f;
	const float kMaxPlayerRotation = 0.3f;
	const float kPlayerReturnSpeed = 0.02f;

	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}

	if (move.x != 0.0f || move.z != 0.0f) {
		move = Multiply(Normalize(move), kCharacterSpeed);
		if (viewProjection_) {
			worldTransformBody_.rotation_.y += move.x * kPlayerRotationSpeed;

			if (worldTransformBody_.rotation_.y > kMaxPlayerRotation) {
				worldTransformBody_.rotation_.y = kMaxPlayerRotation;
			} else if (worldTransformBody_.rotation_.y < -kMaxPlayerRotation) {
				worldTransformBody_.rotation_.y = -kMaxPlayerRotation;
			}
		}
	} else {
	
		if (worldTransformBody_.rotation_.y > 0) {
			worldTransformBody_.rotation_.y -= kPlayerReturnSpeed;
			if (worldTransformBody_.rotation_.y < 0) {
				worldTransformBody_.rotation_.y = 0;
			}
		} else if (worldTransformBody_.rotation_.y < 0) {
			worldTransformBody_.rotation_.y += kPlayerReturnSpeed;
			if (worldTransformBody_.rotation_.y > 0) {
				worldTransformBody_.rotation_.y = 0;
			}
		}
	}

	worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, move);
	worldTransformBody_.UpdateMatrix();


}

void Player::BehaviorAttackUpdate() {

	static const float kAttackDuration = 0.3f; 
	


		XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}
	
		
	   if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && !attackExecuted) {
		isAttacking = true;
		   attackExecuted = true; 
		attackTime += 0.1f;

		
		if (attackTime > 0.0f) {
			worldTransformHammer_.rotation_.x += 0.1f;
		}
		
		if (attackTime >= 180.0f) {
			attackTime = 180.0f; 
		}
	} else {
		
		isAttacking = false;
		attackTime = 0.0f;
		ResetWeaponPosition();
	}

	worldTransformHammer_.UpdateMatrix();
}

void Player::ResetWeaponPosition() { worldTransformHammer_.Initialize(); }




