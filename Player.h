#include "WorldTransform.h"
#include "Model.h"
#include "MathematicsUtil.h"

enum class LRDirection {
	kRight,
	kLeft,
};



#pragma once
class Player {

	public:

		Player();

		~Player();

	    /// <summary>
	    /// 初期化
	    /// </summary>
		
		///<param name = "model">

		///</param>

	    void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

		/// <summary>
	    /// 更新
	    /// </summary>
	    void Update();

		/// <summary>
	    /// 描画
	    /// </summary>
	    void Draw();


		float easeInSine(float frameX, float startX, float endX, float endFrameX); 
		float easeIn(float frameX);

		private:

			WorldTransform worldTransform_;

			Model* model_ = nullptr;

			uint32_t textureHandle_ = 0u;

			ViewProjection* viewProjection_ = nullptr;

		    Vector3 velocity_ = {};

			static inline const float kAcceleration = 1;

			static inline const float kAttenuation = 0.7f;

			static inline const float kLimitRunSpeed = 1;
			
			LRDirection lrDirection_ = LRDirection::kRight;

			float turnFistRotationY_ = 0.0f;

			float turnTimer_ = 0.0f;

			static inline const float kTimeTurn = 0.3f;

			bool onGround_ = true;

			static inline const float kGravityAcceleration = 5.0f;

			static inline const float kLimitFallSpeed = 2.0f;

			static inline const float kJumpAcceleration = 5.0f;


};
