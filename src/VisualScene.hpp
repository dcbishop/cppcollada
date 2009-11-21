#ifndef COLLADACPP_VISUALSCENE_HPP_
#define COLLADACPP_VISUALSCENE_HPP_

/**
 * A COLLADA visual_scene.
 */
#include <vector>

#include "SmartPointers.hpp"
#include "ColladaObject.hpp"


class ColladaNode;

typedef vector<shared_ptr<ColladaNode>> ColladaNodeVector;
typedef ColladaNodeVector::iterator ColladaNodeIterator;

#warning ['TODO']: Keep a map of the nodes/ids...
class VisualScene : public ColladaObject, public Renderable {
   public:
      void addColladaNode(shared_ptr<ColladaNode> node);
      ColladaNodeIterator getFirstColladaNode();
      ColladaNodeIterator getEndColladaNode();
      COLLADA_RENDER_FUNCTION

   private:
      ColladaNodeVector nodes_;
};

#endif /* COLLADACPP_VISUALSCENE_HPP_ */
