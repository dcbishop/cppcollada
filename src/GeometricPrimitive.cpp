#include "GeometricPrimitive.hpp"

#include "console.h"

/**
 * Gets the vertex number from the list of primitives.
 */
int GeometricPrimitive::getVertexNum(const int& num) const {
   int vertexOffset = vertex_->getOffset();
   int vertexNum = vertexOffset + (num * (vertexOffset+1));
   return primitives_->at(vertexNum);
}

PrimIterator GeometricPrimitive::getFirstPrimitive() const {
   return primitives_->begin();
}

PrimIterator GeometricPrimitive::getEndPrimitive() const {
   return primitives_->end();
}

float GeometricPrimitive::getX(const int& num) const {
   return vertex_->getX(num);
}

float GeometricPrimitive::getY(const int& num) const {
   return vertex_->getY(num);
}

float GeometricPrimitive::getZ(const int& num) const {
   return vertex_->getZ(num);
}
