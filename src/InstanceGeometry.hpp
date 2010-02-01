#ifndef COLLADACPP_INSTANCEGEOMETRY_HPP_
#define COLLADACPP_INSTANCEGEOMETRY_HPP_

#include "ColladaObject.hpp"


class InstanceGeometry : public ColladaObject {
   public:
      COLLADA_RENDER_FUNCTION
      void setGeometry(shared_ptr<Geometry> geometry) { geometry_ = geometry; }
      shared_ptr<Geometry> getGeometry() {return geometry_;}

   private:
      shared_ptr<Geometry> geometry_;
};

#endif /* COLLADACPP_INSTANCEGEOMETRY_HPP_ */
