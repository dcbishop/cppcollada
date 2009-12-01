#ifndef COLLADACPP_PHONG_HPP_
#define COLLADACPP_PHONG_HPP_

#include "ColorRGBA.hpp"
#include "Effect.hpp"

class Phong : public Effect {
   public:
      void setEmission(const float& red, const float& green, const float& blue, const float& alpha);
      void setAmbient(const float& red, const float& green, const float& blue, const float& alpha);
      void setDiffuse(const float& red, const float& green, const float& blue, const float& alpha);
      /*void setSpecular(const float& red, const float& green, const float& blue, const float& alpha);
      void setShininess(const float& value);
      void setReflective(const float& red, const float& green, const float& blue, const float& alpha);
      void setReflectivity(const float& value);
      void setTransparent(const float& red, const float& green, const float& blue, const float& alpha);
      void setTransparency(const float& value);*/

   private:
      ColorRGBA emission_;
      ColorRGBA ambient_;
      ColorRGBA diffuse_;
};

#endif /* COLLADACPP_PHONG_HPP_ */
