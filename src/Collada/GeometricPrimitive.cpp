#include "../Collada/GeometricPrimitive.hpp"

#include "../Debug/console.h"

/**
 * Gets the vertex index number from the list of primitives.
 */
int GeometricPrimitive::getVertexNum_(const int& num) const {
   int vertexNum = (getInputCount() * num) + vertex_->getOffset();
   return primitives_->at(vertexNum);
}

/**
 * Gets the normal index number from the list of primitives.
 */
int GeometricPrimitive::getNormalNum_(const int& num) const {
   int normalNum = (getInputCount() * num) + normal_->getOffset();
   return primitives_->at(normalNum);
}

/**
 * Gets the texcoord index number from the list of primitives.
 */
int GeometricPrimitive::getTexCoordNum_(const int& num) const {
   int texcoordNum = (getInputCount() * num) + texCoord_->getOffset();
   return primitives_->at(texcoordNum);
}

PrimIterator GeometricPrimitive::getFirstPrimitive() const {
   return primitives_->begin();
}

PrimIterator GeometricPrimitive::getEndPrimitive() const {
   return primitives_->end();
}

float GeometricPrimitive::getX(const int& num) const {
   return vertex_->getX(getVertexNum_(num));
}

float GeometricPrimitive::getY(const int& num) const {
   return vertex_->getY(getVertexNum_(num));
}

float GeometricPrimitive::getZ(const int& num) const {
   return vertex_->getZ(getVertexNum_(num));
}

float GeometricPrimitive::getNX(const int& num) const {
   return normal_->getX(getNormalNum_(num));
}

float GeometricPrimitive::getNY(const int& num) const {
   return normal_->getY(getNormalNum_(num));
}

float GeometricPrimitive::getNZ(const int& num) const {
   return normal_->getZ(getNormalNum_(num));
}

float GeometricPrimitive::getS(const int& num) const {
   return texCoord_->getS(getTexCoordNum_(num));
}

float GeometricPrimitive::getT(const int& num) const {
   return texCoord_->getT(getTexCoordNum_(num));
}
