#include "Id.hpp"

/**
 * Gets the object's ID.
 * @return The ID of the object.
 */
const string Id::getId() {
   return id_;
}

/**
 * Sets the object's ID.
 * @param id The id to set.
 */
void Id::setId(string id) {
   id_ = id;
}
