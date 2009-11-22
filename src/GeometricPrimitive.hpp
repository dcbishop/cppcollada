#ifndef COLLADACPP_GEOMETRICPRIMITIVE_HPP_
#define COLLADACPP_GEOMETRICPRIMITIVE_HPP_

#include "vector"
using namespace std;

#include "Input.hpp"

typedef vector<int> PrimVector;
typedef PrimVector::iterator PrimIterator;

class GeometricPrimitive : public Renderable {
   public:
      void setVertex(shared_ptr<Input> input) { vertex_ = input; }
      void setNormal(shared_ptr<Input> input) { normal_ = input; }
      void setPrimitives(shared_ptr<PrimVector> primitives) { primitives_ = primitives; }
      void setInputCount(int count) { inputCount_ = count; }
      int getInputCount() { return inputCount_; }

      int getVertexNum(int num);

      int getX(int num);
      int getY(int num);
      int getZ(int num);
      
      void setCount(int count) { count_ = count; }
      int getCount() { return count_; }

      PrimIterator getFirstPrimitive();
      PrimIterator getEndPrimitive();
      COLLADA_RENDER_FUNCTION

   private:
      shared_ptr<Input> vertex_;
      shared_ptr<Input> normal_;
      shared_ptr<PrimVector> primitives_;
      int count_;
      int inputCount_;
};

#endif /* COLLADACPP_GEOMETRICPRIMITIVE_HPP_ */
