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

	radius_ = 1.0f;
}

void EnemyBullet::Update() {

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();

	if (--deathTime_ <= 0) {

		isDead_ = true;
	}

}

void EnemyBullet::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);


}



void EnemyBullet::OnCollision() { isDead_ = true; }

float EnemyBullet::GetRadius() const { return radius_; }

Vector3 EnemyBullet::GetWorldPosition() { return Transform(Vector3{0, 0, 0}, worldTransform_.matWorld_); }


