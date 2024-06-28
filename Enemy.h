#include"Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "MathematicsUtil.h"
#include "EnemyBullet.h"
#include "Input.h"
#include <list>
#pragma once

enum class Phase {

	Approach,
	Leave,
};


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

		 const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

		 float GetRadius() const;

	 private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	 Phase phase_ = Phase::Approach;

	 Input* input_ = nullptr;

	 static const int32_t kFireInterval = 60;

	 int32_t fireTimer_ = kFireInterval;

	 std::list<EnemyBullet*> bullets_;

	  Player* player_ = nullptr;

	  float radius_;
};
