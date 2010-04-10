#ifndef COLLADACPP_INSTANCEGEOMETRY_HPP_
#define COLLADACPP_INSTANCEGEOMETRY_HPP_

#include <string>
#include <unordered_map>
using namespace std;

#include "../Collada/ColladaObject.hpp"
#include "../Collada/Material.hpp"

typedef unordered_map<string, shared_ptr<Material>> MaterialMap;
typedef MaterialMap::iterator MaterialMapIterator;
typedef pair<string, shared_ptr<Material>> MaterialMapPair;

class InstanceGeometry : public ColladaObject {
   public:
      COLLADA_RENDER_FUNCTION
      void setGeometry(shared_ptr<Geometry> geometry) { geometry_ = geometry; }
      shared_ptr<Geometry> getGeometry() {return geometry_;}
      void addInstanceMaterial(string symbol, shared_ptr<Material> material);
      shared_ptr<Material> getInstanceMaterial(string symbol);
      MaterialMapIterator getFirstMaterial() { return materials_.begin(); }
      MaterialMapIterator getEndMaterial() { return materials_.end(); }

   private:
      shared_ptr<Geometry> geometry_;
      MaterialMap materials_;
};
typedef shared_ptr<InstanceGeometry> InstanceGeometryPtr;


#endif /* COLLADACPP_INSTANCEGEOMETRY_HPP_ */
