#ifndef COLLADACPP_QTGUI_QTEDITSCENE_HPP_
#define COLLADACPP_QTGUI_QTEDITSCENE_HPP_

#include <QtGui>
#include "../Collada/Collada.hpp"
#include "../QTGui/QTEditGeneric.hpp"

class QTEditScene : public QTEditGeneric {
   Q_OBJECT

   public:
      QTEditScene(ScenePtr scene);

   public slots:
      void edit();

   private:
      ScenePtr scene_;
      QPushButton* editButton;
      QVBoxLayout *layout;
};

#endif /* COLLADACPP_QTGUI_QTEDITSCENE_HPP_ */
