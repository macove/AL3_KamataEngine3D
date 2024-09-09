#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
class EndedScene {

public:

	~EndedScene();

	void Initialize();

	void Update();

	void Draw();


private:

	DirectXCommon* dxCommon_ = nullptr;

	uint32_t endedSprite_ = 0;

	Sprite* sprite_ = nullptr;

};
