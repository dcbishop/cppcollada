#ifndef COLLADACPP_RENDERABLE_HPP_
#define COLLADACPP_RENDERABLE_HPP_

#define COLLADA_RENDER_FUNCTION virtual inline void render() { getRenderer()->render(this); }
#define COLLADA_PURE_RENDER_FUNCTION  virtual inline void render() = 0;

class Renderer;
#include "../Render/Renderer.hpp"

class Renderable {
   public:
      static Renderer* getRenderer();
      static void setRenderer(Renderer* renderer_);
      COLLADA_PURE_RENDER_FUNCTION

   private:
		static Renderer* renderer_;
};


#endif /* COLLADACPP_RENDERABLE_HPP_ */
