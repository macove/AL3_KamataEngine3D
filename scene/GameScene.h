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
#include <memory>
#include "Skydome.h"
#include "Ground.h"
#include <DebugCamera.h>
#include "FollowCamera.h"

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
	std::unique_ptr<Player> player_;
	std::unique_ptr<ViewProjection> ViewProjection_;
	std::unique_ptr<Model> playerModel_;


	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> modelSkydome_;


	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Model> modelGround_;

	bool isDebugCameraActive_ = false;
	std::unique_ptr<DebugCamera> debugCamera_;

	std::unique_ptr<FollowCamera> followCamera_;

	/// </summary>
};
