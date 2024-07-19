#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"
#include "Player.h"
#include <vector>
#include "DebugCamera.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	/////////////////////////
	/////////////////////////
	/////////////////////////

	void GenerateBlock();


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用

	ViewProjection* ViewProjection_ = nullptr;

	//textureHandle
	//uint32_t textureHandle_ = 0;
	//Sprite
	//Sprite* sprite_ = nullptr;
	//ViewProjection
	//ViewProjection viewProjection_;
	//自キャラ
	Player* player_ = nullptr;
	
	Model* playerModel_ = nullptr;

	///////////////////////////////////////

	uint32_t block_ = 0u;
	Model* modelBlock_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;

	//////////////////////////////////////

	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;


	//////////////////////////////////////
	//map chip field
	MapChipField* mapChipField_ = nullptr;


	CameraController* cameraController_ = nullptr;

	/// </summary>
};
