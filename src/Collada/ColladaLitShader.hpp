#ifndef COLLADACPP_COLLADALITSHADER_HPP_
#define COLLADACPP_COLLADALITSHADER_HPP_

#include "../GameData/ColorRGBA.hpp"
#include "../Collada/ColladaShader.hpp"
#include "../Collada/Image.hpp"

class ColladaLitShader : public ColladaShader {
   public:
      COLLADA_RENDER_FUNCTION
      ColladaLitShader();
      void setAmbient(const float& red, const float& green, const float& blue, const float& alpha);
      void setDiffuse(const float& red, const float& green, const float& blue, const float& alpha);
      
      const ColorRGBA &getAmbient() const { return ambient_; }
      const ColorRGBA &getDiffuse() const { return diffuse_; }

   private:
      ColorRGBA ambient_;
      ColorRGBA diffuse_;
};
typedef shared_ptr<ColladaLitShader> ColladaLitShaderPtr;

#endif /* COLLADACPP_COLLADALITSHADER_HPP_ */
