#include "../Collada/Sampler2D.hpp"

shared_ptr<Image> Sampler2D::getImage() {
   shared_ptr<Image> image = dynamic_pointer_cast<Image, ColladaObject>(sourceOrImage_);
   if(image) {
      return image;
   }

   //shared_ptr<Surface> surface = dynamic_cast<shared_ptr<Surface>>
}

void Sampler2D::setImage(shared_ptr<ColladaObject> source) {
   sourceOrImage_ = source;
}
