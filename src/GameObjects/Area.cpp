#include "../GameObjects/Area.hpp"

#include "../Debug/console.h"

void Area::addObject(GameObjectPtr object) {
   objects_.push_back(object);
   shared_ptr<Area> areaPtr(this);
   object->setArea(areaPtr);
}

void Area::removeObject(GameObjectPtr object) {
   #warning ['TODO']: Stub function
   WARNING("STUB FUNCTION!");
}
