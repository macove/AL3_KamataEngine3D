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

//delete model_;

}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) { 
	

	assert(model); 

	model_ = model;
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

	
	if (Input::GetInstance()->PushKey(DIK_UP)) {
		velocity_ = Add(velocity_, Vector3(0, kJumpAcceleration, 0));

	}

	} else {

		velocity_ = Add(velocity_, Vector3(0, -kGravityAcceleration, 0));

		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		if (landing) {

			worldTransform_.translation_.y = 2.0f;

			velocity_.x *= (1.0f - kAttenuation);

			velocity_.y = 0.0f;

			onGround_ = true;
		
		}


	}

	UpdateInput();

	CollisionMapInfo collisionMapInpo;
	collisionMapInpo.CalculatePlayerMovement = velocity_;
	//CheckMapCollision(collisionMapInpo);
	
}


void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);
	

}



float Player::easeInSine(float frameX, float startX, float endX, float endFrameX) {
    float positionX = startX + (endX - startX) * easeIn(frameX / endFrameX);
    return positionX;
}

float Player::easeIn(float frameX) { 
    return 1 - cosf(frameX * (float(M_PI) / 2.0f)); 
}

void Player::UpdateInput() {
	Vector3 acceleration = {};

	bool rightPressed = Input::GetInstance()->PushKey(DIK_RIGHT);
	bool leftPressed = Input::GetInstance()->PushKey(DIK_LEFT);

	if (rightPressed || leftPressed) {
		HandleDirectionChange(rightPressed, leftPressed);
		acceleration.x = rightPressed ? kAcceleration : -kAcceleration;
	}

	velocity_ = Add(velocity_, acceleration);
	velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	if (!rightPressed && !leftPressed) {
		velocity_.x *= (1.0f - kAttenuation);
		return; 
	}

	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 0.1f / 60.0f;
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		worldTransform_.rotation_.y = easeInSine(turnTimer_, turnFistRotationY_, destinationRotationY, kTimeTurn);
	}
}

void Player::HandleDirectionChange(bool rightPressed, bool leftPressed) {
    LRDirection newDirection = rightPressed ? LRDirection::kRight : LRDirection::kLeft;
    if (newDirection != lrDirection_) {
        lrDirection_ = newDirection;
        turnFistRotationY_ = worldTransform_.rotation_.y; // rotation_.y
        turnTimer_ = kTimeTurn;
    }
    if ((rightPressed && velocity_.x < 0.0f) || (leftPressed && velocity_.x > 0.0f)) {
        velocity_.x *= (1.0f - kAttenuation);
    }
}

//void Player::CheckMapUpCollision(CollisionMapInfo& info) {}

//void Player::CheckMapDownCollision(CollisionMapInfo& info) {}

//void Player::CheckMapRightCollision(CollisionMapInfo& info) {}
//
//void Player::CheckMapLeftCollision(CollisionMapInfo& info) {}






