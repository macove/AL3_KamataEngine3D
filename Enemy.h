#pragma once
#include"BaseCharacter.h"
#include "WorldTransform.h"
#include "Model.h"
#include "MathematicsUtil.h"
#include <ViewProjection.h>


class Enemy : public BaseCharacter {

	public:
	 void Initialize(const std::vector<Model*>& models) override;


	  void Update() override;


	  void Draw(const ViewProjection& viewProjection) override;



private:
	  WorldTransform worldTransform_;

	static constexpr int kModelIndexBody = 0;

	  ViewProjection* viewProjection_ = nullptr;


	   float rotationAngle_ = 0.0f;
	  const float radius_ = 5.0f;
	  const float rotationSpeed_ = 0.02f;

};
