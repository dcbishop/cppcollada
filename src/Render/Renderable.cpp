#include "../Render/Renderable.hpp"
ColladaRenderer* Renderable::renderer_ = 0;

ColladaRenderer* Renderable::getRenderer() {
   return renderer_;
}

#warning ['TODO']: This is a dodgy hack... need one that can be changed at runtime...
void Renderable::setRenderer(ColladaRenderer* renderer) {
   renderer_ = renderer;
}
