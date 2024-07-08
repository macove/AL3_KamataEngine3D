#define NOMINMAX


#include "Player.h"
#include <cassert>
#include "TextureManager.h"
#include <algorithm>
#include <math.h>


using namespace MyMathematics;


Player::~Player() { 
	
	 for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	
}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {

	assert(model); 

	model_ = model;

	textureHandle_ = textureHandle;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	input_ = Input::GetInstance();

	 //worldTransformBlock = &worldTransform_;

	 radius_ = 1.0f;

	 
}

void Player::Update() {


	//worldTransformBlock->UpdateMatrix();

	//worldTransform_.TransferMatrix(); 

	//worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	bool rightPressed = input_->PushKey(DIK_RIGHT);
	bool leftPressed = input_->PushKey(DIK_LEFT);
	bool upPressed = input_->PushKey(DIK_UP);
	bool downPressed = input_->PushKey(DIK_DOWN);
	bool forwardPressed = input_->PushKey(DIK_W);
	bool backwardPressed = input_->PushKey(DIK_S);

	if (rightPressed || leftPressed) {
		move.x = rightPressed ? kCharacterSpeed : -kCharacterSpeed;
	}
	if (upPressed || downPressed) {
		move.y = upPressed ? kCharacterSpeed : -kCharacterSpeed;
	}
	if (forwardPressed || backwardPressed) {
		move.z = forwardPressed ? kCharacterSpeed : -kCharacterSpeed;
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	//const float kMoveLimitX = 35.0f;
	//const float kMoveLimitY = 18.0f;
	//const float kMoveLimitZ = 50.0f;

	//worldTransform_.translation_.x = std::max(worldTransform_.translation_.x, -kMoveLimitX);
	//worldTransform_.translation_.x = std::min(worldTransform_.translation_.x, +kMoveLimitX);
	//worldTransform_.translation_.y = std::max(worldTransform_.translation_.y, -kMoveLimitY);
	//worldTransform_.translation_.y = std::min(worldTransform_.translation_.y, +kMoveLimitY);
	//worldTransform_.translation_.z = std::max(worldTransform_.translation_.z, -kMoveLimitZ);
	//worldTransform_.translation_.z = std::min(worldTransform_.translation_.z, +kMoveLimitZ);

	Rotate();
	

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {

			delete bullet;
			return true;
		}
		return false;
	});

	ImGui::Begin("Player");
	ImGui::PushItemWidth(100); 
	ImGui::SliderFloat("X", &worldTransform_.translation_.x, -35.0f, 35.0f);
	ImGui::SameLine();
	ImGui::SliderFloat("Y", &worldTransform_.translation_.y, -18.0f, 18.0f);
	ImGui::SameLine();
	ImGui::SliderFloat("Z", &worldTransform_.translation_.z, -10.0f, 10.0f);
	ImGui::End();

	

	Attack();

}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw();
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


if (input_->TriggerKey(DIK_SPACE)) {

	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);
	velocity = TransFormNormal(velocity, worldTransform_.matWorld_);



PlayerBullet* newBullet = new PlayerBullet();
    newBullet->SetParent(worldTransform_.parent_);
	newBullet->Initialize(model_, worldTransform_.translation_, viewProjection_,velocity);
	 bullets_.push_back(newBullet);

}




}

Vector3 Player::GetWorldPosition() { 

	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z-50.0f;

	return worldPos;

	//return Transform(Vector3{0, 0, 0}, worldTransform_.matWorld_); 

}

void Player::OnCollision() {}

float Player::GetRadius() const { return radius_; }

void Player::SetParent(const WorldTransform* parent) {

worldTransform_.parent_ = parent;

}

