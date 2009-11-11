#ifndef COLLADACPP_VISUALSCENE_HPP_
#define COLLADACPP_VISUALSCENE_HPP_

/**
 * A COLLADA visual_scene.
 */
#include "ColladaObject.hpp"

#include <vector>

class ColladaNode;

typedef vector<ColladaNode*> ColladaNodeVector;
typedef ColladaNodeVector::iterator ColladaNodeIterator;

#warning ['TODO']: Keep a map of the nodes/ids...
class VisualScene : public ColladaObject {
   public:
      void addColladaNode(ColladaNode* node);
      ColladaNodeIterator getFirstColladaNode();
      ColladaNodeIterator getEndColladaNode();
      COLLADA_RENDER_FUNCTION

   private:
      ColladaNodeVector nodes_;
};

#endif /* COLLADACPP_VISUALSCENE_HPP_ */
