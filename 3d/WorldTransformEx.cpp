#include "WorldTransform.h"
#include "MathematicsUtil.h"

using namespace MyMathematics;

void WorldTransform::UpdateMatrix() {

	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	TransferMatrix();

}