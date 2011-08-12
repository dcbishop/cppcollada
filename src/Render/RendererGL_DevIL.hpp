#include <string>
using namespace std;


#include "../GameData/SmartPointers.hpp"
#include "../Collada/Image.hpp"

class RendererGL_DevIL {
   public:
      ~RendererGL_DevIL();
      void init();
      int loadImage(ImagePtr image);

   private:
      unordered_map<string, int> images_;
};
