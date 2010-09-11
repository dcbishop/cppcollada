#ifndef GAMEOBJECTS_GAMEOBJECT_HPP_
#define GAMEOBJECTS_GAMEOBJECT_HPP_

#include "../GameData/Id.hpp"
#include "../GameData/Name.hpp"
#include "../Render/Renderable.hpp"
#include "../GameData/Position.hpp"
#include "../GameData/Scale.hpp"
#include "../GameData/RotationGL.hpp"
#include "../GameData/SmartPointers.hpp"

class Area;

class GameObject : public Id, public Name, public Renderable, public Position, public RotationGL, public Scale {
   public:
      void setArea(shared_ptr<Area> area);
      shared_ptr<Area> getArea() const;
      COLLADA_RENDER_FUNCTION

   private:
      shared_ptr<Area> area_;
};
typedef shared_ptr<GameObject> GameObjectPtr;

#endif /* GAMEOBJECTS_GAMEOBJECT_HPP_ */
