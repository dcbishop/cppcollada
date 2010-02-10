#include "Phong.hpp"

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
