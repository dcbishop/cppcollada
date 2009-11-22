#include "Collada.hpp"

void Collada::setScene(shared_ptr<Scene> scene) {
   scene_ = scene;
}

shared_ptr<Scene> Collada::getScene() {
   return scene_;
}
