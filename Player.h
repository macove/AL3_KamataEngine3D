#include "WorldTransform.h"
#include "Model.h"
#include "MathematicsUtil.h"
#include <ViewProjection.h>


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

	    void Initialize(Model* model, ViewProjection* viewProjection);

		/// <summary>
	    /// 更新
	    /// </summary>
	    void Update();

		/// <summary>
	    /// 描画
	    /// </summary>
	    void Draw();
		
		const WorldTransform& GetWorldTransform() const;

		void SetViewProjection( ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

		private:

			WorldTransform worldTransform_;

			Model* model_ = nullptr;

		 ViewProjection* viewProjection_ = nullptr;

};
