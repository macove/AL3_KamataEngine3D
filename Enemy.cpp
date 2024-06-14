#include "Enemy.h"
#include <cassert>

using namespace MyMathematics;

void Enemy::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("./Resources/1642226.png");

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;


}

void Enemy::Update() {

 worldTransform_.UpdateMatrix();

 const float kEnemySpeed = 0.1f;

 


 switch (phase_) { 
 case Phase::Approach:
 default:
	 worldTransform_.translation_.z -= kEnemySpeed;

	 if (worldTransform_.translation_.z < 0.0f) {
		 phase_ = Phase::Leave;
	 }
	 break;
 case Phase::Leave:
	
	 worldTransform_.translation_.x += 0.3f;
	 break;
 }

  if (worldTransform_.translation_.x > 40.0f) {
	 worldTransform_.translation_.z = 5.0f;
	  worldTransform_.translation_.x = 0.0f;
	 phase_ = Phase::Approach;
 }

}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);


}
