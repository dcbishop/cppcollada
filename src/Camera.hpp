#ifndef COLLADACPP_CAMERA_HPP_
#define COLLADACPP_CAMERA_HPP_

//#include "Object.hpp"
//#include "DynamicFloat.hpp"

const float PI = 3.14152f;

const float Y_MIN = 0.01f;
const float Y_MAX = 75.0f-Y_MIN;

const float ZOOM_STEP = 0.5f;
const float ZOOM_MIN = 0.5f;
const float ZOOM_MAX = 20.0f;
const float ZOOM_SPEED = 3.0f;
const float ZOOM_THRESHOLD = 0.001f;

#include "SmartPointers.hpp"
#include "Position.hpp"

/**
 * A camera.
 */
#warning ['TODO']: Quicky dummy class, orbital camera only. Set from node?
class Camera : public Position, public Renderable /*public Object*/ {
	public:
		Camera();
		~Camera();
		void update(const int time);
		void setTarget(weak_ptr<Position> object);
		shared_ptr<Position> getTarget();
		float getFov();
		void setZoom(const float zoom);
		float getZoom();
		float getZoomTarget();

		void setRotX(const float rx);
		void setRotY(const float ry);
		float getRotX() {return rx_;}
		float getRotY() {return ry_;}

		void setFov(const float fov);
		const float getX();
		const float getY();
		const float getZ();
		COLLADA_RENDER_FUNCTION

	private:
		weak_ptr<Position> target_;
		//DynamicFloat fov_;
		//DynamicFloat zoom_;
		float fov_;
		float zoom_;
		float rx_;
		float ry_;
};

#endif /* TX_CAMERA_HPP */
