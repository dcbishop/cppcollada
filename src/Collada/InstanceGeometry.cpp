#include "../Collada/InstanceGeometry.hpp"

void InstanceGeometry::addInstanceMaterial(string symbol, shared_ptr<Material> material) {
   materials_.insert(MaterialMapPair(symbol, material));
}

shared_ptr<Material> InstanceGeometry::getInstanceMaterial(string symbol) {
   return materials_.find(symbol)->second;
}
