#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "MathematicsUtil.h"
#include "imgui.h"
#include "PlayerBullet.h"

#pragma once





class Player {


	public:

		 ~Player();

		 void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

		 void Update();

		 void Draw();

		 void Rotate();

		 void Attack();

		private:


			WorldTransform worldTransform_;

	        Model* model_ = nullptr;

	        uint32_t textureHandle_ = 0u;

	        ViewProjection* viewProjection_ = nullptr;

			Input* input_ = nullptr;

			WorldTransform* worldTransformBlock = nullptr;

			static inline const float kRotSpeed = 0.02f;

			PlayerBullet* bullet_ = nullptr;

};
