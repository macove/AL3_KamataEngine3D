#pragma once
#include "ViewProjection.h"
#include "Player.h"

class player;

class CameraController {

	public:


		 void Initialize(ViewProjection* viewProjection);

		 void Update();

		 void SetTarget(Player* target) { target_ = target; }

		 void Reset();

private:

	     ViewProjection* viewProjection_ = nullptr;

		 Player* target_ = nullptr;

		 Vector3 targetOffset_{0, 0, -15.0f};
};
