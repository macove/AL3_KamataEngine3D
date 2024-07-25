#include "Player.h"
#include <cassert>
#include "TextureManager.h"

Player::Player() {
}

Player::~Player() {



}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) { 
	

	assert(model); 

	this->model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	
}

void Player::Update() { 
	
	worldTransform_.TransferMatrix(); 

}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	

}
