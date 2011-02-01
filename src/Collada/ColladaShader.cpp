#include "../Collada/ColladaShader.hpp"
#include "../Collada/Image.hpp"

ColladaShader::ColladaShader() {
   setEmission(0.0, 0.0, 0.0, 1.0);
   setTransparent(0.0, 0.0, 0.0, 1.0);
   setReflectivity(0.0);
   setTransparency(0.0);
   setTextureHackId(0);
}

void ColladaShader::setEmission(const float& red, const float& green, const float& blue, const float& alpha) {
   emission_.setColor(red, green, blue, alpha);
}

void ColladaShader::setReflective(const float& red, const float& green, const float& blue, const float& alpha) {
   reflective_.setColor(red, green, blue, alpha);
}

void ColladaShader::setReflectivity(const float& value) {
   reflectivity_ = value;
}

void ColladaShader::setTransparent(const float& red, const float& green, const float& blue, const float& alpha) {
   transparent_.setColor(red, green, blue, alpha);
}

void ColladaShader::setTransparency(const float& value) {
   transparency_ = value;
}

void ColladaShader::setIndexOfRefraction(const float& value) {
   index_of_refraction_ = value;
}

/**
 * This sets an overiding texture Image. It will just override the diffuse channel if it exists.
 * This should really work with otherchannels other than diffuse.
 */
void ColladaShader::setTextureHack(ImagePtr image) {
   textureHack_ = image;
}

ImagePtr ColladaShader::getTextureHack() {
   return textureHack_;
}

void ColladaShader::setTexCoordHack(string texCoord) {
   texCoordHack_ = texCoord;
}

int ColladaShader::getTextureHackId() {
   return textureHackId_;
}

void ColladaShader::setTextureHackId(const int& textureHackId) {
   textureHackId_ = textureHackId;
}
