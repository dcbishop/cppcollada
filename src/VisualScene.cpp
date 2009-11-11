#include "VisualScene.hpp"

void VisualScene::addColladaNode(ColladaNode* node) {
   nodes_.push_back(node);
   // TODO: Keep a map of the nodes...
}

ColladaNodeIterator VisualScene::getFirstColladaNode() {
   return nodes_.begin();
}

ColladaNodeIterator VisualScene::getEndColladaNode() {
   return nodes_.end();
}
