#ifndef COLLADACPP_RENDERABLE_HPP_
#define COLLADACPP_RENDERABLE_HPP_

#define COLLADA_RENDER_FUNCTION virtual void render() { getRenderer()->render(this); }
#define COLLADA_PURE_RENDER_FUNCTION  virtual void render() = 0;

class ColladaRenderer;
#include "ColladaRenderer.hpp"

class Renderable {
   public:
      static ColladaRenderer* getRenderer();
      static void setRenderer(ColladaRenderer* renderer_);
      //virtual void render() = 0;
      COLLADA_PURE_RENDER_FUNCTION

   private:
         static ColladaRenderer* renderer_;
};


#endif /* COLLADACPP_RENDERABLE_HPP_ */
