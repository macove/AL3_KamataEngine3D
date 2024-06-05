#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "MathematicsUtil.h"
#include "imgui.h"
#pragma once




class Player {



	public:



		 void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

		 void Update();

		 void Draw();





		private:


			WorldTransform worldTransform_;

	        Model* model_ = nullptr;

	        uint32_t textureHandle_ = 0u;

	        ViewProjection* viewProjection_ = nullptr;

			Input* input_ = nullptr;

			WorldTransform* worldTransformBlock = nullptr;

};
