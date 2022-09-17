#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

/**
* @brief Represents object present on the scene.
*/
class Object {
public:
  /**
  * @brief Getter for #isActive field.
  *
  * @return #isActive field.
  */
  bool IsActive();

private:
  bool isActive { true }; //!< Tells is object has any effect on the scene. If is rendered or if any code can be perform on it.
};

inline bool Object::IsActive() { return isActive; }

#endif /* _OBJECT_HPP_ */
