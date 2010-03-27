#ifndef COLLADACPP_VIEWWINDOW_HPP_
#define COLLADACPP_VIEWWINDOW_HPP_

class Collada;
class Camera;

#include <string>
using namespace std;

#include "../GameData/SmartPointers.hpp"
#include "../Render/ColladaRenderer.hpp"

/**
 * A Simple window for viewing models in.
 */
class ViewWindow {
   public:
      ViewWindow();
      ViewWindow(const int width, const int height);
      virtual void setCollada(shared_ptr<Collada> collada);
      shared_ptr<Collada> getCollada();
      virtual void setTitle(const string title) = 0;
      virtual void mainLoop() = 0;
      virtual void setSize(const int width, const int height);
      virtual int getWidth();
      virtual int getHeight();
      virtual ColladaRenderer* getRenderer() = 0;
      virtual void setCamera(shared_ptr<Camera> camera);
      virtual shared_ptr<Camera> getCamera();

   private:
      int width_;
      int height_;
      shared_ptr<Collada> collada_;
      shared_ptr<Camera> camera_;
};

#endif /* COLLADACPP_VIEWWINDOW_HPP_ */
