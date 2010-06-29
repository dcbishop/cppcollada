#include "../Collada/ColladaNode.hpp"

class TestRenderable : public ColladaNode {
   public:
      COLLADA_RENDER_FUNCTION
};

typedef shared_ptr<TestRenderable> TestRenderablePtr;
