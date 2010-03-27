#include "../GameData/Scale.hpp"

void Scale::setScaleXYZ(const float sx, const float sy, const float sz) {
   sx_ = sx;
   sy_ = sy;
   sz_ = sz;
}

float Scale::getScaleX() const {
   return sx_;
}

float Scale::getScaleY() const {
   return sy_;
}

float Scale::getScaleZ() const {
   return sz_;
}
