#include <string>
using namespace std;

#include <GL/gl.h>

#include "../GameData/SmartPointers.hpp"
#include "../Collada/Image.hpp"

class ColladaRendererGL_DevIL {
   public:
      ~ColladaRendererGL_DevIL();
      void init();
      int loadImage(ImagePtr image);

   private:
      unordered_map<string, GLuint> images_;
};
