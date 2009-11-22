#include "Camera.hpp"

#include <iostream>
using namespace std;

#include <math.h>
#include <GL/glu.h>
#include <stdlib.h>

#include "console.h"

/**
 * Constructor.
 * @param tag
 */
Camera::Camera() {
   //setTag(tag);

   //target_ = NULL;

   /*zoom_.setValue(2.5f);
   zoom_.setThreshold(ZOOM_THRESHOLD);
   zoom_.setRate(ZOOM_SPEED);*/

   zoom_ = 2.5f;

   setRotX(-90.0f);
   setRotY(45.0f);

   //fov_.setValue(45.0f);
   fov_ = 45.0f;
}

#warning ['TODO']: Use this or kill it...
Camera::~Camera() {
}

/**
 * Sets the Object that the camera tracks.
 */
void Camera::setTarget(weak_ptr<Position> object) {
   target_ = object;
}

shared_ptr<Position> Camera::getTarget() {
   return target_.lock();
}


/**
 * updates the camera's position around object
 */
void Camera::update(const int time) {
   /* http://en.wikipedia.org/wiki/Spherical_coordinates */

   //zoom_.update(time);
   //fov_.update(time);

   //Object::update(time);
}

const float Camera::getX() {
   float theta = getRotX();
   float phi = getRotY();
   return getZoom() *
      (cos(theta*(PI/180))) *
      (sin(phi*(PI/180)));
   
}

const float Camera::getY() {
   float theta = getRotX();
   float phi = getRotY();
   return getZoom() *
      (cos(phi*(PI/180)));
}

const float Camera::getZ() {
   float theta = getRotX();
   float phi = getRotY();
   return getZoom() *
      (sin(theta*(PI/180))) *
      (sin(phi*(PI/180)));
}

/**
 * Gets the current zoom value
 * @return The zoom value as it actually is, not target value the camera is moving to.
 */
float Camera::getZoom() {
   //return zoom_.getValueCurrent();
   return zoom_;
}

/**
 * @return The zoom value that the camera it moving to.
 */
float Camera::getZoomTarget() {
   return /*zoom_.getValueTarget();*/ zoom_;
}

/**
 * Gets the current field of view.
 * @return The current FOV (not the target FOV).
 */
float Camera::getFov() {
   //return fov_.getValueCurrent();
   return fov_;
}

/**
 * Sets the target field of view.
 * @param fov field of view
 */
void Camera::setFov(const float fov) {
   //fov_.setValue(fov);
   fov_ = fov;
}

/**
 * Sets the camera zoom (distance from target Object)
 * @param zoom Distance from the target in meters.
 */
void Camera::setZoom(const float zoom) {
   /* Ensure the camera zoom is sane */
   if(zoom < ZOOM_MIN) {
      zoom_ = ZOOM_MIN;
      //zoom_.setValue(ZOOM_MIN);
   } else if(zoom > ZOOM_MAX) {
      zoom_ = ZOOM_MAX;
      //zoom_.setValue(ZOOM_MAX);
   } else {
      zoom_ = zoom;
      //zoom_.setValue(zoom);
   }
}

/**
 * Sets the camera rotation around the target.
 * @param rx
 */
void Camera::setRotX(const float rx) {
   //Object::setRotX(rx);
   rx_ = rx;
}

/**
 * Sets the camera rotation above the target.
 * @param ry
 */
void Camera::setRotY(const float ry) {
   /* Stop flipping over the top  */
   if(ry < Y_MIN) {
      ry_ = Y_MIN;
      //Object::setRotY(Y_MIN);
   } else if(ry > Y_MAX) {
      ry_ = Y_MAX;
      //Object::setRotY(Y_MAX);
   } else {
      ry_ = ry;
      //Object::setRotY(ry);
   }
}
