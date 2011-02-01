#include "../GameObjects/Area.hpp"

#include "../Debug/console.h"

Area::~Area() {
   removeAllObjects_();
}

void Area::addObject(GameObjectPtr object) {
   objects_.insert(object);
   shared_ptr<Area> areaPtr(this);
   object->setArea(areaPtr);
}

void Area::removeAllObjects_() {
   for(GameObjectsVector::iterator it=objects_.begin(); it != objects_.end(); it++) {
      (*it)->setArea(AreaPtr());
      objects_.erase(it);
   }
}

void Area::removeObject(GameObjectPtr object) {
   #warning ['TODO']: Stub function
   GameObjectsVector::iterator it = objects_.find(object);
   object->setArea(AreaPtr());
   objects_.erase(object);
}
