#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <vector>

#include <Scripting/CrustScript.hpp>
#include <Rendering/Objects/Transform.hpp>

class CrustScript;

/**
 * @brief Represents object present on the scene.
 */
class Object
{
public:
  /**
   * @brief Creates object at position 0, 0, 0.
   */
  Object();

  virtual ~Object();

  /**
   * @brief Getter for #isActive field.
   *
   * @return #isActive field.
   */
  bool IsActive();

  /**
   * @brief Getter for #transform handler field. Transform represents position and rotation on the scene of the object.
   */
  Transform &GetTransform();

  /**
   * @brief Getter for #scripts field. All scripts of an objects are executed during scene rendering, if they are active.
   *
   * @sa CrustScript.hpp
   */
  std::vector<CrustScript *> GetScripts();

  /**
   * @brief Attaches given script functionality to this object.
   *
   * @param script Attached script, which will be exectued specificly for this object.
   */
  void AttachScript(CrustScript &script);

  /**
   * @brief Getter for object's ID.
   *
   * @return Object's ID.
   */
  uint32_t GetID();

protected:
  bool _isActive{true};                //!< Tells is object has any effect on the scene. If is rendered or if any code can be perform on it.
  Transform *p_transform;               //!< Represents object's orientation on the scene.
  std::vector<CrustScript *> _scripts; //!< Scripts attached to this object, wchich will be executed.

  uint32_t _id;                      //!< Object's ID.
  static inline uint32_t _NEXTID{0}; //!< Next object ID. Also holds amount of objects created on engine work. Only for debug purposes.
};

inline Object::Object()
{
  p_transform = new Transform();
  _id = _NEXTID++;
}

inline Object::~Object()
{
  delete p_transform;
}

inline bool Object::IsActive() { return _isActive; }

inline Transform &Object::GetTransform() { return *p_transform; }

inline std::vector<CrustScript *> Object::GetScripts() { return _scripts; }

inline void Object::AttachScript(CrustScript &script)
{
  _scripts.push_back(&script);
  script.AttachTo(*this);
}

inline uint32_t Object::GetID() { return _id; }

#endif /* _OBJECT_HPP_ */
