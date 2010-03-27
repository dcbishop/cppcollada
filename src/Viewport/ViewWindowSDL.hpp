#ifndef COLLADACPP_VIEWWINDOWSDL_HPP_
#define COLLADACPP_VIEWWINDOWSDL_HPP_

class Collada;

#include <string>
using namespace std;

#include "ViewWindow.hpp"

#include "../GameData/SmartPointers.hpp"
#include "../Render/ColladaRendererGL.hpp"
#include "../Render/Renderable.hpp"
class Grid;

/**
 * A Simple window for viewing models in.
 */
class ViewWindowSDL: public ViewWindow {
   public:
      ViewWindowSDL(const int width, const int height);
      virtual ColladaRenderer* getRenderer();
      virtual void setTitle(const string title);
      virtual void mainLoop();

   private:
      int getComputerTime_();
      void draw_();
      void checkEvents_();
      void drawGrid_();
      bool finished_;
      ColladaRendererGL renderer_;
      int mx_, my_;
      bool cam_move_;
      shared_ptr<Grid> grid_;
};

#endif /* COLLADACPP_VIEWWINDOWSDL_HPP_ */
