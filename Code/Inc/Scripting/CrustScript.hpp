#ifndef _CRUSTSCRIPT_HPP_
#define _CRUSTSCRIPT_HPP_

#include <Rendering/Objects/Object.hpp>

class CrustScript {
public:
  CrustScript(Object* _parentObj) : parentObj(_parentObj) {}
  virtual ~CrustScript() {};

  virtual void Start();
  virtual void Update(double deltaTime);
protected:
  Object* parentObj;
};

inline void CrustScript::Start() {}

inline void CrustScript::Update(double deltaTime) {}

#endif /* _CRUSTSCRIPT_HPP_ */
