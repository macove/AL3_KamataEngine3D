#include "OverScene.h"

OverScene::~OverScene() { 

delete sprite_;

}

void OverScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();

	overSprite_ = TextureManager::Load("./Resources/over.png");

	sprite_ = Sprite::Create(overSprite_, {0, 0});

}

void OverScene::Update() {}

void OverScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	sprite_->Draw();

	Sprite::PostDraw();

}
