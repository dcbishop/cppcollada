#ifndef COLLADACPP_SMARTPOINTERS_HPP_
#define COLLADACPP_SMARTPOINTERS_HPP_

/**
 * This is for getting a shared_ptr
 */

// -std=c++0x
#ifdef __GXX_EXPERIMENTAL_CXX0X__
   #include <memory>
   #include <unordered_map>
   using namespace std;
#endif

#ifdef _TR1PTR
   #include <tr1/memory>
   #include <tr1/unordered_map>
   using namespace tr1;
#endif

#ifdef _BOOSTPTR
   #include <boost/shared_ptr.hpp>
   #include <boost/weak_ptr.hpp>
   #include <boost/unordered_map.hpp>
   //using namespace boost;
   using boost::weak_ptr;
   using boost::shared_ptr;
   using boost::unordered_map;
   using boost::dynamic_pointer_cast;
   using boost::static_pointer_cast;
#endif

#endif /* COLLADACPP_SMARTPOINTERS_HPP_ */
