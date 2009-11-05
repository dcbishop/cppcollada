#ifndef COLLADACPP_NAME_HPP_
#define COLLADACPP_NAME_HPP_

#include <string>
using namespace std;

/**
 * A Named object.
 */
class Name {
   public:
      string getName();
      void setName(string name);

   private:
      string name_;
};

#endif /* COLLADACPP_NAME_HPP_ */
