#define NOMINMAX

#include "Player.h"
#include "TextureManager.h"
#include <WinApp.h>
#include <algorithm>
#include <cassert>
#include <math.h>

using namespace MyMathematics;

Player::~Player() {

	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

	delete sprite2DReticle_;
}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {

	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	viewProjection_ = viewProjection;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	input_ = Input::GetInstance();

	worldTransformBlock = &worldTransform_;

	radius_ = 1.0f;

	worldTransform3DReticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("./Resources/reticle.png");
	sprite2DReticle_ = Sprite::Create(textureReticle, Vector2(0.0f, 0.0f), Vector4(1.0f, 1.0f, 1.0f, 1.0f), Vector2(0.5f, 0.5f));

	
	Vector3 positionReticle = worldTransform3DReticle_.translation_;
	
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matViewProjectionViewport = Multiply(Multiply(viewProjection_->matView, viewProjection_->matProjection), matViewport);
	
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
	

}

void Player::Update() {

	 // Handle input
	XINPUT_STATE joyState;
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.4f;
	
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// Move the player based on joystick input
		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	
	// Update player position and apply movement limits
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	
	const float kMoveLimitX = 40.0f; // Limit for x-axis movement
	const float kMoveLimitY = 20.0f; // Limit for y-axis movement
	const float kMoveLimitZ = 80.0f; // Limit for z-axis movement
	
	// Apply movement limits
	worldTransform_.translation_.x = std::max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = std::min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = std::max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = std::min(worldTransform_.translation_.y, +kMoveLimitY);
	worldTransform_.translation_.z = std::max(worldTransform_.translation_.z, -kMoveLimitZ);
	worldTransform_.translation_.z = std::min(worldTransform_.translation_.z, +kMoveLimitZ);

	// Handle attack logic
	Attack();

	// Handle rotation logic
	Rotate();

	// Update the position of the 3D reticle relative to the player
	const float kDistancePlayerTo3DReticle = 50.0f; // Distance from player to reticle
	Vector3 offset = {0, 0, 1.0f};                  // Offset in front of the player
	offset = Multiply(offset, worldTransform_.matWorld_);
	offset = Multiply(Normalize(offset), kDistancePlayerTo3DReticle);
	worldTransform3DReticle_.translation_ = Add(worldTransform_.translation_, offset);
	worldTransform3DReticle_.UpdateMatrix();

	// Update the position of the 2D reticle based on joystick input
	Vector2 spritePosition = sprite2DReticle_->GetPosition();

	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matViewProjectionViewport = Multiply(Multiply(viewProjection_->matView, viewProjection_->matProjection), matViewport);
	Matrix4x4 matInverseVPV = Inverse(matViewProjectionViewport);
	Vector3 posNear = Vector3(float(spritePosition.x), float(spritePosition.y), 0.0f);
	Vector3 posFar = Vector3(float(spritePosition.x), float(spritePosition.y), 1.0f);
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);
	Vector3 joystickDirection = Subtract(posFar, posNear);
	joystickDirection = Normalize(joystickDirection);
	const float kDistanceTestObject = 100.0f;
	worldTransform3DReticle_.translation_ = Add(posNear, Multiply(joystickDirection, kDistanceTestObject));
	
	worldTransform3DReticle_.translation_.z = 100.0f;

	worldTransform3DReticle_.UpdateMatrix();

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		spritePosition.x += ((float)joyState.Gamepad.sThumbRX / SHRT_MAX) * 10.0f;
		spritePosition.y -= ((float)joyState.Gamepad.sThumbRY / SHRT_MAX) * 10.0f;
		sprite2DReticle_->SetPosition(spritePosition);
	}

	


	// Update each bullet and remove dead bullets
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// Update debug UI with ImGui
	ImGui::Begin("Player");
	ImGui::PushItemWidth(100);
	ImGui::SliderFloat("X", &worldTransform_.translation_.x, -40.0f, 40.0f);
	ImGui::SameLine();
	ImGui::SliderFloat("Y", &worldTransform_.translation_.y, -.0f, 20.0f);
	ImGui::SameLine();
	ImGui::SliderFloat("Z", &worldTransform_.translation_.z, -80.0f, 80.0f);
	ImGui::Text("3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x, worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();

	// Update the transformation matrix
	worldTransformBlock->UpdateMatrix();
}

void Player::Draw() {

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
	//model_->Draw(worldTransform3DReticle_, *viewProjection_, textureHandle_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Rotate() {

	bool aPressed = input_->PushKey(DIK_A);
	bool dPressed = input_->PushKey(DIK_D);

	if (aPressed || dPressed) {

		worldTransform_.rotation_.y += aPressed ? kRotSpeed : -kRotSpeed;
	}
}

void Player::Attack() {

	XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		Vector3 bulletDirection = Subtract(worldTransform3DReticle_.translation_, worldTransform_.translation_);
		bulletDirection = Normalize(bulletDirection);
		const float kBulletSpeed = 1.0f;
		Vector3 velocity = Multiply(bulletDirection, kBulletSpeed);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->SetParent(worldTransform_.parent_);
		newBullet->Initialize(model_, worldTransform_.translation_, viewProjection_, velocity);
		bullets_.push_back(newBullet);
	}
}

Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z - 50.0f;

	return worldPos;

	// return Transform(Vector3{0, 0, 0}, worldTransform_.matWorld_);
}

void Player::OnCollision() {}

float Player::GetRadius() const { return radius_; }

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

void Player::DrawUI() { sprite2DReticle_->Draw(); }
