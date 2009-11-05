#ifndef COLLADACPP_SCENE_HPP_
#define COLLADACPP_SCENE_HPP_

class VisualScene;

class Scene {
   public:
      void setVisualScene(VisualScene* scene);

   private:
      VisualScene* visualScene_;
};

#endif /* COLLADACPP_SCENE_HPP_ */
