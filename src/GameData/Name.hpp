#ifndef COLLADACPP_NAME_HPP_
#define COLLADACPP_NAME_HPP_

#include <string>
using namespace std;

/**
 * A Named object.
 */
class Name {
   public:
      const string& getName() const;
      void setName(const string& name);

   private:
      string name_;
};

#endif /* COLLADACPP_NAME_HPP_ */
