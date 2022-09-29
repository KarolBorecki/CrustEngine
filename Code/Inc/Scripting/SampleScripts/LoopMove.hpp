#ifndef _LOOPMOVE_HPP_
#define _LOOPMOVE_HPP_

#include <Scripting/CrustScript.hpp>

class LoopMove : public CrustScript {
public:
  LoopMove(Object* _parentObj, double _maxX, double _maxY, double _maxZ, double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ);
  ~LoopMove() override {}

  void Start() override;
  void Update(double deltaTime) override;
private:
  double maxX { 0.0 };
  double maxY { 0.0 };
  double maxZ { 0.0 };
  double speedX { 0.0 };
  double speedY { 0.0 };
  double speedZ { 0.0 };
  int moveDirX { 1 };
  int moveDirY { 1 };
  int moveDirZ { 1 };
};

inline LoopMove::LoopMove(Object* _parentObj, double _maxX, double _maxY, double _maxZ, double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ) :
       CrustScript(_parentObj), maxX(_maxX), maxY(_maxY), maxZ(_maxZ), speedX(_moveSpeedX), speedY(_moveSpeedY), speedZ(_moveSpeedZ) {}

inline void LoopMove::Start() {}

void LoopMove::Update(double deltaTime) {
  if(moveDirX > 0 && parentObj->GetPosition()->X() >= maxX) moveDirX = -1;
  if(moveDirX < 0 && parentObj->GetPosition()->X() <= -maxX) moveDirX = 1;

  if(moveDirY > 0 && parentObj->GetPosition()->Y() >= maxY) moveDirY = -1;
  if(moveDirY < 0 && parentObj->GetPosition()->Y() <= -maxY) moveDirY = 1;

  if(moveDirZ > 0 && parentObj->GetPosition()->Z() >= maxZ) moveDirZ = -1;
  if(moveDirZ < 0 && parentObj->GetPosition()->Z() <= -maxZ) moveDirZ = 1;

  parentObj->Move(moveDirX * speedX * deltaTime, moveDirY * speedY * deltaTime, moveDirZ * speedZ * deltaTime);
}

#endif /* _LOOPMOVE_HPP_ */
