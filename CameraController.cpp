#define NOMINMAX

#include "CameraController.h"
#include <WorldTransform.h>

using namespace MyMathematics;

void CameraController::Initialize(ViewProjection* viewProjection) {

	viewProjection_ = viewProjection;


}

void CameraController::Update() {



	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	viewProjection_->translation_ = Add(targetWorldTransform.translation_, targetOffset_);


	viewProjection_->translation_.x = std::max(moveableArea_.left, std::min(viewProjection_->translation_.x, moveableArea_.right));
	viewProjection_->translation_.y = std::max(moveableArea_.bottom, std::min(viewProjection_->translation_.y, moveableArea_.top));

	viewProjection_->UpdateMatrix();


}

void CameraController::Reset() {

	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	viewProjection_->translation_ = Add(targetWorldTransform.translation_,targetOffset_);

	//viewProjection_->UpdateMatrix();
}
