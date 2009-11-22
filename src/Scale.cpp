#include "Scale.hpp"

void Scale::setScaleXYZ(const float sx, const float sy, const float sz) {
   sx_ = sx;
   sy_ = sy;
   sz_ = sz;
}

const float Scale::getScaleX() {
   return sx_;
}

const float Scale::getScaleY() {
   return sy_;
}

const float Scale::getScaleZ() {
   return sz_;
}
