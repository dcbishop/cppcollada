#include "../Collada/Collada.hpp"

/**
 * Sets the filename of the Collada .dae file.
 */
void Collada::setFilename(const string filename) {
   filename_ = filename;
}

/**
 * Get's the filename of the Collada .dae file.
 */
string Collada::getFilename() {
   return filename_;
}

/**
 * Sets the Collada's Scene objcet.
 */
void Collada::setScene(shared_ptr<Scene> scene) {
   scene_ = scene;
}

/**
 * Gets the Collada's Scene object.
 */
shared_ptr<Scene> Collada::getScene() {
   return scene_;
}

/**
 * Adds a ColladaObject to the Collada's list of IDs.
 */
void Collada::addId(const string id, ColladaObjectPtr object) {
   ids_.insert(IdMapPair(id, object));
}

/**
 * Get's a ColladaObject from the Collada by it's ID.
 */
ColladaObjectPtr Collada::getId(const string id) {
   return ids_.find(id)->second;
}
