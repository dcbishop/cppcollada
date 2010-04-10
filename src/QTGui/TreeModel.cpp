#include "../QTGui/TreeModel.hpp"
#include "../Debug/console.h"

TreeModel::TreeModel(ColladaManagerPtr cm, QObject *parent) : QAbstractItemModel(parent) {
   DEBUG_M("TreeModel");
   //QList<QVariant> rootData;
   //rootData_ << "TESTA" << "TESTB";
   rootItem_ = new QTColladaObjectTreeItem(cm);
}

TreeModel::~TreeModel() {
   DEBUG_M("~TreeModel");
   delete(rootItem_);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
   if(!hasIndex(row, column, parent)) {
      return QModelIndex();
   }

   QTColladaObjectTreeItem *parentItem;
   if (!parent.isValid()) {
      parentItem = rootItem_;
   } else {
      parentItem = static_cast<QTColladaObjectTreeItem*>(parent.internalPointer());
   }

   QTColladaObjectTreeItem *childItem = parentItem->child(row);
   if (childItem) {
      return createIndex(row, column, childItem);
   } else {
      return QModelIndex();
   }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
   if(!index.isValid()) {
      return QModelIndex();
   }

   QTColladaObjectTreeItem *childItem = static_cast<QTColladaObjectTreeItem*>(index.internalPointer());
   QTColladaObjectTreeItem *parentItem = childItem->parent();

   if(parentItem == rootItem_) {
      return QModelIndex();
   }

   return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
   QTColladaObjectTreeItem *parentItem;
   if(parent.column() > 0) {
      return 0;
   }

   if(!parent.isValid()) {
      parentItem = rootItem_;
   } else {
      parentItem = static_cast<QTColladaObjectTreeItem*>(parent.internalPointer());
   }

   return parentItem->childCount();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
   if (!index.isValid()) {
      return 0;
   }

   return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
   if (role != Qt::DisplayRole) {
      return QVariant();
   }

   if (!index.isValid()) {
      return QVariant();
   }

   QTColladaObjectTreeItem *item = static_cast<QTColladaObjectTreeItem*>(index.internalPointer());
   return item->data(index.column());
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
      return rootItem_->data(section);
   }

   return QVariant();
}

int TreeModel::columnCount(const QModelIndex &parent) const {
   if (parent.isValid()) {
      return static_cast<QTColladaObjectTreeItem*>(parent.internalPointer())->columnCount();
   } else {
      return rootItem_->columnCount();
   }
}
