#ifndef COLLADACPP_ROTATIONSTUPID_HPP_
#define COLLADACPP_ROTATIONSTUPID_HPP_

#include "Rotation.hpp"

/**
 * A class for rotation information.
 */
class RotationStupid : public Rotation {
	public:
		RotationStupid();

		virtual void setRotation(RotationStupid& rotation);
		virtual void setRotX(const float rx);
		virtual void setRotY(const float ry);
		virtual void setRotZ(const float rz);
		virtual void setRotAngle(const float z);
		virtual const float getRotX();
		virtual const float getRotY();
		virtual const float getRotZ();
		virtual const float getRotAngle();

	private:
		virtual void wrapRot_();
		float rx_;
		float ry_;
		float rz_;
		float angle_;
};

#endif /* COLLADACPP_ROTATIONSTUPID_HPP_ */
