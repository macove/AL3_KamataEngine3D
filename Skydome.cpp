#include "Skydome.h"

void Skydome::Initialize(Model* model, ViewProjection* viewProjection) {



    model_ = model;

	viewProjection_ = viewProjection;
	
	worldTransform_.scale_ = Vector3{3.0f, 3.0f, 3.0f};

	worldTransform_.Initialize();

}

void Skydome::Update() {

worldTransform_.UpdateMatrix();

}

void Skydome::Draw() {

model_->Draw(worldTransform_, *viewProjection_);

}
