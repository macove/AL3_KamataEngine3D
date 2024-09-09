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
#include "Ground.h"
#include <Input.h>




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

	int GetPlayerHP() const { return player_->GetHP(); }

	void RemoveEnemy(Enemy* enemy);

	 void SetAllEnemiesDefeated(bool state) { allEnemiesDefeated_ = state; }
	bool IsAllEnemiesDefeated() const { return allEnemiesDefeated_; }
	 bool IsTimeOver() const { return gameTimer_ >= maxTime_; }

 private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;


	Player* player_ = nullptr;
	ViewProjection* ViewProjection_ = nullptr;
	Model* playerModel_ = nullptr;

	bool isDebugCameraActive_ = false;
	
	//DebugCamera* debugCamera_ = nullptr;

	
	Model* enemyModel_ = nullptr;


	Skydome* skyDomeSpring_ = nullptr;
	Model* modelSkyDomeSpring_ = nullptr;

	Skydome* skyDomeSummer_ = nullptr;
	Model* modelSkyDomeSummer_ = nullptr;

	Skydome* skyDomeAutumn_ = nullptr;
	Model* modelSkyDomeAutumn_ = nullptr;

	Skydome* skyDomeWinter_ = nullptr;
	Model* modelSkyDomeWinter_ = nullptr;

	RailCamera* railCamera_ = nullptr;

    std::list<EnemyBullet*> enemyBullets_;

	std::stringstream enemyPopCommands;
	
	std::list<Enemy*> enemies_;

	bool isWaiting_ = false; 
    int32_t waitTimer_ = 0;

	

	Ground* groundSpring_;
	Model* modelGroundSpring_;

	Ground* groundSummer_;
	Model* modelGroundSummer_;

	Ground* groundAutumn_;
	Model* modelGroundAutumn_;

	Ground* groundWinter_;
	Model* modelGroundWinter_;



	
	 
	 bool allEnemiesDefeated_ = false;

	 uint32_t playerHPSprite_ = 0; 
	 Sprite* playerHP_ = nullptr;

	 uint32_t playerXSprite_ = 0;
	 Sprite* playerX_ = nullptr;
	////////////////////////////////

	 uint32_t Sprite0_ = 0;
	 Sprite* SpriteX0_ = nullptr;

	 uint32_t Sprite1_ = 0;
	 Sprite* SpriteX1_ = nullptr;

	 uint32_t Sprite2_ = 0;
	 Sprite* SpriteX2_ = nullptr;

	 uint32_t Sprite3_ = 0;
	 Sprite* SpriteX3_ = nullptr;

	 uint32_t Sprite4_ = 0;
	 Sprite* SpriteX4_ = nullptr;

	 uint32_t Sprite5_ = 0;
	 Sprite* SpriteX5_ = nullptr;

	 uint32_t Sprite6_ = 0;
	 Sprite* SpriteX6_ = nullptr;

	 uint32_t Sprite7_ = 0;
	 Sprite* SpriteX7_ = nullptr;

	 uint32_t Sprite8_ = 0;
	 Sprite* SpriteX8_ = nullptr;

	 uint32_t Sprite9_ = 0;
	 Sprite* SpriteX9_ = nullptr;

	  float gameTimer_ = 0.0f;
	  float maxTime_ = 7200.0f;

};
