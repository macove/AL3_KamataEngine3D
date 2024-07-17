#include "Enemy.h"
#include "Player.h"
#include <cassert>
#include "GameScene.h"
using namespace MyMathematics;

Enemy::~Enemy() {

	
}

void Enemy::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection) {

	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("./Resources/1642226.png");

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	input_ = Input::GetInstance();

	radius_ = 1.0f;
}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();

	const float kEnemySpeed = 0.1f;

	worldTransform_.translation_.z -= kEnemySpeed;
	if (!isDead_) {
	if (--fireTimer_ <= 0) {
		Fire();
		fireTimer_ = kFireInterval;
	}
	
	}

	//for (EnemyBullet* bullet : bullets_) {
	//	bullet->Update();
	//}
	//bullets_.remove_if([](EnemyBullet* bullet) {
	//	if (bullet->IsDead()) {
	//
	//		delete bullet;
	//		return true;
	//	}
	//	return false;
	//});

	if (worldTransform_.translation_.z < -40.0f) {
		worldTransform_.translation_.z = 40.0f;
	}
}

void Enemy::Draw() {

	if (!isDead_) {
	
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	}

	//for (EnemyBullet* bullet : bullets_) {
	//	bullet->Draw();
	//}
}

void Enemy::Fire() {

	const float kBulletSpeed = 1.0f;

	Vector3 enemyPos = worldTransform_.translation_;
	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 direction = Subtract(playerPos, enemyPos);
	direction = Normalize(direction);
	Vector3 velocity = Multiply(direction, kBulletSpeed);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, viewProjection_, velocity);

	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::InitializeApproachPhase() { fireTimer_ = kFireInterval; }

Vector3 Enemy::GetWorldPosition() { return Transform(Vector3{0, 0, 0}, worldTransform_.matWorld_); }

void Enemy::OnCollision() { isDead_ = true; }

float Enemy::GetRadius() const { return radius_; }