#define NOMINMAX

#include "Player.h"
#include <cassert>
#include "TextureManager.h"
#include <numbers>
#include <algorithm>
#include "Input.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <Windows.h>


using namespace MyMathematics;

Player::Player() {
}

Player::~Player() {

delete model_;

}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) { 
	

	assert(model); 

	this->model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() { 
	

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix(); 

	bool landing = false;

	if (velocity_.y < 0) {

		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	if (onGround_) {
		if (velocity_.y > 0.0f) {
		
		onGround_ = false;
		}

	if (Input::GetInstance()->PushKey(DIK_RIGHT)|| 
		Input::GetInstance()->PushKey(DIK_LEFT)) {
	
	Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
		if (velocity_.x < 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
		}
		    acceleration.x += kAcceleration;
		if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;

				turnFistRotationY_ = worldTransform_.translation_.y;
				turnTimer_ = kTimeTurn;

		}
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			if (velocity_.x > 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kAcceleration;
			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;

				turnFistRotationY_ = worldTransform_.translation_.y;
				turnTimer_ = kTimeTurn;

			}
		}
		velocity_ = Add(velocity_,acceleration);

		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	} else {
		velocity_.x *= (1.0f - kAttenuation);
	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		velocity_ = Add(velocity_, Vector3(0, kJumpAcceleration, 0));


	}
	} else {

		velocity_ = Add(velocity_, Vector3(0, -kGravityAcceleration, 0));

		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		if (landing) {

			worldTransform_.translation_.y = 1.0f;

			velocity_.x *= (1.0f - kAttenuation);

			velocity_.y = 0.0f;

			onGround_ = true;
		
		}


	}

	

	if (turnTimer_>0.0f) {

		turnTimer_ -= 1 / 60;

		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = easeInSine(turnTimer_, turnFistRotationY_, destinationRotationY, kTimeTurn);

	}
	
}


void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	

}



float Player::easeInSine(float frameX, float startX, float endX, float endFrameX) {
	
	float positionX = startX + (endX - startX) * easeIn(frameX / endFrameX);

	    return positionX;
}

float Player::easeIn(float frameX) { 
	return 1 - cosf(frameX * (float(M_PI) / 2.0f)); }
