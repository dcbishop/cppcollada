#ifndef COLLADACPP_QTGUI_QTEDITGENERIC_HPP_
#define COLLADACPP_QTGUI_QTEDITGENERIC_HPP_

#include <QtGui>
class OpenGLScene;

class QTEditGeneric : public QDialog {
   Q_OBJECT

   public:
      void setOpenGLScene(OpenGLScene* openGLScene);
      void setChildEditor(QWidget* childEditor);
      QWidget* getChildEditor();

   public slots:
      virtual void edit();
      
   protected:
      OpenGLScene* openGLScene_;

   private:
      QWidget* childEditor_; /* Tempory store to ensure that ViewWindowQT has something to grab */

};

#endif /* COLLADACPP_QTGUI_QTEDITGENERIC_HPP_ */
