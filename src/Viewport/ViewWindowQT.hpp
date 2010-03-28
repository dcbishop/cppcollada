#ifndef COLLADACPP_VIEWWINDOWQT_HPP_
#define COLLADACPP_VIEWWINDOWQT_HPP_

class Collada;

#include <string>
using namespace std;

#include "ViewWindow.hpp"

#include "../GameData/SmartPointers.hpp"
#include "../Render/ColladaRendererGL.hpp"
#include "../Render/Renderable.hpp"
#include "../QTGui/QTEditCollada.hpp"

#include "../Debug/console.h"
class Grid;

#include <QtGui>
#include <QtOpenGL>

class ViewWindowQT;
class ViewWidget;

/*class GraphicsView : public QGraphicsView {
   public:
      GraphicsView() {
         setWindowTitle("Test!");
      }
      
   protected:
      void resizeEvent(QResizeEvent *event) {
         if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         QGraphicsView::resizeEvent(event);
      }
};*/

class OpenGLScene : public QGraphicsScene {
   Q_OBJECT
   public:
      OpenGLScene(ViewWindowQT* vwqt);
      ~OpenGLScene() { DEBUG_M("Cleaning up OpenGLScene");}
      void drawBackground(QPainter *painter, const QRectF &rect);
      void addOverlayedWidget(QWidget* widget);

      ColladaRendererGL renderer_;

   public slots:
      void editCollada();


   private:
      ViewWindowQT *vwqt_;
      shared_ptr<Grid> grid_;
      QTime time_;
};

/**
 * A Simple window for viewing models in.
 */
class ViewWindowQT: public ViewWindow {
   public:
      ViewWindowQT(const int width, const int height);
      ~ViewWindowQT();
      virtual ColladaRenderer* getRenderer();
      virtual void setTitle(const string title);
      virtual void mainLoop();
      virtual void quit();
      void resizeEvent(QResizeEvent *event);

   private:
      QApplication *app_;
      OpenGLScene *scene_;
      ViewWidget *vw_;
      bool finished_;
      int mx_, my_;
      bool cam_move_;
};

class ViewWidget: public QGraphicsView {
   Q_OBJECT
   public:
      ViewWidget(ViewWindowQT* vwqt);
      //void initializeGL();
      //void resizeGL(int width, int heigh);
      //void paintGL();
      ///ColladaRendererGL renderer_;

      void resizeEvent(QResizeEvent *event);
      void mouseMoveEvent (QMouseEvent* event);
      void mousePressEvent(QMouseEvent *event);
      void mouseReleaseEvent(QMouseEvent *event);
      void wheelEvent(QWheelEvent * event);
      void keyPressEvent(QKeyEvent * event);
      void keyReleaseEvent(QKeyEvent * event);


   private:
      ViewWindowQT *vwqt_;
      int oldx_;
      int oldy_;
      bool mouseDown_;
};

#endif /* COLLADACPP_VIEWWINDOWQT_HPP_ */
