#include "PlayerModel.h"

void PlayerModel::Initialize(Model* model, ViewProjection* viewProjection) {


model_ = model;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

}

void PlayerModel::Update() {


worldTransform_.TransferMatrix();

}

void PlayerModel::Draw() {

model_->Draw(worldTransform_, *viewProjection_);

}
