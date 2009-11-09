#ifndef COLLADACPP_NODE_HPP_
#define COLLADACPP_NODE_HPP_


#include <string>

#include "Position.hpp"
#include "Rotation.hpp"
#include "RotationGL.hpp"
#include "ColladaObject.hpp"
#include "Scale.hpp"

class Node : public ColladaObject, public Position, public RotationGL, public Scale {
   private:
      string layer_;
};

#endif /* COLLADACPP_NODE_HPP_ */
