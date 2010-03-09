#include "ViewWindowQT.hpp"
#include <QtGui>
#include <QtOpenGL>

#include "console.h"

#include "Grid.hpp"
#include "Camera.hpp"
#include "Collada.hpp"
#include "ColladaRendererGL.hpp"

ViewWindowQT::ViewWindowQT(const int width, const int height): ViewWindow(width, height) {
   DEBUG_M("ViewWindowQT spawning...");

   //renderer_.setSize(getWidth(), getHeight());
   int argc = 1;
   char* argv[] = {"Blah"};
   //QApplication app(argc, argv);
   //QApplication app();
   app_ = new QApplication(argc, argv);
   vw_ = new ViewWidget(this);
   vw_->show();
   //vw_->setMouseTracking(true);
   /*QWidget window;
   window.resize(getWidth(), getHeight());
   window.show();
   QGLWidget opengl;
   opengl.show();*/
   
   QPushButton test("TestButton", 0);
   test.resize(100, 30);
   //app.setMainWidget(&test);
   //window.addWidget(test);
   //window.setWindowOpacity(0.5f);
   test.show();

   //finished_ = false;
   //app.exec();
}

ViewWindowQT::~ViewWindowQT() {
   DEBUG_M("Cleaning up ViewWindowQT...");
   delete vw_;
   delete app_;
}

void ViewWindowQT::setTitle(const string title) {
   if(vw_) {
      vw_->setWindowTitle(title.c_str());
   }
}

/**
 * The main rendering and input loop.
 */
void ViewWindowQT::mainLoop() {
   DEBUG_L("Interface::mainLoop()");

   //while(!finished_) {
      //checkEvents_();
      //draw_();
   //}
   if(app_) {
      app_->exec();
   }
   DEBUG_M("Finished...");
}

ColladaRenderer* ViewWindowQT::getRenderer() {
   return &vw_->renderer_;
}

ViewWindowQT::ViewWidget::ViewWidget(ViewWindowQT* vwqt) {
      vwqt_ = vwqt;
      grid_ = shared_ptr<Grid>(new Grid);
}

void ViewWindowQT::ViewWidget::initializeGL() {
   renderer_.init();
}

void ViewWindowQT::ViewWidget::resizeGL(int width, int height) {
	DEBUG_M("Resize %d %d", width, height);
   renderer_.setSize(width, height);
}

void ViewWindowQT::ViewWidget::paintGL() {
   /*static int frame = 0;
   static int last_render_time = 0;
   static int last_fps_time = 0;
   static bool limit_fps_ = true;
   static int fps_ = 0;
   static int mpf_ = 0;
   
   int current_time = getComputerTime_();

   // Limit framerate
   if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
      return;
   }

   // Calculate FPS
   frame++;
   if(current_time - last_fps_time > 1000) {
      fps_ = frame*1000.0f/(current_time-last_fps_time);
      last_fps_time = current_time;
      frame = 0;
      LOG("FPS: %d,\tMPF: %d",fps_, mpf_);
   }
   last_render_time = current_time;*/

   renderer_.preFrame();

   vwqt_->getCamera()->render();
   grid_->render();

   shared_ptr<Collada> collada = vwqt_->getCollada();
   if(collada) {
      collada->render();
   }

   renderer_.postFrame();
   swapBuffers();

   //mpf_ = getComputerTime_() - current_time;
}

void ViewWindowQT::ViewWidget::mouseMoveEvent(QMouseEvent *event) {
   int x = event->x();
   int y = event->y();
   float xrel = x-oldx;
   float yrel = y-oldy;

   shared_ptr<Camera> camera = vwqt_->getCamera();      
   camera->setRotX(camera->getRotX() + xrel / vwqt_->getWidth() * 100);
   camera->setRotY(camera->getRotY() - yrel / vwqt_->getHeight() * 100);
   update();

   oldx = x;
   oldy = y;

   event->accept();
}

void ViewWindowQT::ViewWidget::mousePressEvent(QMouseEvent *event) {
   DEBUG_H("Fired...");
   oldx = event->x();
   oldy = event->y();
   event->accept();
}

void ViewWindowQT::ViewWidget::mouseReleaseEvent(QMouseEvent *event) {
   DEBUG_H("Fired...");
}

void ViewWindowQT::ViewWidget::wheelEvent(QWheelEvent * event) {
   DEBUG_H("Fired...");
   int numDegrees = event->delta() / 8;
   int numSteps = numDegrees / 15;

   if(event->orientation() == Qt::Horizontal) {
      // left/right scrolling...
   } else {
      shared_ptr<Camera> camera = vwqt_->getCamera();
      camera->setZoom(camera->getZoomTarget() + ZOOM_STEP * -numSteps);
   }
   event->accept();
   update();
}

void ViewWindowQT::ViewWidget::keyPressEvent(QKeyEvent * event) {
   if(event->matches(QKeySequence::Quit) ||
      event->key() == Qt::Key_Q ||
      event->key() == Qt::Key_Escape) {
      DEBUG_M("Quit key pressed...");
      vwqt_->app_->quit();
      return;
   }
}

void ViewWindowQT::ViewWidget::keyReleaseEvent(QKeyEvent * event) {

}
