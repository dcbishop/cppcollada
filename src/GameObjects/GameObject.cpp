#include "../GameObjects/GameObject.hpp"
#include "../GameObjects/Area.hpp"

#include "../Debug/console.h"

GameObject::~GameObject() {
   DEBUG_M("Entering deconstructor...");
   if(area_) {
      area_->removeObject(GameObjectPtr(this));
   }
   DEBUG_M("Exiting deconstructor...");
}

void GameObject::setArea(shared_ptr<Area> area) {
   area_ = area;
}

shared_ptr<Area> GameObject::getArea() const {
   return area_;
}
