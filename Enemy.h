#include"Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "MathematicsUtil.h"

#pragma once
class Enemy {


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
