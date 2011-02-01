#include "../Collada/InstanceGeometry.hpp"

void InstanceGeometry::addInstanceMaterial(string symbol, shared_ptr<Material> material) {
   materials_.insert(MaterialMapPair(symbol, material));
}

shared_ptr<Material> InstanceGeometry::getInstanceMaterial(string symbol) {
   MaterialMap::iterator it = materials_.find(symbol);
   if(it == materials_.end()) {
      return shared_ptr<Material>();
   }
   return it->second;
}
