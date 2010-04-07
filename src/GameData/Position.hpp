#ifndef COLLADACPP_POSITION_HPP_
#define COLLADACPP_POSITION_HPP_

#include "../Render/Renderable.hpp"

/**
 * An abstract class for objects with x, y, z coordinates.
 */
class Position : private Renderable {
   public:
      Position();
      virtual Position getPosition();
      virtual void setPosition(Position& position);
      virtual void setXYZ(const float &x, const float &y, const float &z);
      virtual float getX() const;
      virtual float getY() const;
      virtual float getZ() const;
      virtual void setX(const float& x);
      virtual void setY(const float& y);
      virtual void setZ(const float& z);
      virtual float getDistanceTo(const Position& position);
      virtual float getDistanceTo2D(const Position& position);
      virtual float getDirectionTo2D(const Position& position);
      COLLADA_RENDER_FUNCTION

   private:
      float x_;
      float y_;
      float z_;
};

#endif /* COLLADACPP_POSITION_HPP_ */
