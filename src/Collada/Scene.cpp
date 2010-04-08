#include "../Collada/Scene.hpp"

void Scene::addVisualScene(VisualScenePtr visualScene) {
   visualScenes_.push_back(visualScene);
}

VisualSceneIterator Scene::getFirstVisualScene() {
   return visualScenes_.begin();
}

VisualSceneIterator Scene::getEndVisualScene() {
   return visualScenes_.end();
}
