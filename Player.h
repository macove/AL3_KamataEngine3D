#include "WorldTransform.h"
#include "Model.h"
#include "MathematicsUtil.h"
#include "PlayerModel.h"

class MapChipField;

enum class LRDirection {
	kRight,
	kLeft,
};

enum Corner {
	kRightUp,
	kRightDown,
	kBottomRight,
	kBottomLeft,
	kLeftDown,
	kLeftUp,
	kTopLeft,
	kTopRight,
	kNumCorner

};

struct  CollisionMapInfo {
	bool CheckCeilingCollision = false;
	bool CheckLandingStatus = false;
	bool CheckWallCollision = false;
	Vector3 CalculatePlayerMovement;
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

	    void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

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

		void setMapChipField(MapChipField* mapChipField) { this->mapChipField_ = mapChipField; }

		void UpdateInput();

		void HandleDirectionChange(bool rightPressed, bool leftPressed);

		const Vector3& GetVelocity() const { return velocity_; }

		void CheckMapUpCollision(CollisionMapInfo& info);
	    void CheckMapDownCollision(CollisionMapInfo& info);

		Vector3 GetWorldPosition() const;
	    const WorldTransform& GetWorldTransform() const;

	    //void CheckMapRightCollision(CollisionMapInfo& info);
	    //void CheckMapLeftCollision(CollisionMapInfo& info);

		private:

			WorldTransform worldTransform_;

			Model* model_ = nullptr;

			ViewProjection* viewProjection_ = nullptr;

		    Vector3 velocity_ = {};

			static inline const float kAcceleration = 1;

			static inline const float kAttenuation = 0.2f;

			static inline const float kLimitRunSpeed = 1;
			
			LRDirection lrDirection_ = LRDirection::kRight;

			float turnFistRotationY_ = 0.0f;

			float turnTimer_ = 0.0f;

			static inline const float kTimeTurn = 0.3f;

			bool onGround_ = true;

			static inline const float kGravityAcceleration = 5.0f;

			static inline const float kLimitFallSpeed = 2.0f;

			static inline const float kJumpAcceleration = 5.0f;

			MapChipField* mapChipField_ = nullptr;

			static inline const float kWidth = 0.8f;

			static inline const float kHeight = 0.8f;


};
