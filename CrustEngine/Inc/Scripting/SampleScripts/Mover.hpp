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

 #define LOG_MOVER // Uncomment to log debug data
void Mover::Update(double deltaTime)
{
  if (InputHandler::IsPressed(Key::KEY_D))
  {
#ifdef LOG_MOVER
    Logger::Log("Moving +X : (%f, %f, %f)", GetObject().GetTransform().GetPosition().X(), GetObject().GetTransform().GetPosition().Y(), GetObject().GetTransform().GetPosition().Z());
#endif
    GetObject().GetTransform().Translate(speedX * deltaTime, 0, 0);
  }
  if (InputHandler::IsPressed(Key::KEY_A))
  {
#ifdef LOG_MOVER
    Logger::Log("Moving -X : (%f, %f, %f)", GetObject().GetTransform().GetPosition().X(), GetObject().GetTransform().GetPosition().Y(), GetObject().GetTransform().GetPosition().Z());
#endif
    GetObject().GetTransform().Translate(-speedX * deltaTime, 0, 0);
  }
  if (InputHandler::IsPressed(Key::KEY_W))
  {
#ifdef LOG_MOVER
    Logger::Log("Moving +Z : (%f, %f, %f)", GetObject().GetTransform().GetPosition().X(), GetObject().GetTransform().GetPosition().Y(), GetObject().GetTransform().GetPosition().Z());
#endif
    GetObject().GetTransform().Translate(0, 0, speedY * deltaTime);
  }
  if (InputHandler::IsPressed(Key::KEY_S))
  {
#ifdef LOG_MOVER
    Logger::Log("Moving -Z : (%f, %f, %f)", GetObject().GetTransform().GetPosition().X(), GetObject().GetTransform().GetPosition().Y(), GetObject().GetTransform().GetPosition().Z());
#endif
    GetObject().GetTransform().Translate(0, 0, -speedY * deltaTime);
  }

  if (InputHandler::IsPressed(Key::KEY_Q))
  {
#ifdef LOG_MOVER
    Logger::Log("Moving +Y : (%f, %f, %f)", GetObject().GetTransform().GetPosition().X(), GetObject().GetTransform().GetPosition().Y(), GetObject().GetTransform().GetPosition().Z());
#endif
    GetObject().GetTransform().Translate(0, speedY * deltaTime, 0);
    // GetObject().GetTransform().RotateEuler(0, 0, 0.001f * deltaTime);
  }

  if (InputHandler::IsPressed(Key::KEY_E))
  {
#ifdef LOG_MOVER
    Logger::Log("Moving -Y : (%f, %f, %f)", GetObject().GetTransform().GetPosition().X(), GetObject().GetTransform().GetPosition().Y(), GetObject().GetTransform().GetPosition().Z());
#endif
    GetObject().GetTransform().Translate(0, -speedY * deltaTime, 0);
    // GetObject().GetTransform().RotateEuler(0, 0, -0.001f * deltaTime);
  }
}

#endif /* _MOVER_HPP_ */
