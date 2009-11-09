#include "RotationStupid.hpp"

//#include <stdlib.h>
#include <math.h> // For fmodf

//#include "console.h"

RotationStupid::RotationStupid() {
	setRotX(0.0);
	setRotY(1.0);
	setRotZ(0.0);
	setRotAngle(0.0f);
}

/**
 * Sets the Rotation from another Rotation.
 * @param rotation The rotation to use.
 */
void RotationStupid::setRotation(RotationStupid& rotation) {
	setRotX(rotation.getRotX());
	setRotY(rotation.getRotY());
	setRotZ(rotation.getRotZ());
	setRotAngle(rotation.getRotAngle());
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param rx the X rotation in OpenGL coordinates.
 */
void RotationStupid::setRotX(const float rx) {
	rx_ = rx;
	RotationStupid::wrapRot_();
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param ry the Y rotation in OpenGL coordinates.
 */
void RotationStupid::setRotY(const float ry) {
	ry_ = ry;
	RotationStupid::wrapRot_();
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param rz the Z rotation in OpenGL coordinates.
 */
void RotationStupid::setRotZ(const float rz) {
	rz_ = rz;
	RotationStupid::wrapRot_();
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param angle the angle of rotation in OpenGL coordinates.
 */
void RotationStupid::setRotAngle(const float angle) {
	angle_ = angle;
	RotationStupid::wrapRot_();
}

/**
 * For fixing any changes to the rotation data.
 */
void RotationStupid::wrapRot_() {
	if(angle_ > 360.0f || angle_ < -360.0f) {
		angle_ = fmodf(angle_, 360.0f);
	}
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the X rotation in OpenGL coordinates.
 */
const float RotationStupid::getRotX() {
	return rx_;
}
/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the Y rotation in OpenGL coordinates.
 */
const float RotationStupid::getRotY() {
	return ry_;
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the Z rotation in OpenGL coordinates.
 */
const float RotationStupid::getRotZ() {
	return rz_;
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the angle of rotation in OpenGL coordinates.
 */
const float RotationStupid::getRotAngle() {
	return angle_;
}
