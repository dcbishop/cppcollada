#include "Position.hpp"

//#include "console.h"

#include <math.h>

Position::Position() {
   setX(0.0f);
   setY(0.0f);
   setZ(0.0f);
}

/**
 * Returns the Position.
 * @return Refrence to the Position.
 */
Position Position::getPosition() {
   return *this;
}

/**
 * Sets the Position.
 * @param
 */
void Position::setPosition(Position& position) {
   setXYZ(position.getX(), position.getY(), position.getZ());
}

/**
 * Sets the objects X, Y, Z coordinates .
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param z Z coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 */
void Position::setXYZ(const float &x, const float &y, const float &z) {
   Position::setX(x);
   Position::setY(y);
   Position::setZ(z);
}

/**
 * Returns the current X coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The X coordinate.
 */
const float Position::getX() const {
   return x_;
}

/**
 * Returns the current Y coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The Y coordinate.
 */
const float Position::getY() const {
   return y_;
}

/**
 * Returns the current Z coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The Z coordinate.
 */
const float Position::getZ() const {
   return z_;
}

/**
 * Sets the current X coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @param x the X coordinate
 */
void Position::setX(const float& x) {
   x_ = x;
}

/**
 * Sets the current Y coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @param x the Y coordinate
 */
void Position::setY(const float& y) {
   y_ = y;
}

/**
 * Sets the current Z coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @param x the Z coordinate
 */
void Position::setZ(const float& z) {
   z_ = z;
}

/**
 * Gets the distance from this Position to another.
 * @param position The other position
 * @return The distance to the other position.
 */
const float Position::getDistanceTo(Position& position) {
   float dx = getX() - position.getX();
   float dy = getY() - position.getY();
   float dz = getZ() - position.getZ();

   return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}

/**
 * Gets the distance from this Position to another, ignoring height.
 * @param position The other position
 * @return The distance to the other position.
 */
const float Position::getDistanceTo2D(Position& position) {
   float diff_x = position.getX() - getX();
   float diff_z = position.getZ() - getZ();
   return sqrt(pow(diff_x, 2) + pow(diff_z, 2));
}

/**
 * Gets the angle around Y axis towards another Position.
 * @param position The other position.
 * @return The angle.
 */
const float Position::getDirectionTo2D(Position& position) {
   float diff_x = position.getX() - getX();
   float diff_z = position.getZ() - getZ();
   return atan2(diff_z, diff_x);
}
