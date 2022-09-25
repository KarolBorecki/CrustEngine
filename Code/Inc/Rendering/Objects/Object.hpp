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
  * @param pos Position of the new object.
  */
  Object(Vector3* pos);
  /**
  * @brief Creates object at position #posX, #posY, #posZ.
  * @details Calls Object::Init method with values equal to #posX, #posY, #posZ.
  *
  * @param posX X position of the new object.
  * @param posY Y position of the new object.
  * @param posZ Z position of the new object.
  */
  Object(double posX, double posY, double posZ);

  ~Object();

  /**
  * @brief Getter for #isActive field.
  *
  * @return #isActive field.
  */
  bool IsActive();

  /**
  * @brief Getter for #pos field.
  *
  * @return #pos field.
  */
  Vector3* GetPosition();

  /**
  * @brief Moves object by given values.
  *
  * @details Adds x, y and z to adequate values of #pos vector values.
  */
  void Move(double x, double y, double z);

  /**
  * @brief Getter for matrix ID.
  *
  * @return Matrix's ID.
  */
  uint32_t GetID();

private:
  bool isActive { true }; //!< Tells is object has any effect on the scene. If is rendered or if any code can be perform on it.

  Vector3* pos; //!< Object position in 3D space.

  uint32_t ID; //!< Object's ID.
  static inline uint32_t nextID { 0 }; //!< Next object ID. Also holds amount of objects created on engine work. Only for debug purposes.

  /**
  * @details Creates new Vector3 object with values #posX, #posY, #posZ and sets #pos field to it.
  * @param posX X position of the new object.
  * @param posY Y position of the new object.
  * @param posZ Z position of the new object.
  */
  void Init(double posX, double posY, double posZ);
};

Object::Object() { Init(0.0, 0.0, 0.0); }

Object::Object(Vector3* pos) { Init(pos->X(), pos->Y(), pos->Z()); }

Object::Object(double posX, double posY, double posZ) { Init(posX, posY, posZ); }

Object::~Object() {
  Logger::Log("Object destructor<%d>", GetID());
  delete pos;
}

inline bool Object::IsActive() { return isActive; }

inline Vector3* Object::GetPosition() { return pos; }

void Object::Move(double x, double y, double z) {
  Vector3::Add(pos, x, y, z);
}

inline uint32_t Object::GetID() { return ID; }

void Object::Init(double posX, double posY, double posZ) {
  ID = nextID++;
  Logger::Log("============Creating object<%d>============", GetID());
  pos = new Vector3(posX, posY, posZ);
  Logger::Log("============Object creation done<%d>============", GetID());
}

#endif /* _OBJECT_HPP_ */
