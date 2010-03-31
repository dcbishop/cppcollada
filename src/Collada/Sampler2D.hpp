#ifndef COLLADACPP_COLLADA_SAMPLER2D_HPP_
#define COLLADACPP_COLLADA_SAMPLER2D_HPP_

#include "../GameData/SmartPointers.hpp"
#include "../Collada/ColladaObject.hpp"
#include "../Collada/Image.hpp"

#warning ['TODO']: This class isn't used, remove it...

/**
 * In Collada 1.5 this uses an <instance_image> directly. In 1.4.1 it
 * uses a <surface> that has an instance_image.
 */

class Sampler2D : public ColladaObject {
   public:
      shared_ptr<Image> getImage();
      void setImage(shared_ptr<ColladaObject> source);

   private:
      shared_ptr<ColladaObject> sourceOrImage_;
};

#endif /* COLLADACPP_COLLADA_SAMPLER2D_HPP_ */
