#ifndef COLLADACPP_COLLADA_IMAGE_HPP_
#define COLLADACPP_COLLADA_IMAGE_HPP_

#include <string>
using namespace std;

#include "../Collada/ColladaObject.hpp"

class Image: public ColladaObject {
   public:
      void setFilename(const string filename);
      string getFilename();

   private:
      string filename_;
};

#endif /* COLLADACPP_COLLADA_IMAGE_HPP_ */
