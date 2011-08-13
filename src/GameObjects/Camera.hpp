#ifndef GAMEOBJECTS_CAMERA_HPP_
#define GAMEOBJECTS_CAMERA_HPP_

//#include "Object.hpp"
//#include "DynamicFloat.hpp"

const float PI = 3.14152f;

const float Y_MIN = 0.01f;
const float Y_MAX = 175.0f-Y_MIN;

const float ZOOM_STEP = 0.5f;
const float ZOOM_MIN = 0.001f;
const float ZOOM_MAX = 20.0f;
const float ZOOM_SPEED = 3.0f;
const float ZOOM_THRESHOLD = 0.001f;

#include "../GameData/SmartPointers.hpp"
#include "../GameData/Globals.hpp"
#include "../GameObjects/GameObject.hpp"

/**
 * A camera.
 */
#warning ['TODO']: Quicky dummy class, orbital camera only. Set from node?
class Camera : public GameObject {
   public:
      Camera();
      ~Camera();
      void update(const int& time);
      void setTarget(weak_ptr<Position> object);
      shared_ptr<Position> getTarget();
      float getFov() const;
      void setFov(const float& fov);
      float getZoom() const;
      void setZoom(const float& zoom);
      float getZoomTarget() const;

      void setRotX(const float& rx);
      void setRotY(const float& ry);
      float getRotX() const {return rx_;}
      float getRotY() const {return ry_;}

      float getX() const;
      float getY() const;
      float getZ() const;

      COLLADA_RENDER_FUNCTION

   private:
      weak_ptr<Position> target_;
      float fov_;
      float zoom_;
      float rx_;
      float ry_;
};
typedef shared_ptr<Camera> CameraPtr;

#endif /* GAMEOBJECTS_CAMERA_HPP_ */
