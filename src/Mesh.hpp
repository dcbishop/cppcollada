#ifndef COLLADACPP_MESH_HPP_
#define COLLADACPP_MESH_HPP_

#include "Geometry.hpp"

class Mesh : public Geometry, public Renderable {
   public:
      COLLADA_RENDER_FUNCTION
};

#endif /* COLLADACPP_MESH_HPP_ */
