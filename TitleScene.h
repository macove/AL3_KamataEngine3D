#pragma once
#include "SceneState.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include <WinApp.h>
class TitleScene {

public:
	
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

private:

	DirectXCommon* dxCommon_ = nullptr;

	uint32_t titleSprite_ = 0; 

	Sprite* sprite_ = nullptr;

};
