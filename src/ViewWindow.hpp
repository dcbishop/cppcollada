#ifndef COLLADACPP_VIEWWINDOW_HPP_
#define COLLADACPP_VIEWWINDOW_HPP_

class Collada;
class Camera;

#include <string>
using namespace std;

#include "SmartPointers.hpp"

/**
 * A Simple window for viewing models in.
 */
class ViewWindow {
   public:
      ViewWindow() {};
      ViewWindow(int width, int height);
      virtual void setCollada(shared_ptr<Collada> collada) = 0;
      virtual void setCamera(shared_ptr<Camera> camera) = 0;
      virtual void setTitle(const string title) = 0;
      virtual void mainLoop() = 0;
      virtual int getComputerTime() = 0;
      virtual void setSize(const int width, const int height);
      virtual int getWidth();
      virtual int getHeight();

   private:
      int width_;
      int height_;
};

#endif /* COLLADACPP_VIEWWINDOW_HPP_ */
