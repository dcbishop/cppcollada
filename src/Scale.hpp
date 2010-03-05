#ifndef COLLADACPP_SCALE_HPP
#define COLLADACPP_SCALE_HPP

#include "Renderable.hpp"

/**
 * A class for rotation information.
 */
class Scale: public Renderable {
   public:
      virtual void setScaleXYZ(const float sx, const float sy, const float sz);
      virtual float getScaleX() const;
      virtual float getScaleY() const;
      virtual float getScaleZ() const;
      COLLADA_RENDER_FUNCTION

   private:
      float sx_;
      float sy_;
      float sz_;
};

#endif /* COLLADACPP_SCALE_HPP */
