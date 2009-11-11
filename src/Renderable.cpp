#include "Renderable.hpp"
ColladaRenderer* Renderable::renderer_ = 0;

ColladaRenderer* Renderable::getRenderer() {
   return renderer_;
}

// TODO: Don't have this here... Some global setting...
void Renderable::setRenderer(ColladaRenderer* renderer) {
   renderer_ = renderer;
}
