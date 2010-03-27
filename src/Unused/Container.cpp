#include "Container.hpp"

/**
 * Adds a thing to the container.
 * @param child The thing to be contained.
 */
void Container::add(Contained* child) {
   if(!child) {
      return;
   }

   // Stop adding the child more than once
   ChildrenIterator found = find(getChildBegin(), getChildEnd(), child);
   if(found != getChildEnd()) {
      return;
   }

   child->setParent(this);
   children_.push_back(child);
}

/**
 * Removes a thing from the container.
 * @param child The thing to be contained.
 */
void Container::remove(Contained* child) {
   //DEBUG_M("Entering function remove...");
   if(!child) {
      return;
   }

   //DEBUG_H("\tRemoving object from container object vector.");
   ChildrenIterator found = find(getChildBegin(), getChildEnd(), child);

   if(found != getChildEnd()) {
      if(*found && ((*found) == child)) {
         children_.erase(found);
      }
   }
}

/**
 * Returns a pointer to the vector containing the children.
 * @return Iterator to the first contained element.
 */
ChildrenIterator Container::getChildBegin() {
   return children_.begin();
}

/**
 * Returns a pointer to the vector end.
 * @return Iterator to the last contained element.
 */
ChildrenIterator Container::getChildEnd() {
   return children_.end();
}

/**
 * Sets the parent/owner Container.
 * @param parent The thing within which this thing is contained.
 */
void Contained::setParent(Container* parent) {
   parent_ = parent;
}

/**
 * Gets the parent/owning Container of the thing.
 * @return Pointer to the parent Container.
 */
Container* Contained::getParent() {
   return parent_;
}
