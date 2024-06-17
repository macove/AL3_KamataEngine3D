#include "Enemy.h"
#include <cassert>

using namespace MyMathematics;

Enemy::~Enemy() {

	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("./Resources/1642226.png");

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	input_ = Input::GetInstance();

}

void Enemy::Update() {

 worldTransform_.UpdateMatrix();

 const float kEnemySpeed = 0.1f;

  worldTransform_.translation_.z -= kEnemySpeed;

  if (--fireTimer_ <= 0) {
	  Fire();
	  fireTimer_ = kFireInterval; 
  }
  for (EnemyBullet* bullet : bullets_) {
	  bullet->Update();
  }
  /*bullets_.remove_if([](EnemyBullet* bullet) {
	  if (bullet->IsDead()) {

		  delete bullet;
		  return true;
	  }
	  return false;
  });*/



   if (worldTransform_.translation_.z < -40.0f) {
	  worldTransform_.translation_.z = 40.0f;
  }

  
}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw();
	}

}

void Enemy::Fire() {

		const float kBulletSpeed = -1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = TransFormNormal(velocity, worldTransform_.matWorld_);

		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, viewProjection_, velocity);

		bullets_.push_back(newBullet);
	
		

}

void Enemy::InitializeApproachPhase() {

	fireTimer_ = kFireInterval;
}


