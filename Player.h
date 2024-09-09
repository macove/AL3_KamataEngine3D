#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "MathematicsUtil.h"
#include "PlayerBullet.h"
#include <list>
#include <Sprite.h>
#include <ViewProjection.h>

#pragma once


class Player {


	public:

		 ~Player();

		 void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

		 void Update();

		 void Draw();

		 void Rotate();

		 void Attack();

	     Vector3 GetWorldPosition();

		 void OnCollision();

		 int GetHP() const { return hp_; }

	     

		 const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	     float GetRadius() const;

		 void SetParent(const WorldTransform* parent);

		 void DrawUI();

		private:


			WorldTransform worldTransform_;

	        Model* model_ = nullptr;

	        uint32_t textureHandle_ = 0u;

	        ViewProjection* viewProjection_ = nullptr;

			Input* input_ = nullptr;

			WorldTransform* worldTransformBlock = nullptr;

			static inline const float kRotSpeed = 0.02f;

	        std::list<PlayerBullet*> bullets_;

			float radius_;

			WorldTransform worldTransform3DReticle_;

			Sprite* sprite2DReticle_ = nullptr;

			int hp_ = 10; 

			Model* bulletModel_ = nullptr;


			int bulletCount_ = 0;            
	        int cooldownTimer_ = 0;           
	        const int maxBulletCount_ = 10;   
	        const int cooldownDuration_ = 60; 

};
