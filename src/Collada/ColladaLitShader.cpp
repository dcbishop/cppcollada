#include "../Collada/ColladaLitShader.hpp"
#include "../Collada/Image.hpp"

ColladaLitShader::ColladaLitShader() {
   setDiffuse(0.5, 0.5, 0.5, 1.0);
   setAmbient(0.0, 0.0, 0.0, 1.0);
   setEmission(0.0, 0.0, 0.0, 1.0);
   setTransparent(0.0, 0.0, 0.0, 1.0);
   setReflectivity(0.0);
   setTransparency(0.0);
   setTextureHackId(0);
}

void ColladaLitShader::setAmbient(const float& red, const float& green, const float& blue, const float& alpha) {
   ambient_.setColor(red, green, blue, alpha);
}

void ColladaLitShader::setDiffuse(const float& red, const float& green, const float& blue, const float& alpha) {
   diffuse_.setColor(red, green, blue, alpha);
}
