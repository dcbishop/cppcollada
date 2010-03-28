#include "../Collada/Collada.hpp"
void Collada::setFilename(const string filename) {
   filename_ = filename;
}

string Collada::getFilename() {
   return filename_;
}

void Collada::setScene(shared_ptr<Scene> scene) {
   scene_ = scene;
}

shared_ptr<Scene> Collada::getScene() {
   return scene_;
}
