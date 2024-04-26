#include "Player.h"
#include <cassert>
#include "TextureManager.h"
#include "Mathematics.h"

Player::Player() {
}

Player::~Player() {

delete model_;

}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) { 
	

	assert(model); 

	this->model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	
}

void Player::Update() { 
	
	worldTransform_.UpdateMatrix(); 

}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	

}
