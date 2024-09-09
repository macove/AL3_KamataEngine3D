#include "Ground.h"

void Ground::Initialize(Model* model, ViewProjection* viewProjection) {

 model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
	worldTransform_.scale_ = Vector3{50.0f, 1.0f, 50.0f};
	worldTransform_.rotation_ = Vector3{0.0f, 3.0f, 0.0f};
}

void Ground::Update() {


worldTransform_.UpdateMatrix();


}

void Ground::Draw() { 
	
	
	
	model_->Draw(worldTransform_, *viewProjection_);


}
