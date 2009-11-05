/**
 * A COLLADA visual_scene.
 */
#include "ColladaObject.hpp"

#include <vector>

class Node;

#warning ['TODO']: Keep a map of the nodes...
class VisualScene : public ColladaObject {
   public:
      void addNode(Node* node);

   private:
      vector<Node*> nodes_;
};
