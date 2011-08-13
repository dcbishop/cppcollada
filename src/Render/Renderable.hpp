#ifndef COLLADACPP_RENDERABLE_HPP_
#define COLLADACPP_RENDERABLE_HPP_

#include "../GameData/Globals.hpp"

#define COLLADA_RENDER_FUNCTION virtual inline void render() { g.getRenderer()->render(this); }
#define COLLADA_PURE_RENDER_FUNCTION  virtual inline void render() = 0;

class Renderer;
#include "../Render/Renderer.hpp"

class Renderable {
   public:
      COLLADA_PURE_RENDER_FUNCTION

   private:
};


#endif /* COLLADACPP_RENDERABLE_HPP_ */
