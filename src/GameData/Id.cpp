#include "../GameData/Id.hpp"

/**
 * Gets the object's ID.
 * @return The ID of the object.
 */
const string& Id::getId() const {
   return id_;
}

/**
 * Sets the object's ID.
 * @param id The id to set.
 */
void Id::setId(const string& id) {
   id_ = id;
}
