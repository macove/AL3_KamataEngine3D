#include "Ground.h"

void Ground::Initialize(Model* model, ViewProjection* viewProjection) {

 model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.scale_ = Vector3{20.0f, 1.0f, 20.0f};

	worldTransform_.Initialize();
}

void Ground::Update() {


worldTransform_.UpdateMatrix();


}

void Ground::Draw() { 
	
	
	
	model_->Draw(worldTransform_, *viewProjection_);


}
