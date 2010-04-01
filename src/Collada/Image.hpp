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
typedef shared_ptr<Image> ImagePtr;

#endif /* COLLADACPP_COLLADA_IMAGE_HPP_ */
