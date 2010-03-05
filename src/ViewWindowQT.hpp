#ifndef COLLADACPP_VIEWWINDOWQT_HPP_
#define COLLADACPP_VIEWWINDOWQT_HPP_

class Collada;

#include <string>
using namespace std;

#include "ViewWindow.hpp"

#include "SmartPointers.hpp"
#include "ColladaRendererGL.hpp"
#include "Renderable.hpp"
class Grid;

#include <QtGui>
#include <QtOpenGL>

class ViewWindowQT;

/**
 * A Simple window for viewing models in.
 */
class ViewWindowQT: public ViewWindow {
   // http://doc.trolltech.com/4.6/qglwidget.html#details
   class ViewWidget: public QGLWidget {
      //Q_OBJECT
      public:
         ViewWidget(ViewWindowQT* vwqt);
         void initializeGL();
         void resizeGL(int width, int heigh);
         void paintGL();
         ColladaRendererGL renderer_;
         void mouseMoveEvent (QMouseEvent* event);

      private:
         ViewWindowQT *vwqt_;
         shared_ptr<Grid> grid_;
   };

   public:
      ViewWindowQT(const int width, const int height);
      ~ViewWindowQT();
      virtual ColladaRenderer* getRenderer();
      virtual void setTitle(const string title);
      virtual void mainLoop();

   private:
      QApplication *app_;
      ViewWidget *vw_;
      bool finished_;
      int mx_, my_;
      bool cam_move_;
};

#endif /* COLLADACPP_VIEWWINDOWQT_HPP_ */
