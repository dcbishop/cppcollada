#include "../Collada/ColladaNode.hpp"

void ColladaNode::addInstance(shared_ptr<ColladaObject> instance) {
   instances_.push_back(instance);
}

InstanceIterator ColladaNode::getFirstInstance() {
   return instances_.begin();
}

InstanceIterator ColladaNode::getEndInstance() {
   return instances_.end();
}
