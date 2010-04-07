#ifndef COLLADACPP_PHONG_HPP_
#define COLLADACPP_PHONG_HPP_

#include "../GameData/ColorRGBA.hpp"
#include "../Collada/Effect.hpp"
#include "../Collada/Image.hpp"

class Phong : public Effect {
   public:
      COLLADA_RENDER_FUNCTION
      Phong();
      void setEmission(const float& red, const float& green, const float& blue, const float& alpha);
      void setAmbient(const float& red, const float& green, const float& blue, const float& alpha);
      void setDiffuse(const float& red, const float& green, const float& blue, const float& alpha);
      void setSpecular(const float& red, const float& green, const float& blue, const float& alpha);
      void setShininess(const float& value);
      void setReflective(const float& red, const float& green, const float& blue, const float& alpha);
      void setReflectivity(const float& value);
      void setTransparent(const float& red, const float& green, const float& blue, const float& alpha);
      void setTransparency(const float& value);
      
      const ColorRGBA &getEmission() const { return emission_; }
      const ColorRGBA &getAmbient() const { return ambient_; }
      const ColorRGBA &getDiffuse() const { return diffuse_; }
      const ColorRGBA &getSpecular() const { return specular_; }
      const float &getShininess() const { return shininess_; }
      const ColorRGBA &getReflective() const { return reflective_; }
      const float &getReflectivity() const { return reflectivity_; }
      const ColorRGBA &getTransparent() const { return transparent_; }
      const float &getTransparency() const { return transparency_; }

      void setTextureHack(ImagePtr image);
      void setTexCoordHack(string texCoord);
      ImagePtr getTextureHack();
      int getTextureHackId();
      void setTextureHackId(const int& textureHackId);


   private:
      ColorRGBA emission_;
      ColorRGBA ambient_;
      ColorRGBA diffuse_;
      ColorRGBA specular_;
      float shininess_;
      ColorRGBA reflective_;
      float reflectivity_;
      ColorRGBA transparent_;
      float transparency_;
      ImagePtr textureHack_; /* This is a tempory hack */
      string texCoordHack_;
      int textureHackId_; 
};
typedef shared_ptr<Phong> PhongPtr;
#endif /* COLLADACPP_PHONG_HPP_ */
