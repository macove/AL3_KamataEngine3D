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




class Enemy {

public:

	~Enemy();

		void Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection);

	    void Update();

	    void Draw();

		void Fire();

		 void InitializeApproachPhase();

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	 Phase phase_ = Phase::Approach;

	 Input* input_ = nullptr;
	 
	 static const int32_t kLifeTime = 0;

	  static const int32_t kFireInterval = 60;
	 int32_t fireTimer_ = kFireInterval;

	 std::list<EnemyBullet*> bullets_;
};
