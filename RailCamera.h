#pragma once
#include "WorldTransform.h"
#include <ViewProjection.h>

class RailCamera {


	
public:
	/// <summary>
	/// ゲームシーン
	/// </summary>
	void Initialize();

	/// <summary>
	/// ゲームシーン
	/// </summary>
	void Update();

	 const WorldTransform& GetWorldTransform() const;
	 const ViewProjection& GetViewProjection() const;

	private:
	WorldTransform worldTransform_;


	ViewProjection viewProjection_;




};
