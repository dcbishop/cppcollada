#ifndef COLLADACPP_LAMBERT_HPP_
#define COLLADACPP_LAMBERT_HPP_

#include "../GameData/ColorRGBA.hpp"
#include "../Collada/ColladaLitShader.hpp"

class Lambert : public ColladaLitShader {
   public:
      COLLADA_RENDER_FUNCTION
};

typedef shared_ptr<Lambert> LambertPtr;

#endif /* COLLADACPP_LAMBERT_HPP_ */
