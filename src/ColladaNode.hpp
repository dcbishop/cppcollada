#ifndef COLLADACPP_NODE_HPP_
#define COLLADACPP_NODE_HPP_


#include <string>

#include "Renderable.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "RotationGL.hpp"
#include "ColladaObject.hpp"
#include "Scale.hpp"

#warning ['TODO']: ColladaNodes can have other transition types...

class ColladaNode : public ColladaObject, public Position, public RotationGL, public Scale {
   public:
      COLLADA_RENDER_FUNCTION
      
   private:
      string layer_;
};

#endif /* COLLADACPP_NODE_HPP_ */
