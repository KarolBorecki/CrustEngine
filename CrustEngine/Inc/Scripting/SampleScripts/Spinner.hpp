#ifndef _SPINNER_HPP_
#define _SPINNER_HPP_

#include <Scripting/CrustScript.hpp>
#include <Rendering/Objects/Object.hpp>

#include <Input/InputHandler.hpp>
#include <Input/InputEvent.hpp>
#include <Math/Vector3.hpp>

class Spinner : public CrustScript
{
public:
    Spinner(float xSpeed, float ySpeed, float zSpeed);
    ~Spinner() override{};

    void Start() override;
    void Update(float deltaTime) override;

private:
    float _xSpeed{0.0f};
    float _ySpeed{0.0f};
    float _zSpeed{0.0f};
};

inline Spinner::Spinner(float xSpeed, float ySpeed, float zSpeed) : _xSpeed(xSpeed), _ySpeed(ySpeed), _zSpeed(zSpeed) {}

inline void Spinner::Start() {}

void Spinner::Update(float deltaTime)
{
    GetObject().GetTransform().RotateEuler(0, 0, _zSpeed * deltaTime);
    GetObject().GetTransform().RotateEuler(0, _ySpeed * deltaTime, 0);
    GetObject().GetTransform().RotateEuler(_xSpeed * deltaTime, 0, 0);
    
}

#endif /* _SPINNER_HPP_ */