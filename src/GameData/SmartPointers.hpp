#ifndef COLLADACPP_SMARTPOINTERS_HPP_
#define COLLADACPP_SMARTPOINTERS_HPP_

/**
 * This is for getting a shared_ptr
 */

// -std=c++0x
#ifdef __GXX_EXPERIMENTAL_CXX0X__
   #include <memory>
   using namespace std;
#endif

#ifdef _TR1PTR
   #include <tr1/memory>
   using namespace tr1;
#endif

#ifdef _BOOSTPTR
   #include <boost/shared_ptr.hpp>
   using namespace boost;
#endif

#endif /* COLLADACPP_SMARTPOINTERS_HPP_ */
