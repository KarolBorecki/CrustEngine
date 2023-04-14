#ifndef _MOVER_HPP_
#define _MOVER_HPP_

#include <Scripting/CrustScript.hpp>

#include <Logging/Logger.hpp>
#include <Input/InputHandler.hpp>

#include <Rendering/Objects/Object.hpp>

class Mover : public CrustScript
{
public:
  Mover(double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ);
  ~Mover() override {}

  void Start() override;
  void Update(double deltaTime) override;

private:
  double speedX{0.0};
  double speedY{0.0};
  double speedZ{0.0};
};

inline Mover::Mover(double _moveSpeedX, double _moveSpeedY, double _moveSpeedZ) : speedX(_moveSpeedX), speedY(_moveSpeedY), speedZ(_moveSpeedZ) {}

inline void Mover::Start() {}

void Mover::Update(double deltaTime)
{
  if (InputHandler::GetEvent().type == EVENT_KEY_DOWN)
  {
    if (InputHandler::GetEvent().keyCode == KEY_0)
    {
      GetObject().GetTransform().Translate(speedX * deltaTime, 0, 0);
    } else if (InputHandler::GetEvent().keyCode == KEY_1)
    {
      GetObject().GetTransform().Translate(-speedX * deltaTime, 0, 0);
    }else if (InputHandler::GetEvent().keyCode == KEY_3)
    {
      GetObject().GetTransform().Translate(0, speedY * deltaTime, 0);
    }else if (InputHandler::GetEvent().keyCode == KEY_4)
    {
      GetObject().GetTransform().Translate(0, -speedY * deltaTime, 0);
    }
  }
}

#endif /* _MOVER_HPP_ */
