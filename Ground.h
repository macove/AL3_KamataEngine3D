#pragma once
#include "WorldTransform.h"
#include "Model.h"


class Ground {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;
};
