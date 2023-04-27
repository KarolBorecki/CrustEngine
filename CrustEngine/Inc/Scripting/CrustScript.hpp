#ifndef _CRUSTSCRIPT_HPP_
#define _CRUSTSCRIPT_HPP_

class Object;
class Transform;

class CrustScript
{
public:
  CrustScript() {}
  virtual ~CrustScript(){};

  /**
   * @brief Function called when script is being attached to the object.
   */
  virtual void Start();

  /**
   * @brief Function called once per frame.
   *
   * @param deltaTime Time that passed since last frame - it represents how much seconds does the last frame took to render.
   */
  virtual void Update(double deltaTime);

  /**
   * @brief Function that should only be called once. This is only called from Object::AttachScript and should not be called by the user.
   *
   * @param _parentObj Object that holds this script.
   *
   * @sa Object.hpp
   */
  void AttachTo(Object &_parentObj);

  /**
   * @brief Get the object of an parent class that holds this sctipt. It is highly useful to perform any action on parent object.
   *
   * @return Object& Parent object reference.
   */
  Object &GetObject();

private:
  Object *p_parentObj{nullptr}; //!< Object that holds this script and on which this script's functionallity will be performed.

  bool _isAttached{false}; //!< Flag that represents if given script was already attached to it's parent. If equal to yes method #AttachTo will do no action.
};

inline void CrustScript::Start() {}

inline void CrustScript::Update(double deltaTime) {}

inline void CrustScript::AttachTo(Object &_parentObj)
{
  if (_isAttached)
    return;
  p_parentObj = &_parentObj;
  _isAttached = (p_parentObj != nullptr);
}

inline Object &CrustScript::GetObject() { return *p_parentObj; }

#endif /* _CRUSTSCRIPT_HPP_ */
