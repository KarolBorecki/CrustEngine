#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

class Object {
public:

  bool IsActive();

private:
  bool isActive { true };
};

inline bool Object::IsActive() { return isActive; }

#endif /* _OBJECT_HPP_ */
