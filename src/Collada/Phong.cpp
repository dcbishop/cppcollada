#include "../Collada/Phong.hpp"
#include "../Collada/Image.hpp"

Phong::Phong() {
   setEmission(0.0, 0.0, 0.0, 1.0);
   setAmbient(0.0, 0.0, 0.0, 1.0);
   setDiffuse(0.5, 0.5, 0.5, 1.0);
   setReflective(0.0, 0.0, 0.0, 1.0);
   setReflectivity(0.0);
   setTransparent(0.0, 0.0, 0.0, 1.0);
   setSpecular(1.0, 1.0, 1.0, 1.0);


   setShininess(0.0);
   setTransparency(0.0);
   setTextureHackId(0);
}


void Phong::setSpecular(const float& red, const float& green, const float& blue, const float& alpha) {
   specular_.setColor(red, green, blue, alpha);
}

void Phong::setShininess(const float& value) {
   shininess_ = value;
}
