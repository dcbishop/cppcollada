#include "Scene.hpp"

void Scene::setVisualScene(shared_ptr<VisualScene> visualScene) {
   visualScene_ = visualScene;
}

shared_ptr<VisualScene> Scene::getVisualScene() {
   return visualScene_;
}
