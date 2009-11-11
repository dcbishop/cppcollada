#ifndef COLLADACPP_SCENE_HPP_
#define COLLADACPP_SCENE_HPP_

#include "Renderable.hpp"

class VisualScene;

class Scene: public Renderable {
   public:
      void setVisualScene(VisualScene* scene);
      VisualScene* getVisualScene();
      COLLADA_RENDER_FUNCTION

   private:
      VisualScene* visualScene_;
};

#endif /* COLLADACPP_SCENE_HPP_ */
