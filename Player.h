#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "MathematicsUtil.h"
#include "imgui.h"
#include "PlayerBullet.h"
#include <list>
#include <Sprite.h>

#pragma once
//
//
//struct ViewProject {
//	Matrix4x4 matView;
//	Matrix4x4 matProjection;
//};


class Player {


	public:

		 ~Player();

		 void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

		 void Update();

		 void Draw();

		 void Rotate();

		 void Attack();

	     Vector3 GetWorldPosition();

		 void OnCollision();

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

			//ViewProject* viewProject_;
};
