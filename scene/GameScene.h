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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用

	//textureHandle
	//uint32_t textureHandle_ = 0;
	//Sprite
	//Sprite* sprite_ = nullptr;
	//ViewProjection
	//ViewProjection viewProjection_;
	//自キャラ
	Player* player_ = nullptr;
	//ViewProjection* ViewProjection_ = nullptr;
	Model* playerModel_ = nullptr;

	///////////////////////////////////////

	uint32_t block_ = 0u;
	Model* modelBlock_ = nullptr;
	ViewProjection* ViewProjection_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;


	/// </summary>
};
