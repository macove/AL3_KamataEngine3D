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
	delete playerModel_;
	delete modelBlock_;
	delete modelSkydome_;
	delete ViewProjection_;
	delete skydome_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
		delete worldTransformBlock;
	    }
	}
	worldTransformBlocks_.clear();

	delete mapChipField_;
	delete debugCamera_;
	delete cameraController_;
}

void GameScene::Initialize() {

	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = new Player();

	playerModel_ = new Model();

	ViewProjection_ = new ViewProjection();

	playerModel_ = Model::CreateFromOBJ("playerModel", true);

	ViewProjection_->Initialize();

	//ViewProjection_->farZ = 10;

	//////////////////////////////////////////////////////

	mapChipField_ = new MapChipField;
	mapChipField_->ResetMapChipData();
	mapChipField_->LoadMapChipCsv("Resources/block.csv");

	GenerateBlock();

	/////////////////////////////////

	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1,18);

	player_->Initialize(playerModel_, ViewProjection_, playerPosition);

	player_->setMapChipField(mapChipField_);

	///////////////////////////////////

	debugCamera_ = new DebugCamera(1280, 720);

	///////////////////////////////////////////////

	skydome_ = new Skydome();

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_->Initialize(modelSkydome_, ViewProjection_);

	///////////////////////////////////////////////

	cameraController_ = new CameraController; 
	cameraController_->Initialize(ViewProjection_);
	cameraController_->SetTarget(player_); 
	Rect cameraMovableArea = {0.0f, 100.0f, 0.0f, 100.0f}; 
	//cameraController_->SetMovableArea(cameraMovableArea);

	cameraController_->Reset();


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
		isDebugCameraActive_ ^= true;
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

	cameraController_->Update();
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

void GameScene::GenerateBlock() {

	modelBlock_ = Model::Create();

	// 要素数

	uint32_t numBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVertical);

	for (uint32_t i = 0; i < numBlockVertical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
		// cubeの生成
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j,i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

	
	

}


