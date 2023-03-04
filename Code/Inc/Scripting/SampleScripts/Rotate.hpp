#ifndef _ROTATE_HPP_
#define _ROTATE_HPP_

#include <math.h>

#include <Scripting/CrustScript.hpp>

#include <Rendering/Objects/Object.hpp>

class Rotate : public CrustScript {
public:
  using CrustScript::CrustScript;

  void Start() override;
  void Update(double deltaTime) override;
private:
  Matrix<double> *rotMatX{nullptr};
  Matrix<double>* rotMatZ { nullptr };
};

inline void Rotate::Start() {
  rotMatX = new Matrix<double>(4, 4);
  rotMatZ = new Matrix<double>(4, 4);

  rotMatX->ResetMatrix(0.0);
  rotMatZ->ResetMatrix(0.0);
}

void Rotate::Update(double deltaTime) {
  parentObj->GetTransform()->Rotate(1 * 1 * deltaTime, 0 * 2 * deltaTime, 1 * 3 * deltaTime); // TODO
}

#endif /* _ROTATE_HPP_ */
