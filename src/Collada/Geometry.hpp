#ifndef COLLADACPP_GEOMETRY_HPP_
#define COLLADACPP_GEOMETRY_HPP_

#include <vector>
using namespace std;

#include "../Collada/ColladaObject.hpp"

typedef vector< shared_ptr<GeometricPrimitive> > GeoPrimVector;
typedef GeoPrimVector::iterator GeoPrimIterator;

class Geometry : public ColladaObject {
   public:
      COLLADA_RENDER_FUNCTION
      void addPrimitive(shared_ptr<GeometricPrimitive> primitive) { primitives_.push_back(primitive); }
      GeoPrimIterator getFirstPrimitive() { return primitives_.begin(); }
      GeoPrimIterator getEndPrimitive() { return primitives_.end(); }

   private:
      GeoPrimVector primitives_;
};
typedef shared_ptr<Geometry> GeometryPtr;

#endif /* COLLADACPP_GEOMETRY_HPP_ */
