#include "MathematicsUtil.h"
#include "WorldTransform.h"

using namespace MyMathematics;

 void WorldTransform::UpdateMatrix() {

	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	//TransferMatrix();

 }