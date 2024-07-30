#pragma once
#include "ViewProjection.h"
#include "Player.h"

class player;

struct Rect // limit the cameras movement
{
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};


class CameraController {

	public:


		 void Initialize(ViewProjection* viewProjection);

		 void Update();

		 void SetTarget(Player* target) { target_ = target; }

		 void Reset();

		 void SetMoveableArea(Rect area) { moveableArea_ = area; };

private:

	     ViewProjection* viewProjection_ = nullptr;

		 Player* target_ = nullptr;

		 Vector3 targetOffset_{0, 0, -40.0f};

		 Rect moveableArea_ = {0, 100, 0, 100};
	     Vector3 targetPosition;
	     static inline const float kInterpolationRate = 0.1f;
	     static inline const float kVelocityBias = 20.0f;
	     static inline const Rect margin = {-400, 400, -200, 200};

};
