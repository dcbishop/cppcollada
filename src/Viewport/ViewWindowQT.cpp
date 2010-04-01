#include "ViewWindowQT.hpp"
#include <QtGui>
#include <QtOpenGL>

#include "../Debug/console.h"

#include "../GameData/Grid.hpp"
#include "../GameData/Camera.hpp"
#include "../Collada/Collada.hpp"
#include "../Render/ColladaRendererGL.hpp"

#include "../QTGui/QTEditScene.hpp"
#include "../QTGui/QTEditGeneric.hpp"

OpenGLScene::OpenGLScene(ViewWindowQT* vwqt) {
   grid_ = shared_ptr<Grid>(new Grid);
   vwqt_ = vwqt;
   renderer_.setSize(vwqt_->getWidth(), vwqt_->getHeight());

   QWidget *editCollada = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);
   editCollada->setWindowTitle("Edit Collada");
   editCollada->setLayout(new QVBoxLayout);
   
   QPushButton* editColladaButton = new QPushButton(tr("Edit Collada"));
   editCollada->layout()->addWidget(editColladaButton);
   
   connect(editColladaButton, SIGNAL(clicked()), this, SLOT(editCollada()));
   addOverlayedWidget(editCollada);

   time_.start();

}

void OpenGLScene::editCollada() {
   DEBUG_A("Oh boy!, PANCAKES!");
   newEditCollada = new QTEditCollada(vwqt_->getCollada());
   addOverlayedWidget((QWidget*)newEditCollada);
}

void OpenGLScene::addOverlayedWidget(QWidget* widget) {
   DEBUG_M("Entering function... %p", widget);
   if(!widget) {
      return;
   }
   widget->setWindowOpacity(0.8);

   QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(0, Qt::Dialog);
   proxy->setWidget(widget);
   addItem(proxy);

   QPointF pos(10, 10);
   foreach (QGraphicsItem *item, items()) {
      item->setFlag(QGraphicsItem::ItemIsMovable);
      item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

      const QRectF rect = item->boundingRect();
      item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
      pos += QPointF(0, 10 + rect.height());
   }

   QTEditGeneric* qtedit = dynamic_cast<QTEditGeneric*>(widget);
   if(qtedit) {
      qtedit->setOpenGLScene(this);
   }
}

void OpenGLScene::drawBackground(QPainter *painter, const QRectF &) {
   if (painter->paintEngine()->type() != QPaintEngine::OpenGL
      && painter->paintEngine()->type() != QPaintEngine::OpenGL2)
   {
      static bool nospam = false;
      if(!nospam) {
         WARNING("No OpenGL viewport widget set!");
      }
      nospam = true;
      return;
   }

   static int frame = 0;
   static int last_render_time = 0;
   static int last_fps_time = 0;
   static int fps_ = 0;
   static int mpf_ = 0;
   
   int current_time = time_.elapsed();

   // Limit framerate
   /*if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
      return;
   }*/

   // Calculate FPS
   frame++;
   if(current_time - last_fps_time > 1000) {
      fps_ = frame*1000.0f/(current_time-last_fps_time);
      last_fps_time = current_time;
      frame = 0;
      LOG("FPS: %d,\tMPF: %d",fps_, mpf_);
   }
   last_render_time = current_time;

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
   int end_time = time_.elapsed();
   mpf_ = end_time - current_time;
}

ViewWindowQT::ViewWindowQT(const int width, const int height): ViewWindow(width, height) {
   DEBUG_M("ViewWindowQT spawning...");

   int argc = 1;
   char* argv[] = {"Blah"};
   //QApplication::setStyle(QStyleFactory::create("motif"));
   app_ = new QApplication(argc, argv);
   scene_ = new OpenGLScene(this);
   vw_ = new ViewWidget(this);
   vw_->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
   vw_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
   vw_->setScene(scene_);
   vw_->resize(getWidth(), getHeight());
   vw_->show();
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
   mouseDown_ = false;
}

void ViewWidget::resizeEvent(QResizeEvent *event) {
   if (scene())
      scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
   QGraphicsView::resizeEvent(event);

   vwqt_->getRenderer()->setSize(event->size().width(), event->size().height());
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
   /*QGraphicsView::wheelEvent(event);
   if(event->isAccepted()) {
      return;
   }*/

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
