#define NOMINMAX


#include "Player.h"
#include <cassert>
#include "TextureManager.h"
#include <algorithm>
#include <math.h>






using namespace MyMathematics;






Player::~Player() { 
	
	delete bullet_;
	

}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {

	assert(model); 

	model_ = model;

	textureHandle_ = textureHandle;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();

	 worldTransformBlock = &worldTransform_;
}

void Player::Update() {

	//worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
	//
	//worldTransformBlock->TransferMatrix();

	worldTransformBlock->UpdateMatrix();

	worldTransform_.TransferMatrix(); 

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	bool rightPressed = input_->PushKey(DIK_RIGHT);
	bool leftPressed = input_->PushKey(DIK_LEFT);
	bool upPressed = input_->PushKey(DIK_UP);
	bool downPressed = input_->PushKey(DIK_DOWN);

	if (rightPressed || leftPressed) {
		move.x = rightPressed ? kCharacterSpeed : -kCharacterSpeed;
	}
	if (upPressed || downPressed) {
		move.y = upPressed ? kCharacterSpeed : -kCharacterSpeed;
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 18.0f;

	worldTransform_.translation_.x = std::max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = std::min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = std::max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = std::min(worldTransform_.translation_.y, +kMoveLimitY);

	Rotate();


	Attack();

	if (bullet_) {
	
	bullet_->Update();
	}

	ImGui::Begin("Player");
	ImGui::PushItemWidth(100); 
	ImGui::SliderFloat("X", &worldTransform_.translation_.x, -35.0f, 35.0f);
	ImGui::SameLine();
	ImGui::SliderFloat("Y", &worldTransform_.translation_.y, -18.0f, 18.0f);
	ImGui::SameLine();
	ImGui::SliderFloat("Z", &worldTransform_.translation_.z, -10.0f, 10.0f);
	ImGui::End();



	
}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

	if (bullet_) {
		bullet_->Draw();
	}

}

void Player::Rotate() {



bool aPressed = input_->PushKey(DIK_A);
bool dPressed = input_->PushKey(DIK_D);

if (aPressed || dPressed) {

worldTransform_.rotation_.y += aPressed ? kRotSpeed : -kRotSpeed;

}





}

void Player::Attack() {


if (input_->PushKey(DIK_SPACE)) {
	
PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, viewProjection_);

	 bullet_ = newBullet;

}




}
