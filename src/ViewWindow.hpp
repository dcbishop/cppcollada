#ifndef COLLADACPP_VIEWWINDOW_HPP_
#define COLLADACPP_VIEWWINDOW_HPP_

class Collada;

#include <string>
using namespace std;

#include "SmartPointers.hpp"
#include "ColladaRendererGL.hpp"
#include "Renderable.hpp"

/**
 * A simple grid.
 */
class Grid: public Renderable {
   private:
      int sx_, sy_, sz_;
      float spacing_;
      float color_[3];
   public:
      Grid(){ 
         sx_ = 10;
         sy_ = 10;
         sz_ = 10;
         spacing_ = 1.0f;
         color_[0] = 1.0f; color_[1] = 1.0f; color_[2] = 1.0f;
      }
      float getSpacing() {return spacing_;}
      int getSizeX(){return sx_;}
      int getSizeY(){return sy_;}
      int getSizeZ(){return sz_;}
      float* getColor(){return color_;}
      COLLADA_RENDER_FUNCTION
};

/**
 * A Simple window for viewing models in.
 */
class ViewWindow {
   public:
      ViewWindow(int width, int height);
      void setCollada(shared_ptr<Collada> collada);
      void setCamera(shared_ptr<Camera> camera);
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
      shared_ptr<Collada> collada_;
      bool finished_;
      ColladaRendererGL renderer_;
      shared_ptr<Camera> camera_;
      int mx_, my_;
      bool cam_move_;
      shared_ptr<Position> position_;
      shared_ptr<Grid> grid_;
};

#endif /* COLLADACPP_VIEWWINDOW_HPP_ */
