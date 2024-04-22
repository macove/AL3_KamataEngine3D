#include "WorldTransform.h"
#include "Model.h"




#pragma once
class Player {

	public:

		Player();

		~Player();

	    /// <summary>
	    /// 初期化
	    /// </summary>
		
		///<param name = "model">

		///</param>

	    void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

		/// <summary>
	    /// 更新
	    /// </summary>
	    void Update();

		/// <summary>
	    /// 描画
	    /// </summary>
	    void Draw();


		private:

			WorldTransform worldTransform_;

			Model* model_ = nullptr;

			uint32_t textureHandle_ = 0u;

			ViewProjection* viewProjection_ = nullptr;

};
