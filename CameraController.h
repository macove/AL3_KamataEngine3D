#pragma once
#include "ViewProjection.h"

class CameraController {

	public:


		 void Initialize(ViewProjection* viewProjection);

		 void Update();





private:

	     ViewProjection* viewProjection_ = nullptr;

};
