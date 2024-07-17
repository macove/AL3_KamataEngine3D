#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"
#include "DebugCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"
#include <sstream>
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

	void CheckAllCollisions();

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

	void SpawnEnemy(const Vector3& position);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;


	Player* player_ = nullptr;
	ViewProjection* ViewProjection_ = nullptr;
	Model* playerModel_ = nullptr;

	bool isDebugCameraActive_ = false;
	
	DebugCamera* debugCamera_ = nullptr;

	Enemy* enemy_ = nullptr;
	Model* enemyModel_ = nullptr;


	Skydome* skydome_ = nullptr;

	Model* modelSkydome_ = nullptr;

	RailCamera* railCamera_ = nullptr;

    //std::list<Enemy*> enemies_;
    std::list<EnemyBullet*> enemyBullets_;

	std::stringstream enemyPopCommands;
	
	std::list<Enemy*> enemies_;

	bool isWaiting_ = false; 
    int32_t waitTimer_ = 0;

};
