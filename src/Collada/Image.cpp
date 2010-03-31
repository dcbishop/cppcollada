#include "../Collada/Image.hpp"

void Image::setFilename(const string filename) {
   filename_ = filename;
}

string Image::getFilename() {
   return filename_;
}
