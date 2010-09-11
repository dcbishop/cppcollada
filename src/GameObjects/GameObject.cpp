#include "../GameObjects/GameObject.hpp"
#include "../GameObjects/Area.hpp"

void GameObject::setArea(shared_ptr<Area> area) {
   area_ = area;
}

shared_ptr<Area> GameObject::getArea() const {
   return area_;
}
