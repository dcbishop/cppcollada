#ifndef COLLADACPP_QTGUI_QTEDITCOLLADA_HPP_
#define COLLADACPP_QTGUI_QTEDITCOLLADA_HPP_

#include <QtGui>
#include "../Collada/Collada.hpp"
#include "../QTGui/QTEditGeneric.hpp"
#include "../QTGui/QTEditScene.hpp"

class QTEditCollada : public QTEditGeneric {
   Q_OBJECT

   public:
      QTEditCollada(shared_ptr<Collada> collada);

   public slots:
      void edit();

   private:
      shared_ptr<Collada> collada_;
      QPushButton* sceneButton_;
      QLabel* filenameLabel_;
};

#endif /* COLLADACPP_QTGUI_QTEDITCOLLADA_HPP_ */
