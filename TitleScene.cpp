#include "TitleScene.h"


TitleScene::~TitleScene() { 
	
	delete sprite_;


}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();

	titleSprite_ = TextureManager::Load("./Resources/title.png");

	 sprite_ = Sprite::Create(titleSprite_, {0, 0});
}

void TitleScene::Update() {

	 

}

void TitleScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	sprite_->Draw();
	
	Sprite::PostDraw();
}
