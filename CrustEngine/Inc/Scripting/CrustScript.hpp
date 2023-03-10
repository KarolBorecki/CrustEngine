#ifndef _CRUSTSCRIPT_HPP_
#define _CRUSTSCRIPT_HPP_

class Object;

class CrustScript {
public:
  CrustScript() {}
  virtual ~CrustScript() {};

  virtual void Start();
  virtual void Update(double deltaTime);

  void AttachTo(Object* _parentObj);
protected:
  Object* parentObj;
};

inline void CrustScript::Start() {}

inline void CrustScript::Update(double deltaTime) {}

inline void CrustScript::AttachTo(Object *_parentObj) { parentObj = _parentObj; }

#endif /* _CRUSTSCRIPT_HPP_ */
