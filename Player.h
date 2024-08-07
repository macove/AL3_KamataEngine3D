#include "WorldTransform.h"
#include "Model.h"
#include "MathematicsUtil.h"
#include <ViewProjection.h>
#include "BaseCharacter.h"

#pragma once
class Player : public BaseCharacter {


	public:

		Player();

		~Player();

	    /// <summary>
	    /// 初期化
	    /// </summary>
		
		///<param name = "model">

		///</param>

	   void Initialize(const std::vector<Model*>& models) override;

		/// <summary>
	    /// 更新
	    /// </summary>
	   void Update() override;

		/// <summary>
	    /// 描画
	    /// </summary>
	   void Draw(const ViewProjection& viewProjection) override;
		
		const WorldTransform& GetWorldTransform() const;

		void SetViewProjection( ViewProjection* viewProjection) { viewProjection_ = viewProjection; }

		void InitializeFloatingGimmick();

		void UpdateFloatingGimmick();

		void SetParent(const WorldTransform* parent);


		private:

			WorldTransform worldTransform_;
	        WorldTransform worldTransformBase_;
	        WorldTransform worldTransformBody_;
	        WorldTransform worldTransformHead_;
	        WorldTransform worldTransformL_arm_;
	        WorldTransform worldTransformR_arm_;

			static constexpr int kModelIndexBody = 0;
	        static constexpr int kModelIndexHead = 1;
	        static constexpr int kModelIndexL_arm = 2;
	        static constexpr int kModelIndexR_arm = 3;

		 ViewProjection* viewProjection_ = nullptr;

		 float floatingParameter_ = 0.0f;

};
