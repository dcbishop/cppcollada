#include "ViewWindowQT.hpp"
#include <QtGui>
#include <QtOpenGL>

#include "console.h"

#include "Grid.hpp"
#include "Camera.hpp"
#include "Collada.hpp"
#include "ColladaRendererGL.hpp"

OpenGLScene::OpenGLScene(ViewWindowQT* vwqt) {
   grid_ = shared_ptr<Grid>(new Grid);
   vwqt_ = vwqt;
   renderer_.setSize(vwqt_->getWidth(), vwqt_->getHeight());
   QWidget *testDialog = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);
   testDialog->setWindowOpacity(0.8);
   testDialog->setWindowTitle("Test Dialog!");
   testDialog->setLayout(new QVBoxLayout);
   
   testButton_ = new QPushButton(tr("Push Me!"));
   testDialog->layout()->addWidget(testButton_);
   
   QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(0, Qt::Dialog);
   proxy->setWidget(testDialog);
   addItem(proxy);
   
   QPointF pos(10, 10);
   foreach (QGraphicsItem *item, items()) {
      item->setFlag(QGraphicsItem::ItemIsMovable);
      item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

      const QRectF rect = item->boundingRect();
      item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
      pos += QPointF(0, 10 + rect.height());
   }
}

void OpenGLScene::drawBackground(QPainter *painter, const QRectF &) {
   if (painter->paintEngine()->type() != QPaintEngine::OpenGL
      && painter->paintEngine()->type() != QPaintEngine::OpenGL2)
   {
      //qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
      static bool nospam = false;
      if(!nospam) {
         WARNING("No OpenGL viewport widget set!");
      }
      nospam = true;
      return;
   }

   painter->beginNativePainting();

   renderer_.preFrame();

   if(vwqt_->getCamera() != shared_ptr<Camera>()) {
      vwqt_->getCamera()->render();
   }

   grid_->render();

   shared_ptr<Collada> collada = vwqt_->getCollada();
   if(collada) {
      collada->render();
   }

   renderer_.postFrame();

   painter->endNativePainting();

   QTimer::singleShot(20, this, SLOT(update()));
}

ViewWindowQT::ViewWindowQT(const int width, const int height): ViewWindow(width, height) {
   DEBUG_M("ViewWindowQT spawning...");

   //renderer_.setSize(getWidth(), getHeight());
   int argc = 1;
   char* argv[] = {"Blah"};
   //QApplication app(argc, argv);
   //QApplication app();
   QApplication::setStyle(QStyleFactory::create("motif"));
   app_ = new QApplication(argc, argv);
  
   //vw_ = new ViewWidget(this);
   //vw_->setAutoFillBackground(false);

//   view.setViewport(new ViewWidget(this));
    
    scene_ = new OpenGLScene(this);
    vw_ = new ViewWidget(this);
    vw_->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    vw_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    vw_->setScene(scene_);
    vw_->show();

    vw_->resize(1024, 768);
    //camera_ = NULL;
   //vw_->show();
   //vw_->setMouseTracking(true);
   /*QWidget window;
   window.resize(getWidth(), getHeight());
   window.show();
   QGLWidget opengl;
   opengl.show();*/
   
   //QPushButton test("TestButton", 0);
   //test.resize(100, 30);
   //app.setMainWidget(&test);
   //window.addWidget(test);
   //window.setWindowOpacity(0.5f);
   //test.show();

   //finished_ = false;
   //app_->exec();
}

ViewWindowQT::~ViewWindowQT() {
   DEBUG_M("Cleaning up ViewWindowQT...");

   delete vw_;
   delete scene_;
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
   return &scene_->renderer_;
}

void ViewWindowQT::quit() {
   app_->quit();
}

ViewWidget::ViewWidget(ViewWindowQT* vwqt) {
   vwqt_ = vwqt;
}

#if 0
void ViewWidget::initializeGL() {
   renderer_.init();
}

void ViewWidget::resizeGL(int width, int height) {
	DEBUG_M("Resize %d %d", width, height);
   renderer_.setSize(width, height);
}

void ViewWidget::paintGL() {
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

   if(getCamera() != shared_ptr<Camera>()) {
      vwqt_->getCamera()->render();
   }

   grid_->render();

   shared_ptr<Collada> collada = vwqt_->getCollada();
   if(collada) {
      collada->render();
   }

   renderer_.postFrame();
   swapBuffers();

   //mpf_ = getComputerTime_() - current_time;
}
#endif

void ViewWidget::resizeEvent(QResizeEvent *event) {
   DEBUG_M("Fired... A");
   if (scene())
      scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
   QGraphicsView::resizeEvent(event);
   
   vwqt_->getRenderer()->setSize(event->size().width(), event->size().height());
   DEBUG_M("Fired... B");
}

void ViewWidget::mouseMoveEvent(QMouseEvent *event) {
   DEBUG_H("Fired...");
   // Check if the event is handled by the overdrawn QT widgets
   if(!mouseDown_) {
      QGraphicsView::mouseMoveEvent(event);
      if(event->isAccepted()) {
         return;
      }
   }

   int x = event->x();
   int y = event->y();
   float xrel = x-oldx_;
   float yrel = y-oldy_;

   event->accept();

   shared_ptr<Camera> camera = vwqt_->getCamera();  
   if(camera == shared_ptr<Camera>()) {
      WARNING("NO CAMERA!");
      return;
   }
   camera->setRotX(camera->getRotX() + xrel / vwqt_->getWidth() * 100);
   camera->setRotY(camera->getRotY() - yrel / vwqt_->getHeight() * 100);
   update();

   oldx_ = x;
   oldy_ = y;
}

void ViewWidget::mousePressEvent(QMouseEvent *event) {
   DEBUG_H("Fired...");
   // Check if the event is handled by the overdrawn QT widgets
   QGraphicsView::mousePressEvent(event);
   if(event->isAccepted()) {
      return;
   }

   mouseDown_ = true;
   oldx_ = event->x();
   oldy_ = event->y();
   event->accept();
}

void ViewWidget::mouseReleaseEvent(QMouseEvent *event) {
   DEBUG_H("Fired...");
   mouseDown_ = false;
   // Check if the event is handled by the overdrawn QT widgets
   QGraphicsView::mouseReleaseEvent(event);
   if(event->isAccepted()) {
      return;
   }
   
}

void ViewWidget::wheelEvent(QWheelEvent * event) {
   // Check if the event is handled by the overdrawn QT widgets
   DEBUG_M("Fired... A");
   /*QGraphicsView::wheelEvent(event);
   if(event->isAccepted()) {
      return;
   }
   DEBUG_M("Fired... B");*/
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

void ViewWidget::keyPressEvent(QKeyEvent * event) {
   // Check if the event is handled by the overdrawn QT widgets
   QGraphicsView::keyPressEvent(event);
   if(event->isAccepted()) {
      return;
   }
   if(event->matches(QKeySequence::Quit) ||
      event->key() == Qt::Key_Q ||
      event->key() == Qt::Key_Escape) {
      DEBUG_M("Quit key pressed...");
      vwqt_->quit();
      return;
   }
}

void ViewWidget::keyReleaseEvent(QKeyEvent * event) {
   // Check if the event is handled by the overdrawn QT widgets
   QGraphicsView::keyReleaseEvent(event);
   if(event->isAccepted()) {
      return;
   }
}
