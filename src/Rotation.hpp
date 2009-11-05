#ifndef COLLADACPP_ROTATION_HPP_
#define COLLADACPP_ROTATION_HPP_

/**
 * A class for rotation information.
 */
class Rotation {
	public:
		Rotation();
		virtual Rotation getRotation();
		virtual void setRotation(Rotation& rotation);
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

#endif /* COLLADACPP_ROTATION_HPP_ */
