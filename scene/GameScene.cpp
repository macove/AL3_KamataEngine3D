#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MathematicsUtil.h"

using namespace MyMathematics;


GameScene::GameScene() {


}

GameScene::~GameScene() { 
	//delete sprite_;
	delete player_;
	delete modelBlock_;
	delete debugCamera_;
	delete modelSkydome_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
		delete worldTransformBlock;
	    }
	}
	worldTransformBlocks_.clear();

}

void GameScene::Initialize() {

	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = new Player();

	playerModel_ = new Model();

	ViewProjection_ = new ViewProjection();

    uint32_t playerTextureHandle = TextureManager::Load("./Resources/kuma1.png");

	playerModel_ = Model::Create();

	ViewProjection_->Initialize();

	//ViewProjection_->farZ = 10;

	player_->Initialize(playerModel_, playerTextureHandle, ViewProjection_);

	///////////////////////////////////

	modelBlock_ = Model::Create();

	//要素数
	const uint32_t kNumBlockVertical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	//
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;
	
	
	
	worldTransformBlocks_.resize(kNumBlockVertical);
	
	for (uint32_t i = 0; i < kNumBlockVertical; ++i) 
	{
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
		// cubeの生成
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (i % 2 ==1 && j % 2==1 ||i%2==0 && j%2==0) {
				worldTransformBlocks_[i][j] = new WorldTransform();
				worldTransformBlocks_[i][j]->Initialize();
				worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
				worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
			}
			
		}
	}
	

	debugCamera_ = new DebugCamera(kNumBlockHorizontal, kNumBlockVertical);

	///////////////////////////////////////////////

	skydome_ = new Skydome();

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_->Initialize(modelSkydome_, ViewProjection_);





}

void GameScene::Update() {

	player_->Update();
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			worldTransformBlock->TransferMatrix();
		}
	}

	

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

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, *ViewProjection_);
		}
	}
	
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
