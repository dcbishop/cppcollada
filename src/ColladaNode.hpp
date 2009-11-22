#ifndef COLLADACPP_NODE_HPP_
#define COLLADACPP_NODE_HPP_


#include <vector>
using namespace std;

#include "SmartPointers.hpp"

#include "Renderable.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "RotationGL.hpp"
#include "ColladaObject.hpp"
#include "Scale.hpp"

#warning ['TODO']: ColladaNodes can have other transition types...

typedef vector<shared_ptr<ColladaObject>> InstanceVector;
typedef InstanceVector::iterator InstanceIterator;

class ColladaNode : public ColladaObject, public Position, public RotationGL, public Scale {
   public:
      InstanceIterator getFirstInstance();
      InstanceIterator getEndInstance();
      
      void addInstance(shared_ptr<ColladaObject> instance);
      COLLADA_RENDER_FUNCTION
      
   private:
      string layer_;
      vector<shared_ptr<ColladaObject>> instances_;
};

#endif /* COLLADACPP_NODE_HPP_ */
