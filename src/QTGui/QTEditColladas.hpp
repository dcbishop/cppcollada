#ifndef COLLADACPP_QTGUI_QTEDITCOLLADAS_HPP_
#define COLLADACPP_QTGUI_QTEDITCOLLADAS_HPP_

#include <QtGui>
#include "../Collada/Collada.hpp"
#include "../Collada/ColladaManager.hpp"
#include "../QTGui/QTEditGeneric.hpp"
#include "../QTGui/QTEditScene.hpp"
#include "../QTGui/TreeModel.hpp"

class QTEditColladas : public QTEditGeneric {
   Q_OBJECT

   public:
      QTEditColladas(ColladaManagerPtr cm);

   public slots:
      void edit();

   private:
      ColladaManagerPtr cm_;
      //QPushButton* sceneButton_;
      QLabel* filenameLabel_;
      QTreeView* tree_;
      TreeModel* model_;
};

#endif /* COLLADACPP_QTGUI_QTEDITCOLLADAS_HPP_ */
