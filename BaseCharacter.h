#pragma once
#include <vector>
#include <cassert>
#include <Input.h>
#include <Model.h>
#include <WorldTransform.h>

class BaseCharacter {


	public:


		 virtual void Initialize(const std::vector<Model*>& models);

		 virtual void Update();

		 virtual void Draw(const ViewProjection& viewProjection);


		 const WorldTransform& GetWorldTransform() const { return worldTransform_; }



	private:



	protected:

	 std::vector<Model*> models_;
	 WorldTransform worldTransform_;





};
