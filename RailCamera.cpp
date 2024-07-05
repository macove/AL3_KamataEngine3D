#include "RailCamera.h"
#include "MathematicsUtil.h"
#include <imgui.h>

using namespace MyMathematics;

void RailCamera::Initialize() {

	//viewProjection_ = viewProjection;
	worldTransform_.translation_ = Vector3(0.0f, 0.0f, -50.0f);
	worldTransform_.rotation_ = Vector3(0.0f, 0.0f, 0.0f);

	  viewProjection_.Initialize();

	  viewProjection_.farZ = 1000.0f;
}

void RailCamera::Update() {

	 Vector3 move = {0.0f, 0.0f, 0.0f};
	 Vector3 rot = {0.0f, 0.0f, 0.0f};

	
	ImGui::Begin("camera");
	ImGui::PushItemWidth(300);
	ImGui::DragFloat3("translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("rotation", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();

	
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, rot);

	
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	//viewProjection_.TransferMatrix();

}

const WorldTransform& RailCamera::GetWorldTransform() const { return worldTransform_; }

const ViewProjection& RailCamera::GetViewProjection() const { return viewProjection_; }


