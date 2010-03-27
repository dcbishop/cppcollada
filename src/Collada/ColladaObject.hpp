#ifndef COLLADACPP_COLLADAOBJECT_HPP_
#define COLLADACPP_COLLADAOBJECT_HPP_

#include "../GameData/Id.hpp"
#include "../GameData/Name.hpp"
#include "../Render/Renderable.hpp"

class ColladaObject: public Id, public Name, public Renderable {
   public:
      COLLADA_RENDER_FUNCTION
};

#endif /* COLLADACPP_COLLADAOBJECT_HPP_ */
