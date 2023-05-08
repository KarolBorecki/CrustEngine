#ifndef _ROTATOR_HPP_
#define _ROTATOR_HPP_

#include <Scripting/CrustScript.hpp>
#include <Rendering/Objects/Object.hpp>

#include <Input/InputHandler.hpp>
#include <Input/InputEvent.hpp>
#include <Math/Vector3.hpp>

class Rotator : public CrustScript
{
public:
    Rotator(float speed);
    ~Rotator() override{};

    void Start() override;
    void Update(double deltaTime) override;

private:
    float _speed{0.0f};
};

inline Rotator::Rotator(float speed) : _speed(speed) {}

inline void Rotator::Start() {}

#define LOG_ROTATOR // Uncomment to log debug data

void Rotator::Update(double deltaTime)
{
    if (InputHandler::IsPressed(Key::KEY_Z))
    {
        GetObject().GetTransform().RotateEuler(0, 0, _speed * deltaTime);
#ifdef LOG_ROTATOR
        Logger::Log("Rotating +Z : %f", GetObject().GetTransform().GetEulerRotation().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_X))
    {
        GetObject().GetTransform().RotateEuler(0, 0, -_speed * deltaTime);
#ifdef LOG_ROTATOR
        Logger::Log("Rotating -Z : %f", GetObject().GetTransform().GetEulerRotation().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_C))
    {
        GetObject().GetTransform().RotateEuler(_speed * deltaTime, 0, 0);
#ifdef LOG_ROTATOR
        Logger::Log("Rotating +X : %f", GetObject().GetTransform().GetEulerRotation().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_V))
    {
        GetObject().GetTransform().RotateEuler(-_speed * deltaTime, 0, 0);
#ifdef LOG_ROTATOR
        Logger::Log("Rotating -X : %f", GetObject().GetTransform().GetEulerRotation().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_B))
    {
        GetObject().GetTransform().RotateEuler(0, _speed * deltaTime, 0);
#ifdef LOG_ROTATOR
        Logger::Log("Rotating +Y : %f", GetObject().GetTransform().GetEulerRotation().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_N))
    {
        GetObject().GetTransform().RotateEuler(0, -_speed * deltaTime, 0);
#ifdef LOG_ROTATOR
        Logger::Log("Rotating -Y : %f", GetObject().GetTransform().GetEulerRotation().Z());
#endif
    }
}

#endif /* _ROTATOR_HPP_ */