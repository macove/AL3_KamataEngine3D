#include "EnemyBullet.h"
#include <cassert>

using namespace MyMathematics;

void EnemyBullet::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection, const Vector3& velocity) {

	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("./Resources/white1x1.png");

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;


}

void EnemyBullet::Update() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();

	

}

void EnemyBullet::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);


}


