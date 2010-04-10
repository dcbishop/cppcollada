#ifndef COLLADACPP_QTGUI_QTCOLLADAOBJECTTREEITEM_HPP_
#define COLLADACPP_QTGUI_QTCOLLADAOBJECTTREEITEM_HPP_


#include <QtGui>
#include "../Collada/ColladaManager.hpp"

class QTColladaObjectTreeItem {
   public:
      QTColladaObjectTreeItem(ColladaObjectPtr co, QTColladaObjectTreeItem *parent = 0);
      ~QTColladaObjectTreeItem();

      void appendChild(QTColladaObjectTreeItem *child);

      QTColladaObjectTreeItem *child(int row);
      int childCount() const;
      int columnCount() const;
      QVariant data(int column) const;
      int row() const;
      QTColladaObjectTreeItem *parent();

      private:
         void setup_();
         QList<QTColladaObjectTreeItem*> childItems_;
         ColladaObjectPtr co_;
         QTColladaObjectTreeItem *parentItem_;
         QList<QVariant> itemData_;
};

#endif /* COLLADACPP_QTGUI_QTCOLLADAOBJECTTREEITEM_HPP_ */
