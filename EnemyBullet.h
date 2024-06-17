#include"Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "MathematicsUtil.h"

#pragma once
class EnemyBullet {


	public:

		void Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection, const Vector3& velocity);

	    void Update();

	    void Draw();

		

	public:

		WorldTransform worldTransform_;

	    Model* model_ = nullptr;

	    uint32_t textureHandle_ = 0u;

	    ViewProjection* viewProjection_ = nullptr;

	    Vector3 velocity_;


};
