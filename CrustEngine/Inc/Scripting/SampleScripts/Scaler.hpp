#ifndef _SCALER_HPP_
#define _SCALER_HPP_

#include <Scripting/CrustScript.hpp>
#include <Rendering/Objects/Object.hpp>

#include <Input/InputHandler.hpp>
#include <Input/InputEvent.hpp>
#include <Math/Vector3.hpp>

class Scaler : public CrustScript
{
public:
    Scaler(float speed);
    ~Scaler() override{};

    void Start() override;
    void Update(float deltaTime) override;

private:
    float _speed{0.0f};
};

inline Scaler::Scaler(float speed) : _speed(speed) {}

inline void Scaler::Start() {}

#define LOG_SCALER // Uncomment to log debug data

void Scaler::Update(float deltaTime)
{
    if (InputHandler::IsPressed(Key::KEY_1))
    {
        GetObject().GetTransform().Scale(0, 0, _speed * deltaTime);
#ifdef LOG_SCALER
        Logger::Log("Scaling +Z : %f", GetObject().GetTransform().GetScale().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_2))
    {
        GetObject().GetTransform().Scale(0, 0, -_speed * deltaTime);
#ifdef LOG_SCALER
        Logger::Log("Scaling -Z : %f", GetObject().GetTransform().GetScale().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_3))
    {
        GetObject().GetTransform().Scale(_speed * deltaTime, 0, 0);
#ifdef LOG_SCALER
        Logger::Log("Scaling +X : %f", GetObject().GetTransform().GetScale().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_4))
    {
        GetObject().GetTransform().Scale(-_speed * deltaTime, 0, 0);
#ifdef LOG_SCALER
        Logger::Log("Scaling -X : %f", GetObject().GetTransform().GetScale().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_5))
    {
        GetObject().GetTransform().Scale(0, _speed * deltaTime, 0);
#ifdef LOG_SCALER
        Logger::Log("Scaling +Y : %f", GetObject().GetTransform().GetScale().Z());
#endif
    }

    if (InputHandler::IsPressed(Key::KEY_6))
    {
        GetObject().GetTransform().Scale(0, -_speed * deltaTime, 0);
#ifdef LOG_SCALER
        Logger::Log("Scaling -Y : %f", GetObject().GetTransform().GetScale().Z());
#endif
    }
}

#endif /* _SCALER_HPP_ */