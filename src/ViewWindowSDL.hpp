#ifndef COLLADACPP_ViewWindowSDL_HPP_
#define COLLADACPP_ViewWindowSDL_HPP_

class Collada;

#include <string>
using namespace std;

#include "ViewWindow.hpp"

#include "SmartPointers.hpp"
#include "ColladaRendererGL.hpp"
#include "Renderable.hpp"
class Grid;

/**
 * A Simple window for viewing models in.
 */
class ViewWindowSDL: public ViewWindow {
   public:
      ViewWindowSDL(int width, int height);
      void setCollada(shared_ptr<Collada> collada);
      void setCamera(shared_ptr<Camera> camera);
      void setTitle(const string title);
      void mainLoop();
      int getComputerTime();

   private:
      void draw_();
      void checkEvents_();
      void drawGrid_();

      shared_ptr<Collada> collada_;
      bool finished_;
      ColladaRendererGL renderer_;
      shared_ptr<Camera> camera_;
      int mx_, my_;
      bool cam_move_;
      shared_ptr<Position> position_;
      shared_ptr<Grid> grid_;
};

#endif /* COLLADACPP_ViewWindowSDL_HPP_ */
