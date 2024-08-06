#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <ViewProjection.h>
#include "MathematicsUtil.h"

class FollowCamera {



public:

	void Initialize(ViewProjection* viewProjection);


	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

private:

	ViewProjection* viewProjection_ = nullptr;
	const WorldTransform* target_ = nullptr;

};
