#include "PlayerBullet.h"
#include <cassert>


using namespace MyMathematics;

void PlayerBullet::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection, const Vector3& velocity) {


	assert(model);

	model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	 velocity_ = velocity;

	 radius_ = 1.0f;
}

void PlayerBullet::Update() {

	 worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_); 
	
	 worldTransform_.UpdateMatrix();

	 if (--deathTime_ <= 0) {
	 
	 isDead_ = true;
	 }


}

void PlayerBullet::Draw() {



model_->Draw(worldTransform_, *viewProjection_);



}

void PlayerBullet::OnCollision() { isDead_ = true; }

float PlayerBullet::GetRadius() const { return radius_; }

void PlayerBullet::SetParent(const WorldTransform* parent) {

worldTransform_.parent_ = parent; 

}

Vector3 PlayerBullet::GetWorldPosition() { return Transform(Vector3{0, 0, 0}, worldTransform_.matWorld_); }
