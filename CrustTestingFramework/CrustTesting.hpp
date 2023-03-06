#ifndef _CRUSTTESTING_HPP_
#define _CRUSTTESTING_HPP_

#include <iostream>

#define _TRUE(assertion) { if (!(assertion)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }
#define _FALSE(assertion) { if (assertion) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

#endif /* _CRUSTTESTING_HPP_ */
