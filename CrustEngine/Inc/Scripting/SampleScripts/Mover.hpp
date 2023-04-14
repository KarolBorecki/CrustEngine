#ifndef _MOVER_HPP_
#define _MOVER_HPP_

#include <Scripting/CrustScript.hpp>

#include <Logging/Logger.hpp>
#include <Input/InputHandler.hpp>

class Mover : public CrustScript {
public:
  Mover(double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ);
  ~Mover() override {}

  void Start() override;
  void Update(double deltaTime) override;
private:
  double speedX { 0.0 };
  double speedY { 0.0 };
  double speedZ { 0.0 };
};

inline Mover::LoopMove(double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ) :
       speedX(_moveSpeedX), speedY(_moveSpeedY), speedZ(_moveSpeedZ) {}

inline void Mover::Start() {}

void Mover::Update(double deltaTime) {
  if(InputHandler::GetEvent().keyCode == KeyCode.KEY_A) {
    Logger::Log("DOSTAŁEM AAAAAAAAAAAAAAAAAAAAAAAAA");
  }
}

#endif /* _MOVER_HPP_ */
