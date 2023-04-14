#ifndef _CRUSTSCRIPT_HPP_
#define _CRUSTSCRIPT_HPP_

class Object;
class Transform;

class CrustScript
{
public:
  CrustScript() {}
  virtual ~CrustScript(){};

  virtual void Start();
  virtual void Update(double deltaTime);

  void AttachTo(Object &_parentObj);

  Object& GetObject();

private:
  Object *parentObj;
};

inline void CrustScript::Start() {}

inline void CrustScript::Update(double deltaTime) {}

inline void CrustScript::AttachTo(Object &_parentObj) { parentObj = &_parentObj; }

inline Object& CrustScript::GetObject() { return *parentObj; }

#endif /* _CRUSTSCRIPT_HPP_ */
