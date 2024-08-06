#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <memory>


GameScene::GameScene() {


}

GameScene::~GameScene() { 
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = std::make_unique<Player>();
	playerModel_ = std::unique_ptr<Model>(Model::CreateFromOBJ("player1", true));
	ViewProjection_ = std::make_unique<ViewProjection>();

	ViewProjection_->Initialize();

	player_->Initialize(playerModel_.get(), ViewProjection_.get());

	skydome_ = std::make_unique <Skydome>();
	modelSkydome_ = std::unique_ptr<Model>(Model::CreateFromOBJ("skydome", true));
	skydome_->Initialize(modelSkydome_.get(), ViewProjection_.get());

	ground_ = std::make_unique <Ground>();
	modelGround_ = std::unique_ptr<Model>(Model::CreateFromOBJ("ground1", true));
	ground_->Initialize(modelGround_.get(), ViewProjection_.get());


	debugCamera_ = std::make_unique <DebugCamera>(1920, 1080);

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize(ViewProjection_.get());
	followCamera_->SetTarget(&player_.get()->GetWorldTransform());

	player_->SetViewProjection(ViewProjection_.get());

}

void GameScene::Update() {

	player_->Update();
	skydome_->Update();
	ground_->Update();
	followCamera_->Update();


	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_D)) {
		isDebugCameraActive_ = true;
	}

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		ViewProjection_->matView = debugCamera_->GetViewProjection().matView;
		ViewProjection_->matProjection = debugCamera_->GetViewProjection().matProjection;
		ViewProjection_->TransferMatrix();
	} else {
		ViewProjection_->UpdateMatrix();
	}

#endif

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

	ground_->Draw();

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
