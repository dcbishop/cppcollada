#ifndef COLLADACPP_PHONG_HPP_
#define COLLADACPP_PHONG_HPP_

#include "../GameData/ColorRGBA.hpp"
#include "../Collada/ColladaLitShader.hpp"
#include "../Collada/Image.hpp"

class Phong : public ColladaLitShader {
   public:
      COLLADA_RENDER_FUNCTION
      Phong();
      void setSpecular(const float& red, const float& green, const float& blue, const float& alpha);
      void setShininess(const float& value);
      
      const ColorRGBA &getSpecular() const { return specular_; }
      const float &getShininess() const { return shininess_; }

   private:
      ColorRGBA specular_;
      float shininess_;
};
typedef shared_ptr<Phong> PhongPtr;

#endif /* COLLADACPP_PHONG_HPP_ */
