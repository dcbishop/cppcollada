#ifndef COLLADACPP_SCALE_HPP
#define COLLADACPP_SCALE_HPP

/**
 * A class for rotation information.
 */
class Scale {
	public:
		virtual void setScaleXYZ(const float sx, const float sy, const float sz);
		virtual const float getScaleX();
		virtual const float getScaleY();
		virtual const float getScaleZ();

	private:
		float sx_;
		float sy_;
		float sz_;
};

#endif /* COLLADACPP_SCALE_HPP */
