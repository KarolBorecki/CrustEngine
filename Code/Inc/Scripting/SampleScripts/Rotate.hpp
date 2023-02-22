#ifndef _ROTATE_HPP_
#define _ROTATE_HPP_

#include <math.h>

#include <Scripting/CrustScript.hpp>

class Rotate : public CrustScript {
public:
  Rotate(Object* _parentObj);
  ~Rotate() override {}

  void Start() override;
  void Update(double deltaTime) override;
private:
  Matrix* rotMatX { nullptr };
  Matrix* rotMatZ { nullptr };
};

inline Rotate::Rotate(Object* _parentObj) : CrustScript(_parentObj) {}

inline void Rotate::Start() {
  rotMatX = new Matrix(4, 4);
  rotMatZ = new Matrix(4, 4);

  rotMatX->ResetMatrix(0.0);
  rotMatZ->ResetMatrix(0.0);
}

void Rotate::Update(double deltaTime) {
  parentObj->Rotate(1 * 1 * deltaTime, 0 * 2 * deltaTime, 1 * 3 * deltaTime); // TODO
}

#endif /* _ROTATE_HPP_ */
