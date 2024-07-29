#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <memory>


GameScene::GameScene() {


}

GameScene::~GameScene() { 
	//delete sprite_;
	//delete player_;
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = std::make_unique<Player>();
	playerModel_.reset(Model::Create());
	ViewProjection_ = std::make_unique<ViewProjection>();


    uint32_t playerTextureHandle = TextureManager::Load("./Resources/kuma1.png");


	ViewProjection_->Initialize();

	player_->Initialize(playerModel_.get(), playerTextureHandle, ViewProjection_.get());

	skydome_ = new Skydome();

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_->Initialize(modelSkydome_, ViewProjection_.get());
}

void GameScene::Update() {

	player_->Update();
	skydome_->Update();
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	//sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw();

	skydome_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	



#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
