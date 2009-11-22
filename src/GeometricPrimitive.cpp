#include "GeometricPrimitive.hpp"

#include "console.h"

/**
 * Gets the vertex number from the list of primitives.
 */
int GeometricPrimitive::getVertexNum(int num) {
   int vertexOffset = vertex_->getOffset();
   int vertexNum = vertexOffset + (num * (vertexOffset+1));
   return primitives_->at(vertexNum);
}

PrimIterator GeometricPrimitive::getFirstPrimitive() {
   return primitives_->begin();
}

PrimIterator GeometricPrimitive::getEndPrimitive() {
   return primitives_->end();
}

int GeometricPrimitive::getX(int num) {
   DEBUG_H("getX(%d)", num);
   return vertex_->getX(num);
}

int GeometricPrimitive::getY(int num) {
   DEBUG_H("getY(%d)", num);
   return vertex_->getY(num);
}

int GeometricPrimitive::getZ(int num) {
   DEBUG_H("getZ(%d)", num);
   return vertex_->getZ(num);
}
