#include "Scene.hpp"

void Scene::setVisualScene(VisualScene* visualScene) {
   visualScene_ = visualScene;
}

VisualScene* Scene::getVisualScene() {
   return visualScene_;
}
