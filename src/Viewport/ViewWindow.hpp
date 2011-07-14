#ifndef COLLADACPP_VIEWWINDOW_HPP_
#define COLLADACPP_VIEWWINDOW_HPP_

class Collada;
class Camera;

#include <string>
using namespace std;

#include "../GameData/SmartPointers.hpp"
#include "../Render/ColladaRenderer.hpp"
#include "../Collada/ColladaManager.hpp"
#include "../GameObjects/Camera.hpp"
#include "../GameData/Controller.hpp"

/**
 * A Simple window for viewing models in.
 */
class ViewWindow {
   public:
      ViewWindow();
      ViewWindow(const int width, const int height);
      virtual void setTitle(const string title) = 0;
      virtual void mainLoop() = 0;
      virtual void setSize(const int width, const int height);
      virtual int getWidth() const;
      virtual int getHeight() const;
      virtual ColladaRenderer* getRenderer() = 0;
      virtual void setCamera(CameraPtr camera);
      virtual CameraPtr getCamera() const;
      ControllerPtr getController() const;
      void setController(ControllerPtr controller);

   private:
      int width_;
      int height_;
      CameraPtr camera_;
      ControllerPtr controller_;
};

#endif /* COLLADACPP_VIEWWINDOW_HPP_ */
