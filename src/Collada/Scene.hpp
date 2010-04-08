#ifndef COLLADACPP_SCENE_HPP_
#define COLLADACPP_SCENE_HPP_

#include "../GameData/SmartPointers.hpp"
#include "../Render/Renderable.hpp"
#include "../Collada/VisualScene.hpp";

#include <vector>
using namespace std;

typedef vector<VisualScenePtr> VisualSceneVector;
typedef VisualSceneVector::iterator VisualSceneIterator;

class Scene: public Renderable {
   public:
      void addVisualScene(VisualScenePtr visualScene);
      VisualSceneIterator getFirstVisualScene();
      VisualSceneIterator getEndVisualScene();
      COLLADA_RENDER_FUNCTION

   private:
      VisualSceneVector visualScenes_;
};

#endif /* COLLADACPP_SCENE_HPP_ */
