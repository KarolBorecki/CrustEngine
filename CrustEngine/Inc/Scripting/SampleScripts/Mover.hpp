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
  if (InputHandler::IsPressed(Key::KEY_D))
  {
    Logger::Log("Moving +X");
    GetObject().GetTransform().Translate(speedX * deltaTime, 0, 0);
  }
  if (InputHandler::IsPressed(Key::KEY_A))
  {
    Logger::Log("Moving -X");
    GetObject().GetTransform().Translate(-speedX * deltaTime, 0, 0);
  }
  if (InputHandler::IsPressed(Key::KEY_W))
  {
    Logger::Log("Moving +Z");
    GetObject().GetTransform().Translate(0, 0, speedY * deltaTime);
  }
  if (InputHandler::IsPressed(Key::KEY_S))
  {
    Logger::Log("Moving -Z");
    GetObject().GetTransform().Translate(0, 0, -speedY * deltaTime);
  }

  if (InputHandler::IsPressed(Key::KEY_Q))
  {
    Logger::Log("Moving +Y");
    GetObject().GetTransform().Translate(0, speedY * deltaTime, 0);
  }

  if (InputHandler::IsPressed(Key::KEY_E))
  {
    Logger::Log("Moving -Y");
    GetObject().GetTransform().Translate(0, -speedY * deltaTime, 0);
  }
}

#endif /* _MOVER_HPP_ */
