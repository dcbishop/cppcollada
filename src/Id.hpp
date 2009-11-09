#ifndef COLLADACPP_ID_HPP_
#define COLLADACPP_ID_HPP_

#include <string>
using namespace std;

/**
 * An object with an ID.
 */
class Id {
   public:
      const string getId();
      void setId(string id);

   private:
      string id_;
};

#endif /* COLLADACPP_ID_HPP_ */
