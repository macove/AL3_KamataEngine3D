#include "PlayerBullet.h"
#include <cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection) {


	assert(model);

	model_ = model;

	textureHandle_ = TextureManager::Load("./Resources/white1x1.png");

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;


}

void PlayerBullet::Update() {

	
	
	 worldTransform_.UpdateMatrix();




}

void PlayerBullet::Draw() {



model_->Draw(worldTransform_, *viewProjection_, textureHandle_);



}
