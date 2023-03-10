#ifndef _CRUSTTESTING_HPP_
#define _CRUSTTESTING_HPP_

#include <iostream>

#define _TRUE(assertion) { if (!(assertion)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - assertion is false, but should be true"<< std::endl; }
#define _FALSE(assertion) { if (assertion) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - assertion is true, but should be false" << std::endl; }

#define _NULLPTR(assertion) { if (assertion != nullptr) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - assertion is nullptr, but should not"<< std::endl; }
#define _NOTNULLPTR(assertion) { if (assertion == nullptr) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - assertion is not a nullptr, but should be" << std::endl; }

#define _EQUALS(got, expected) { if (got != expected) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - got != expected" << std::endl; }
#define _NOTEQUALS(got, expected) { if (got == expected) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - got == expected"<< std::endl; }

#define _EQUALSDET(got, expected, delta) { if ((got - delta) > expected || (got + delta) < expected) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - got != expected"<< std::endl; }
#define _NOTEQUALSDET(got, expected, delta) { if (got - delta) <= expected && (got + delta) >= expected) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << " - got == expected"<< std::endl; }

#endif /* _CRUSTTESTING_HPP_ */
