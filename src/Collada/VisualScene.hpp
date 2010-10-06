#ifndef COLLADACPP_VISUALSCENE_HPP_
#define COLLADACPP_VISUALSCENE_HPP_

/**
 * A COLLADA visual_scene.
 */
#include <vector>
using namespace std;

#include "../GameData/SmartPointers.hpp"
#include "../Collada/ColladaObject.hpp"


class ColladaNode;

typedef vector< shared_ptr<ColladaNode> > ColladaNodeVector;
typedef ColladaNodeVector::iterator ColladaNodeIterator;

#warning ['TODO']: Keep a map of the nodes/ids...
class VisualScene : public ColladaObject {
   public:
      void addColladaNode(shared_ptr<ColladaNode> node);
      ColladaNodeIterator getFirstColladaNode();
      ColladaNodeIterator getEndColladaNode();
      COLLADA_RENDER_FUNCTION

   private:
      ColladaNodeVector nodes_;
};
typedef shared_ptr<VisualScene> VisualScenePtr;

#endif /* COLLADACPP_VISUALSCENE_HPP_ */
