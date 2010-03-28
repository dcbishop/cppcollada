#ifndef COLLADACPP_QTGUI_QTEDITCOLLADA_HPP_
#define COLLADACPP_QTGUI_QTEDITCOLLADA_HPP_

#include <QtGui>
#include "../Collada/Collada.hpp"

class QTEditCollada : public QDialog {
   Q_OBJECT

   public:
      QTEditCollada(shared_ptr<Collada> collada);

   public slots:
      void editScene();

   private:
      shared_ptr<Collada> collada_;
};

#endif /* COLLADACPP_QTGUI_QTEDITCOLLADA_HPP_ */
