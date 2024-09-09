#pragma once
#include "WorldTransform.h"
#include <ViewProjection.h>



class RailCamera {


	
public:

	 Vector3 cameraPos[6];

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
	WorldTransform railWorldTransform_;

	//int cameraDirection = 0;
	//BYTE preButtons;
	//int countUp = 0;
	//int countDown = 0;
	//int j;
	//int k;

};
