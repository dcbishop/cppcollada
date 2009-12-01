#include "RotationGL.hpp"

RotationGL::RotationGL() {
   setRotationGL(0, 0, 0, 0, 0);
   setRotationGL(1, 0, 0, 0, 0);
   setRotationGL(2, 0, 0, 0, 0);
}

void RotationGL::setRotationGL(const int& number, const float& x, const float& y, const float& z, const float& angle) {
   rotations_[number][0] = x;
   rotations_[number][1] = y;
   rotations_[number][2] = z;
   rotations_[number][3] = angle;
}

void RotationGL::getRotationGL(const int &number, float &x, float &y, float &z, float &angle) {
   x = rotations_[number][0];
   y = rotations_[number][1];
   z = rotations_[number][2];
   angle = rotations_[number][3];
}
