#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <Physics/Vector3.hpp>

/**
* @brief Represents object present on the scene.
*/
class Object {
public:
  /**
  * @brief Creates object at position 0, 0, 0.
  * @details Calls Object::Init method with all values equal to 0.0.
  */
  Object();
  /**
  * @brief Creates object at position #posX, #posY, #posZ.
  * @details Calls Object::Init method with values equal to #posX, #posY, #posZ.
  *
  * @param posX X position of the new object.
  * @param posY Y position of the new object.
  * @param posZ Z position of the new object.
  */
  Object(double posX, double posY, double posZ);

  virtual ~Object();

  /**
  * @brief Getter for #isActive field.
  *
  * @return #isActive field.
  */
  bool IsActive();

private:
  bool isActive { true }; //!< Tells is object has any effect on the scene. If is rendered or if any code can be perform on it.

  Vector3* pos; //!< Object position in 3D space.

  /**
  * @details Creates new Vector3 object with values #posX, #posY, #posZ and sets #pos field to it.
  * @param posX X position of the new object.
  * @param posY Y position of the new object.
  * @param posZ Z position of the new object.
  */
  void Init(double posX, double posY, double posZ);
};

Object::Object() { Init(0.0, 0.0, 0.0); }

Object::Object(double posX, double posY, double posZ) { Init(posX, posY, posZ); }

Object::~Object() { delete pos; }

inline bool Object::IsActive() { return isActive; }

void Object::Init(double posX, double posY, double posZ) {
  pos = new Vector3(posX, posY, posZ);
}

#endif /* _OBJECT_HPP_ */
