#include "EndedScene.h"

EndedScene::~EndedScene() {

	delete sprite_;

}

void EndedScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();

	endedSprite_ = TextureManager::Load("./Resources/clear.png");

	sprite_ = Sprite::Create(endedSprite_, {0, 0});
}

void EndedScene::Update() {}

void EndedScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	sprite_->Draw();

	Sprite::PostDraw();



}
