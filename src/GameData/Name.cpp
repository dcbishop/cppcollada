#include "../GameData/Name.hpp"

/**
 * Gets the name of the object.
 * @return The name.
 */
const string& Name::getName() const {
   return name_;
}

/**
 * Sets the name of the object.
 * @param name The name.
 */
void Name::setName(const string& name) {
   name_ = name;
}
