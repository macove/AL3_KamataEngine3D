#include "CameraController.h"
#include <WorldTransform.h>

using namespace MyMathematics;

void CameraController::Initialize(ViewProjection* viewProjection) {

	viewProjection_ = viewProjection;


}

void CameraController::Update() {}

void CameraController::Reset() {

	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	viewProjection_->translation_ = Add(targetWorldTransform.translation_,targetOffset_);

	viewProjection_->UpdateMatrix();
}
