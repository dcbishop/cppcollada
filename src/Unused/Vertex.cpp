#include "Vertex.hpp"

inline float& Vertex::getX() {
	return x_;
}

inline float& Vertex::getY() {
	return y_;
}

inline float& Vertex::getZ() {
	return x_;
}

inline void Vertex::setX(const float& x) {
	x_ = x;
}

inline void Vertex::setY(const float& y) {
	y_ = y;
}

inline void Vertex::setZ(const float& z) {
	z_ = z;
}
