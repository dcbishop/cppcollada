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
#include "../QTGui/QTEditColladas.hpp"

#include "../Debug/console.h"
class Grid;

#include <QtGui>
#include <QtOpenGL>
#include <QWebView>

class ViewWindowQT;
class ViewWidget;

class OpenGLScene : public QGraphicsScene {
   Q_OBJECT
   public:
      OpenGLScene(ViewWindowQT* vwqt);
      ~OpenGLScene() { DEBUG_M("Cleaning up OpenGLScene");}
      void drawBackground(QPainter *painter, const QRectF &rect);
      void addOverlayedWidget(QWidget* widget, bool disableFrame = true, bool transparentBackground = true);
      ColladaRendererGL renderer_;
      void setSize(const int width, const int height);

   public slots:
      void editCollada();


   private:
      ViewWindowQT *vwqt_;
      shared_ptr<Grid> grid_;
      QTime time_;
      QWidget *editScene;
      QTEditColladas* newEditColladas;
      QWebView* htmlOverlay;
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
      OpenGLScene* getOpenGLScene();

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
