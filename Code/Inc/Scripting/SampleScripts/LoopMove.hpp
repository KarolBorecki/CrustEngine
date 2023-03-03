#ifndef _LOOPMOVE_HPP_
#define _LOOPMOVE_HPP_

#include <Scripting/CrustScript.hpp>

class LoopMove : public CrustScript {
public:
  LoopMove(Object* _parentObj, double _minX, double _maxX, double _minY, double _maxY, double _minZ, double _maxZ, double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ);
  ~LoopMove() override {}

  void Start() override;
  void Update(double deltaTime) override;
private:
  double maxX { 0.0 };
  double minX { 0.0 };
  double maxY { 0.0 };
  double minY { 0.0 };
  double maxZ { 0.0 };
  double minZ { 0.0 };
  double speedX { 0.0 };
  double speedY { 0.0 };
  double speedZ { 0.0 };
  int moveDirX { 1 };
  int moveDirY { 1 };
  int moveDirZ { 1 };
};

inline LoopMove::LoopMove(Object* _parentObj, double _minX, double _maxX, double _minY, double _maxY, double _minZ, double _maxZ, double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ) :
       CrustScript(_parentObj), minX(_minX), maxX(_maxX), minY(_minY), maxY(_maxY), minZ(_minZ), maxZ(_maxZ), speedX(_moveSpeedX), speedY(_moveSpeedY), speedZ(_moveSpeedZ) {}

inline void LoopMove::Start() {}

void LoopMove::Update(double deltaTime) {
  if(moveDirX > 0 && parentObj->GetTransform()->GetPosition()->X() >= maxX) moveDirX = -1;
  if (moveDirX < 0 && parentObj->GetTransform()->GetPosition()->X() <= minX)
    moveDirX = 1;

  if (moveDirY > 0 && parentObj->GetTransform()->GetPosition()->Y() >= maxY)
    moveDirY = -1;
  if (moveDirY < 0 && parentObj->GetTransform()->GetPosition()->Y() <= minY)
    moveDirY = 1;

  if (moveDirZ > 0 && parentObj->GetTransform()->GetPosition()->Z() >= maxZ)
    moveDirZ = -1;
  if (moveDirZ < 0 && parentObj->GetTransform()->GetPosition()->Z() <= minZ)
    moveDirZ = 1;

  parentObj->GetTransform()->Translate(moveDirX * speedX * deltaTime, moveDirY * speedY * deltaTime, moveDirZ * speedZ * deltaTime);
}

#endif /* _LOOPMOVE_HPP_ */
