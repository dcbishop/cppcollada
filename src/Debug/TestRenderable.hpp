#include "../Collada/ColladaNode.hpp"

class TestRenderable : public ColladaNode {
   public:
      COLLADA_RENDER_FUNCTION
      TestRenderable() {
         width = 256;
         height = 256;
         //data = (char**)malloc(sizeof(char) * width * height);
         //data = new char[width][height];
         
         data = new char* [height];
         for(int i=0; i<height; i++) {
            data[i]=new char[width];
         }
      }

      ~TestRenderable() {
         //free(data);
      }

      int getHeight() {
         return height;
      }

      int getWidth() {
         return width;
      }

      int width;
      int height;
      char** data;
};

typedef shared_ptr<TestRenderable> TestRenderablePtr;
