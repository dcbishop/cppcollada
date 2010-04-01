#ifndef COLLADACPP_MESH_HPP_
#define COLLADACPP_MESH_HPP_

#include "../Collada/Geometry.hpp"
#include "../GameData/SmartPointers.hpp"

class Mesh : public Geometry {
   public:
      COLLADA_RENDER_FUNCTION
};
typedef shared_ptr<Mesh> MeshPtr;

#endif /* COLLADACPP_MESH_HPP_ */
