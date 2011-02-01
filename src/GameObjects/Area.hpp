#ifndef GAMEOBJECTS_AREA_HPP_
#define GAMEOBJECTS_AREA_HPP_

#include <set>
using namespace std;

#include "../GameData/Id.hpp"
#include "../GameData/Name.hpp"
#include "../Render/Renderable.hpp"
#include "../GameData/SmartPointers.hpp"
#include "../GameObjects/GameObject.hpp"

typedef set<GameObjectPtr> GameObjectsVector;
typedef GameObjectsVector::iterator GameObjectIterator;

class Area : public GameObject {
   public:
      ~Area();
      void addObject(GameObjectPtr object);
      void removeObject(GameObjectPtr object);
      void removeAllObjects_();
      GameObjectIterator getFirstGameObject() { return objects_.begin(); }
      GameObjectIterator getEndGameObject() { return objects_.end(); }
      COLLADA_RENDER_FUNCTION

   private:
      GameObjectsVector objects_;
};
typedef shared_ptr<Area> AreaPtr;


#endif /* GAMEOBJECTS_AREA_HPP_ */
