#include"Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"

#pragma once

class PlayerBullet {

	public:

	void Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection);

	 void Update();

	 void Draw();

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

};
