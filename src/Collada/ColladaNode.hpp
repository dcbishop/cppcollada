#ifndef COLLADACPP_NODE_HPP_
#define COLLADACPP_NODE_HPP_


#include <vector>
using namespace std;

#include "../GameData/SmartPointers.hpp"

#include "../Render/Renderable.hpp"
#include "../GameData/Position.hpp"
#include "../GameData/Rotation.hpp"
#include "../GameData/RotationGL.hpp"
#include "../Collada/ColladaObject.hpp"
#include "../GameData/Scale.hpp"

#warning ['TODO']: ColladaNodes can have other transition types...

typedef vector<ColladaObjectPtr> InstanceVector;
typedef InstanceVector::iterator InstanceIterator;

class ColladaNode : public ColladaObject, public Position, public RotationGL, public Scale {
   public:
      InstanceIterator getFirstInstance();
      InstanceIterator getEndInstance();
      
      void addInstance(ColladaObjectPtr instance);
      COLLADA_RENDER_FUNCTION
      
   private:
      string layer_;
      InstanceVector instances_;
};
typedef shared_ptr<ColladaNode> ColladaNodePtr;

#endif /* COLLADACPP_NODE_HPP_ */
