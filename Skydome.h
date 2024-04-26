#include "WorldTransform.h"
#include "Model.h"



#pragma once
class Skydome {

public:
	/// <summary>
	/// ゲームシーン
	/// </summary>
	void Initialize(Model* model,ViewProjection* viewProjection);

	/// <summary>
	/// ゲームシーン
	/// </summary>
	void Update();

	/// <summary>
	/// ゲームシーン
	/// </summary>
	void Draw();


	private:

	    WorldTransform worldTransform_;

	    Model* model_ = nullptr;

	    ViewProjection* viewProjection_ = nullptr;
};
