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
   * @details Calls Object::Init method with all values equal to 0.0.
   */
  Object();

  ~Object();

  virtual std::string GetObjectTypeName();

  /**
   * @brief Getter for #isActive field.
   *
   * @return #isActive field.
   */
  bool IsActive();

  /**
   * @brief Getter for #transform handler field.
   *
   * @sa CrustScript.hpp
   */
  Transform &GetTransform();

  /**
   * @brief Getter for #scripts field.
   *
   * @sa CrustScript.hpp
   */
  std::vector<CrustScript *> GetScripts();

  /**
   * @brief Attaches given script functionality to this object.
   *
   * @param script Attached script which will be exectued specificly for this object.
   */
  void AttachScript(CrustScript &script);

  /**
   * @brief Getter for object's ID.
   *
   * @return Object's ID.
   */
  uint32_t GetID();

protected:
  bool isActive{true}; //!< Tells is object has any effect on the scene. If is rendered or if any code can be perform on it.
  Transform *transform;
  std::vector<CrustScript *> scripts; //!< Scripts attached to this object, wchich will be executed.

  uint32_t ID;                      //!< Object's ID.
  static inline uint32_t nextID{0}; //!< Next object ID. Also holds amount of objects created on engine work. Only for debug purposes.
};

inline Object::Object()
{
  transform = new Transform();
  ID = nextID++;
}

inline Object::~Object()
{
  Logger::Log("Object 1");
  delete transform;
  Logger::Log("Object 2");
}

inline std::string Object::GetObjectTypeName() { return "Object"; }

inline bool Object::IsActive() { return isActive; }

inline Transform &Object::GetTransform() { return *transform; }

inline std::vector<CrustScript *> Object::GetScripts() { return scripts; }

inline void Object::AttachScript(CrustScript &script)
{
  scripts.push_back(&script);
  script.AttachTo(*this);
}

inline uint32_t Object::GetID() { return ID; }

#endif /* _OBJECT_HPP_ */
