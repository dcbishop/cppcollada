#include "ViewWindow.hpp"
#include "../Collada/Collada.hpp"
#include "../GameObjects/Camera.hpp"

#include "../Debug/console.h"

#include "../GameData/Globals.hpp"

ViewWindow::ViewWindow(const int width, const int height) {
   camera_ = CameraPtr();
   setSize(width, height);
}

void ViewWindow::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
}

int ViewWindow::getWidth() const {
   return width_;
}

int ViewWindow::getHeight() const {
   return height_;
}

void ViewWindow::setCamera(CameraPtr camera) {
   camera_ = camera;
   g.getRenderer()->setCameraMatrix(camera.get());
}

CameraPtr ViewWindow::getCamera() const {
   return camera_;
}

ControllerPtr ViewWindow::getController() const {
   return controller_;
}

void ViewWindow::setController(ControllerPtr controller) {
   controller_ = controller;
}
