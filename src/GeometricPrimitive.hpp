#ifndef COLLADACPP_GEOMETRICPRIMITIVE_HPP_
#define COLLADACPP_GEOMETRICPRIMITIVE_HPP_

#include "vector"
using namespace std;

#include "Input.hpp"

class GeometricPrimitive {
   public:
      void setVertex(shared_ptr<Input> input) { vertex_ = input; }
      void setNormal(shared_ptr<Input> input) { normal_ = input; }
      void setPrimitives(shared_ptr<vector<int>> primitives) { primitives_ = primitives; }

      int getVertexNum(int num);

      int getX(int num) { return vertex_->getX(getVertexNum(num)); }
      int getY(int num) { return vertex_->getY(getVertexNum(num)); }
      int getZ(int num) { return vertex_->getZ(getVertexNum(num)); }

   private:
      shared_ptr<Input> vertex_;
      shared_ptr<Input> normal_;
      shared_ptr<vector<int>> primitives_;
};

/**
 * Gets the vertex number from the list of primitives.
 */
int GeometricPrimitive::getVertexNum(int num) {
   int vertexOffset = vertex_->getOffset();
   int vertexNum = vertexOffset + (num * vertexOffset);
   return primitives_->at(vertexNum);
}

#endif /* COLLADACPP_GEOMETRICPRIMITIVE_HPP_ */
