#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"ImGuiManager.h"
#include"PrimitiveDrawer.h"
#include"AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	//delete sprite_;
	delete player_;
	delete playerModel_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = new Player();

	playerModel_ = new Model();

	playerViewProjection_ = new ViewProjection();

	 uint32_t playerTextureHandle = TextureManager::Load("./Resources/sample.png");

	 playerModel_ = Model::Create();

	playerViewProjection_->Initialize();

	player_->Initialize(playerModel_, playerTextureHandle, playerViewProjection_);


	//worldTransform_.Initialize();
	//soundDateHandle_ = audio_->LoadWave("./Resources/fanfare.wav");
	//audio_->PlayWave(soundDateHandle_);
	//voiceHandle_ = audio_->PlayWave(soundDateHandle_, true);
	//PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	//debugCamera_ = new DebugCamera(1920, 1080);
	//AxisIndicator::GetInstance()->SetVisible(true);
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

	player_->Update();

	//if (input_->TriggerKey(DIK_SPACE)) {
	//	audio_->StopWave(voiceHandle_);
	//}

	//ImGui::Begin("Debug1");
	//ImGui::InputFloat3("InputFloat3", inputFloat3);
	//ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	//ImGui::End();
	//
	//ImGui::ShowDemoWindow();

	//debugCamera_->Update();

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

	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	

	//PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
	//PrimitiveDrawer::GetInstance()->DrawLine3d({0, 10, 0}, {10, 10, 10}, {0.0f, 1.0f, 0.0f, 1.0f});
	//PrimitiveDrawer::GetInstance()->DrawLine3d({10, 10, 10}, {20, 20, 30}, {0.0f, 0.0f, 1.0f, 1.0f});
	//PrimitiveDrawer::GetInstance()->DrawLine3d({20, 20, 30}, {0, 10, 0}, {0.0f, 0.0f, 1.0f, 1.0f});



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
