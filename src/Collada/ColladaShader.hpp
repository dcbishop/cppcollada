#ifndef COLLADACPP_COLLADASHADER_HPP_
#define COLLADACPP_COLLADASHADER_HPP_

#include "../GameData/ColorRGBA.hpp"
#include "../Collada/Effect.hpp"
#include "../Collada/Image.hpp"

class ColladaShader : public Effect {
   public:
      COLLADA_RENDER_FUNCTION
      ColladaShader();
      void setEmission(const float& red, const float& green, const float& blue, const float& alpha);
      void setReflective(const float& red, const float& green, const float& blue, const float& alpha);
      void setReflectivity(const float& value);
      void setTransparent(const float& red, const float& green, const float& blue, const float& alpha);
      void setTransparency(const float& value);
      void setIndexOfRefraction(const float& value);
      
      const ColorRGBA &getEmission() const { return emission_; }
      const ColorRGBA &getReflective() const { return reflective_; }
      const float &getReflectivity() const { return reflectivity_; }
      const ColorRGBA &getTransparent() const { return transparent_; }
      const float &getTransparency() const { return transparency_; }
      const float &getIndexOfRefraction() const { return index_of_refraction_; }

      void setTextureHack(ImagePtr image);
      void setTexCoordHack(string texCoord);
      ImagePtr getTextureHack();
      int getTextureHackId();
      void setTextureHackId(const int& textureHackId);


   private:
      ColorRGBA emission_;
      ColorRGBA reflective_;
      float reflectivity_;
      ColorRGBA transparent_;
      float transparency_;
      ImagePtr textureHack_; /* This is a tempory hack */
      string texCoordHack_;
      int textureHackId_; 
      float index_of_refraction_;
};
typedef shared_ptr<ColladaShader> ColladaShaderPtr;

#endif /* COLLADACPP_COLLADASHADER_HPP_ */
