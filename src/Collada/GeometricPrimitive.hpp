#ifndef COLLADACPP_GEOMETRICPRIMITIVE_HPP_
#define COLLADACPP_GEOMETRICPRIMITIVE_HPP_

#include <vector>
using namespace std;

#include "../Collada/Input.hpp"

typedef vector<int> PrimVector;
typedef shared_ptr<PrimVector> PrimVectorPtr;
typedef PrimVector::iterator PrimIterator;

class GeometricPrimitive : public Renderable {
   public:
      GeometricPrimitive(): count_(0), inputCount_(0) {}
      void setVertex(shared_ptr<Input> input) { vertex_ = input; }
      void setNormal(shared_ptr<Input> input) { normal_ = input; }
      void setTexCoord(shared_ptr<Input> input) { texCoord_ = input; }
      void setPrimitives(shared_ptr<PrimVector> primitives) { primitives_ = primitives; }
      void setInputCount(const int& count) { inputCount_ = count; }
      int getInputCount() const { return inputCount_; }
      int getVertexCount() const { 
         if(primitives_.get() !=  NULL) {
            return primitives_->size()/getInputCount();
         }
         return 0;
      }
      
      int getVertexOffset() { return vertex_->getOffset(); }
      int getNormalOffset() { return normal_->getOffset(); }
      int getTexCoordOffset() { return texCoord_->getOffset(); }

      float getX(const int& num) const;
      float getY(const int& num) const;
      float getZ(const int& num) const;
      float getNX(const int& num) const;
      float getNY(const int& num) const;
      float getNZ(const int& num) const;
      float getS(const int& num) const;
      float getT(const int& num) const;
      
      inline void setCount(const int& count) { count_ = count; }
      int getCount() const { return count_; }
      void setMaterial(string material) { material_ = material; }
      string getMaterial() {return material_; }

      PrimIterator getFirstPrimitive() const; //should these be const?
      PrimIterator getEndPrimitive() const;
      COLLADA_RENDER_FUNCTION

   private:
      int getVertexNum_(const int& num) const;
      int getNormalNum_(const int& num) const;
      int getTexCoordNum_(const int& num) const;

      shared_ptr<Input> vertex_;
      shared_ptr<Input> normal_;
      shared_ptr<Input> texCoord_;
      PrimVectorPtr primitives_;
      int count_;
      int inputCount_;
      string material_;
};
typedef shared_ptr<GeometricPrimitive> GeometricPrimitivePtr;


#endif /* COLLADACPP_GEOMETRICPRIMITIVE_HPP_ */
