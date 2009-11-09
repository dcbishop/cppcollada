#include "RotationGL.hpp"

void RotationGL::setRotationGL(int number, float x, float y, float z, float angle) {
   rotations_[number][0] = x;
   rotations_[number][1] = y;
   rotations_[number][2] = z;
   rotations_[number][3] = angle;
}

void RotationGL::getRotationGL(int number, float &x, float &y, float &z, float &angle) {
   x = rotations_[number][0];
   y = rotations_[number][1];
   z = rotations_[number][2];
   angle = rotations_[number][3];
}
