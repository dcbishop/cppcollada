#include "../Collada/Phong.hpp"
#include "../Collada/Image.hpp"

Phong::Phong() {
   setDiffuse(0.5, 0.5, 0.5, 1.0);
   setAmbient(0.0, 0.0, 0.0, 1.0);
   setEmission(0.0, 0.0, 0.0, 1.0);
   setSpecular(1.0, 1.0, 1.0, 1.0);
   setTransparent(0.0, 0.0, 0.0, 1.0);
   setReflectivity(0.0);
   setShininess(0.0);
   setTransparency(0.0);
   setTextureHackId(0);
}

void Phong::setEmission(const float& red, const float& green, const float& blue, const float& alpha) {
   emission_.setColor(red, green, blue, alpha);
}

void Phong::setAmbient(const float& red, const float& green, const float& blue, const float& alpha) {
   ambient_.setColor(red, green, blue, alpha);
}

void Phong::setDiffuse(const float& red, const float& green, const float& blue, const float& alpha) {
   diffuse_.setColor(red, green, blue, alpha);
}

void Phong::setSpecular(const float& red, const float& green, const float& blue, const float& alpha) {
   specular_.setColor(red, green, blue, alpha);
}

void Phong::setShininess(const float& value) {
   shininess_ = value;
}

void Phong::setReflective(const float& red, const float& green, const float& blue, const float& alpha) {
   reflective_.setColor(red, green, blue, alpha);
}

void Phong::setReflectivity(const float& value) {
   reflectivity_ = value;
}

void Phong::setTransparent(const float& red, const float& green, const float& blue, const float& alpha) {
   transparent_.setColor(red, green, blue, alpha);
}

void Phong::setTransparency(const float& value) {
   transparency_ = value;
}

/**
 * This sets an overiding texture Image. It will just override the diffuse channel if it exists.
 * This should really work with otherchannels other than diffuse.
 */
void Phong::setTextureHack(ImagePtr image) {
   textureHack_ = image;
}

ImagePtr Phong::getTextureHack() {
   return textureHack_;
}

void Phong::setTexCoordHack(string texCoord) {
   texCoordHack_ = texCoord;
}

int Phong::getTextureHackId() {
   return textureHackId_;
}

inline void Phong::setTextureHackId(const int& textureHackId) {
   textureHackId_ = textureHackId;
}
