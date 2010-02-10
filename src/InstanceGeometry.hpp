#ifndef COLLADACPP_INSTANCEGEOMETRY_HPP_
#define COLLADACPP_INSTANCEGEOMETRY_HPP_

#include <map>
#include <string>
using namespace std;

#include "ColladaObject.hpp"
#include "Material.hpp"

#warning ['TODO']: Should be some kind of hashmap (unordered_map?)...
typedef map<string, shared_ptr<Material>> MaterialMap;
typedef MaterialMap::iterator MaterialMapIterator;
typedef pair<string, shared_ptr<Material>> MaterialMapPair;

class InstanceGeometry : public ColladaObject {
   public:
      COLLADA_RENDER_FUNCTION
      void setGeometry(shared_ptr<Geometry> geometry) { geometry_ = geometry; }
      shared_ptr<Geometry> getGeometry() {return geometry_;}

      void addInstanceMaterial(string symbol, shared_ptr<Material> material) {
         materials_.insert(MaterialMapPair(symbol, material));
      }

      shared_ptr<Material> getInstanceMaterial(string symbol) {
         return materials_.find(symbol)->second;
      }

   private:
      shared_ptr<Geometry> geometry_;
      MaterialMap materials_;
};

#endif /* COLLADACPP_INSTANCEGEOMETRY_HPP_ */
