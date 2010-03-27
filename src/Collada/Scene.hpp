#ifndef COLLADACPP_SCENE_HPP_
#define COLLADACPP_SCENE_HPP_

#include "../GameData/SmartPointers.hpp"
#include "../Render/Renderable.hpp"

class VisualScene;

class Scene: public Renderable {
   public:
      void setVisualScene(shared_ptr<VisualScene> scene);
      shared_ptr<VisualScene> getVisualScene();
      COLLADA_RENDER_FUNCTION

   private:
      shared_ptr<VisualScene> visualScene_;
};

#endif /* COLLADACPP_SCENE_HPP_ */
