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

 worldTransform_.translation_.z -= kEnemySpeed;

}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);


}
