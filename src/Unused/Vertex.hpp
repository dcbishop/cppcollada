#ifndef COLLADACPP_VERTEX_HPP_
#define COLLADACPP_VERTEX_HPP_

class Vertex {
	public:
		float& getX();
		float& getY();
		float& getZ();
		void setX(const float &x);
		void setY(const float &x);
		void setZ(const float &x);

	private:
		float x_;
		float y_;
		float z_;
};

#endif /* COLLADACPP_VERTEX_HPP_ */
