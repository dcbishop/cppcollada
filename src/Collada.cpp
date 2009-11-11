#include "Collada.hpp"

void Collada::setScene(Scene* scene) {
	scene_ = scene;
}

Scene* Collada::getScene() {
   return scene_;
}
