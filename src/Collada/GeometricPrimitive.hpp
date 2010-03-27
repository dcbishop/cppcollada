#ifndef COLLADACPP_GEOMETRICPRIMITIVE_HPP_
#define COLLADACPP_GEOMETRICPRIMITIVE_HPP_

#include <vector>
using namespace std;

#include "../Collada/Input.hpp"

typedef vector<int> PrimVector;
typedef PrimVector::iterator PrimIterator;

class GeometricPrimitive : public Renderable {
   public:
      void setVertex(shared_ptr<Input> input) { vertex_ = input; }
      void setNormal(shared_ptr<Input> input) { normal_ = input; }
      void setPrimitives(shared_ptr<PrimVector> primitives) { primitives_ = primitives; }
      void setInputCount(const int& count) { inputCount_ = count; }
      int getInputCount() const { return inputCount_; }

      int getVertexNum(const int& num) const;

      float getX(const int& num) const;
      float getY(const int& num) const;
      float getZ(const int& num) const;
      float getNX(const int& num) const;
      float getNY(const int& num) const;
      float getNZ(const int& num) const;
      
      inline void setCount(const int& count) { count_ = count; }
      int getCount() const { return count_; }
      void setMaterial(string material) { material_ = material; }
      string getMaterial() {return material_; }

      PrimIterator getFirstPrimitive() const; //should these be const?
      PrimIterator getEndPrimitive() const;
      COLLADA_RENDER_FUNCTION

   private:
      shared_ptr<Input> vertex_;
      shared_ptr<Input> normal_;
      shared_ptr<PrimVector> primitives_;
      int count_;
      int inputCount_;
      string material_;
};

#endif /* COLLADACPP_GEOMETRICPRIMITIVE_HPP_ */
