#include "Enemy.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Enemy::Initialize(const std::vector<Model*>& models) {

	worldTransform_.Initialize(); 


	 BaseCharacter::Initialize(models);


}

void Enemy::Update() {

	rotationAngle_ -= rotationSpeed_;
	if (rotationAngle_ >= 2 * M_PI) {
		rotationAngle_ -= float(2 * M_PI);
	}

	float newX = radius_ * std::cos(rotationAngle_);
	float newZ = radius_ * std::sin(rotationAngle_);

	Vector3 moveVector = {newX - worldTransform_.translation_.x, 0.0f, newZ - worldTransform_.translation_.z};

	 worldTransform_.translation_.x = newX;
	worldTransform_.translation_.z = newZ;
	 worldTransform_.rotation_.y = -rotationAngle_;

	worldTransform_.UpdateMatrix();

}

void Enemy::Draw(const ViewProjection& viewProjection) {

	models_[kModelIndexBody]->Draw(worldTransform_, viewProjection);

}
