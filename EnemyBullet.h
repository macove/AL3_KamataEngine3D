#include"Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "MathematicsUtil.h"

#pragma once
class EnemyBullet {


	public:

		void Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection, const Vector3& velocity);

	    void Update();

	    void Draw();

		void OnCollision();

		 bool IsDead() const { return isDead_; } 

		float GetRadius() const;

	public:

		WorldTransform worldTransform_;

	    Model* model_ = nullptr;

	    uint32_t textureHandle_ = 0u;

	    ViewProjection* viewProjection_ = nullptr;

	    Vector3 velocity_;

		static const int32_t kLifeTime = 60 * 3;

	    int32_t deathTime_ = kLifeTime;

	    bool isDead_ = false;

		float radius_;

};
