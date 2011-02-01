#ifndef COLLADACPP_TRIANGLES_HPP_
#define COLLADACPP_TRIANGLES_HPP_

#include "../Render/Renderable.hpp"
#include "../Collada/GeometricPrimitive.hpp"

class Material;

class Triangles : public GeometricPrimitive {
   public:
      COLLADA_RENDER_FUNCTION
};
typedef shared_ptr<Triangles> TrianglesPtr;

#endif /* COLLADACPP_TRIANGLES_HPP_ */
