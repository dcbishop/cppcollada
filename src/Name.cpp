#include "Name.hpp"

/**
 * Gets the name of the object.
 * @return The name.
 */
const string Name::getName() {
   return name_;
}

/**
 * Sets the name of the object.
 * @param name The name.
 */
void Name::setName(string name) {
   name_ = name;
}
