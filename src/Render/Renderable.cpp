#include "../Render/Renderable.hpp"
Renderer* Renderable::renderer_ = 0;

Renderer* Renderable::getRenderer() {
   return renderer_;
}

#warning ['TODO']: This is a dodgy hack... need one that can be changed at runtime...
void Renderable::setRenderer(Renderer* renderer) {
   renderer_ = renderer;
}
