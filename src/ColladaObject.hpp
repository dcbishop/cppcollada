#ifndef COLLADACPP_COLLADAOBJECT_HPP_
#define COLLADACPP_COLLADAOBJECT_HPP_

#include "Id.hpp"
#include "Name.hpp"
#include "Renderable.hpp"

class ColladaObject: public Id, public Name, public Renderable {
   public:
      COLLADA_RENDER_FUNCTION
};

#endif /* COLLADACPP_COLLADAOBJECT_HPP_ */
