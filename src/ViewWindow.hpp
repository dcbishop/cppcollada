#ifndef COLLADACPP_VIEWWINDOW_HPP_
#define COLLADACPP_VIEWWINDOW_HPP_

class Collada;

#include <string>
using namespace std;
#include "ColladaRendererGL.hpp"

/**
 * A Simple window for viewing models in.
 */
class ViewWindow {
   public:
      ViewWindow(int width, int height);
      void setCollada(Collada* collada);
      void setTitle(const string title);
      void mainLoop();
      int getComputerTime();

   private:
      void setPerspective_();
      void draw_();
      void checkEvents_();
      void drawGrid_();

      int width_;
      int height_;
      Collada* collada_;
      bool finished_;
      ColladaRendererGL renderer_;
};

#endif /* COLLADACPP_VIEWWINDOW_HPP_ */
