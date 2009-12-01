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
