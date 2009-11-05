#include <string>

#include "Position.hpp"
#include "Rotation.hpp"
#include "ColladaObject.hpp"

class Node : public ColladaObject, public Position, public Rotation {
   private:
      string layer_;
};
