#ifndef COLLADACPP_VIEWWINDOWSDL_HPP_
#define COLLADACPP_VIEWWINDOWSDL_HPP_

#include "ViewWindow.hpp"
class Collada;

#include <string>
using namespace std;

#include "SDL.h"

#include "../GameData/SmartPointers.hpp"
#include "../Render/RendererGL.hpp"
#include "../Render/Renderable.hpp"
class Grid;

/**
 * A Simple window for viewing models in.
 */
class ViewWindowSDL: public ViewWindow {
   public:
      ViewWindowSDL(const int width, const int height);
      virtual void setTitle(const string title);
      virtual void mainLoop();

   private:
      int getComputerTime_();
      void draw_();
      void checkEvents_();
      void handleKeyUp_(const SDL_Event& event);

      bool finished_;
      RendererGL renderer_;
      int mx_, my_;
      bool cam_move_;
      shared_ptr<Grid> grid_;
};

#endif /* COLLADACPP_VIEWWINDOWSDL_HPP_ */
