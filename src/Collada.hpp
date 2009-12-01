#ifndef COLLADACPP_COLLADA_HPP_
#define COLLADACPP_COLLADA_HPP_

#include <iostream>
using namespace std;

#include "SmartPointers.hpp"
#include "Renderable.hpp"
#include "Rotation.hpp"

class Scene;

class Collada : public Renderable {
   public:
      #warning ['TODO']: Filename?
      #warning ['TODO']: Asset information... created by and so on...
      void setScene(shared_ptr<Scene> scene);
      shared_ptr<Scene> getScene();
      COLLADA_RENDER_FUNCTION
      shared_ptr<Rotation> debugRotationHack; // TODO: remove me, for testing...

   private:
      shared_ptr<Scene> scene_;
};

#endif /* COLLADACPP_COLLADA_HPP_ */
