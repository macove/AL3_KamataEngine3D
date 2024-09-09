#include "EnemyBullet.h"
#include "Input.h"
#include "MathematicsUtil.h"
#include "Model.h"
#include "TextureManager.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include <list>
#pragma once

enum class Phase {

	Approach,
	Leave,
};
class GameScene;
class Player;

class Enemy {

public:
	~Enemy();

	void Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection);

	void Update();

	void Draw();

	void Fire();

	void InitializeApproachPhase();

	void SetPlayer(Player* player) { player_ = player; };

	Vector3 GetWorldPosition();

	void OnCollision();

	//const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	float GetRadius() const;

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	 int GetCount() const { return enemyCount_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	Phase phase_ = Phase::Approach;

	Input* input_ = nullptr;

	static const int32_t kFireInterval = 70;

	int32_t fireTimer_ = kFireInterval;

	std::list<EnemyBullet*> bullets_;

	Player* player_ = nullptr;

	float radius_;

	GameScene* gameScene_ = nullptr;

	bool isDead_ = false;

	Model* bulletModel_ = nullptr;

	int enemyCount_ = 20;
};