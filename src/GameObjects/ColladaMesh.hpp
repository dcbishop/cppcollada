#ifndef GAMEOBJECTS_COLLADAMESH_HPP_
#define GAMEOBJECTS_COLLADAMESH_HPP_

#include "../GameObjects/GameObject.hpp"
#include "../Collada/Collada.hpp"

class ColladaMesh: public GameObject {
   public:
      void setCollada(ColladaPtr collada) { collada_ = collada; }
      ColladaPtr getCollada() { return collada_; }
      COLLADA_RENDER_FUNCTION

   private:
      ColladaPtr collada_;
};
typedef shared_ptr<ColladaMesh> ColladaMeshPtr;


#endif /* GAMEOBJECTS_COLLADAMESH_HPP_ */
