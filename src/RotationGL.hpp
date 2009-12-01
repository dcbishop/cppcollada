#ifndef COLLADACPP_ROTATIONGL_HPP_
#define COLLADACPP_ROTATIONGL_HPP_

#include "Rotation.hpp"

class RotationGL : public Rotation {
   public:
      RotationGL();
      void setRotationGL(const int& number, const float& x, const float& y, const float& z, const float& angle);
      void getRotationGL(const int& number, float &x, float &y, float &z, float &angle);
      COLLADA_RENDER_FUNCTION

   private:
      float rotations_[3][4];
};
#endif /* COLLADACPP_ROTATIONGL_HPP_ */
