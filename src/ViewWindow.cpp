#include "ViewWindow.hpp"

void ViewWindow::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
}

int ViewWindow::getWidth() {
   return width_;
}

int ViewWindow::getHeight() {
   return height_;
}
