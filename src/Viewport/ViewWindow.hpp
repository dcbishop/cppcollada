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

/**
 * A Simple window for viewing models in.
 */
class ViewWindow {
   public:
      ViewWindow();
      ViewWindow(const int width, const int height);
      /*virtual void setCollada(ColladaPtr collada);
      ColladaPtr getCollada();*/
      virtual void setTitle(const string title) = 0;
      virtual void mainLoop() = 0;
      virtual void setSize(const int width, const int height);
      virtual int getWidth();
      virtual int getHeight();
      virtual ColladaRenderer* getRenderer() = 0;
      virtual void setCamera(CameraPtr camera);
      virtual CameraPtr getCamera();
      //virtual void setColladaManager(ColladaManagerPtr cm) { cm_ = cm; }
      //virtual ColladaManagerPtr getColladaManager() { return cm_; }

   private:
      int width_;
      int height_;
      /*ColladaPtr collada_;
      ColladaManagerPtr cm_;*/
      CameraPtr camera_;
};

#endif /* COLLADACPP_VIEWWINDOW_HPP_ */
