#ifndef COLLADACPP_QTGUI_TREEMODEL_HPP_
#define COLLADACPP_QTGUI_TREEMODEL_HPP_

#include <QtGui>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "../Collada/Collada.hpp"
#include "../Collada/ColladaManager.hpp"
#include "../QTGui/QTColladaObjectTreeItem.hpp"

class QTColladaObjectTreeItem;

class TreeModel : public QAbstractItemModel {
   Q_OBJECT

   public:
      TreeModel(ColladaManagerPtr cm, QObject *parent = 0);
      ~TreeModel();
      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
      int rowCount(const QModelIndex&) const;
      Qt::ItemFlags flags(const QModelIndex &index) const;
      QVariant data(const QModelIndex &index, int role) const;
      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
      QModelIndex parent(const QModelIndex &index) const;
      int columnCount(const QModelIndex &parent = QModelIndex()) const;

   private:
      QTColladaObjectTreeItem* rootItem_;
};

#endif /* COLLADACPP_QTGUI_TREEMODEL_HPP_ */
