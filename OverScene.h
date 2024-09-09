#pragma once

#include "Sprite.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
class OverScene {


public:

	~OverScene();

	void Initialize();

	void Update();

	void Draw();





private:

	DirectXCommon* dxCommon_ = nullptr;

	uint32_t overSprite_ = 0;

	Sprite* sprite_ = nullptr;


};
