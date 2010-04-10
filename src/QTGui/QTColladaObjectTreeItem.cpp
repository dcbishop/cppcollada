#include "../QTGui/QTColladaObjectTreeItem.hpp"

#include "../Collada/Scene.hpp"
#include "../Collada/ColladaNode.hpp"
#include "../Collada/InstanceGeometry.hpp"


#include "../Debug/console.h"

QTColladaObjectTreeItem::QTColladaObjectTreeItem(const ColladaObjectPtr co, QTColladaObjectTreeItem *parent) {
   parentItem_ = parent;
   co_ = co;
   setup_();
}

QTColladaObjectTreeItem::~QTColladaObjectTreeItem() {
  qDeleteAll(childItems_);
}

void QTColladaObjectTreeItem::appendChild(QTColladaObjectTreeItem *item) {
   childItems_.append(item);
}

QTColladaObjectTreeItem* QTColladaObjectTreeItem::child(int row) {
   return childItems_.value(row);
}

int QTColladaObjectTreeItem::childCount() const {
   return childItems_.count();
}

int QTColladaObjectTreeItem::row() const {
   if (parentItem_) {
      return parentItem_->childItems_.indexOf(const_cast<QTColladaObjectTreeItem*>(this));
   }

   return 0;
}

int QTColladaObjectTreeItem::columnCount() const {
   return 1;
   //return itemData_.count();
}

QTColladaObjectTreeItem *QTColladaObjectTreeItem::parent() {
   return parentItem_;
}

void QTColladaObjectTreeItem::setup_() {
   ColladaManagerPtr cm = dynamic_pointer_cast<ColladaManager, ColladaObject>(co_);
   if(cm.get()) {
      DEBUG_M("It was a ColladaManager");
      ColladaMap* cmap = cm->getColladaMap();
      itemData_ << "Collada Files...";
      for(ColladaMapIterator cmapIter = cmap->begin(); cmapIter != cmap->end(); cmapIter++) {
         DEBUG_M("adding child");
         appendChild(new QTColladaObjectTreeItem(cmapIter->second, this));
      }
      return;
   }

   ColladaPtr collada = dynamic_pointer_cast<Collada, ColladaObject>(co_);
   if(collada.get()) {
      itemData_ << string("<collada>: " + collada->getFilename()).c_str();
      DEBUG_M("It was a Collada");
      ScenePtr scene = collada->getScene();
      appendChild(new QTColladaObjectTreeItem(scene, this));
      return;
   }
   
   ScenePtr scene = dynamic_pointer_cast<Scene, ColladaObject>(co_);
   if(scene.get()) {
      DEBUG_M("It was a Scene");
      itemData_ << "<scene>";
      for(VisualSceneIterator vsi = scene->getFirstVisualScene(); vsi != scene->getEndVisualScene(); vsi++) {
         appendChild(new QTColladaObjectTreeItem((*vsi), this));
      }
      return;
   }
   
   VisualScenePtr vs = dynamic_pointer_cast<VisualScene, ColladaObject>(co_);
   if(vs.get()) {
      itemData_ << string("<visual_scene id=\"" + vs->getId() + "\" name=\"" + vs->getName() + "\">" ).c_str();
      for(ColladaNodeIterator cni = vs->getFirstColladaNode(); cni != vs->getEndColladaNode(); cni++) {
         appendChild(new QTColladaObjectTreeItem((*cni), this));
      }
      return;
   }
   
   ColladaNodePtr node = dynamic_pointer_cast<ColladaNode, ColladaObject>(co_);
   if(node.get()) {
      itemData_ << string("<node id=\"" + node->getId() + "\" name=\"" + node->getName() + "\">").c_str();
      for(InstanceIterator ii = node->getFirstInstance(); ii != node->getEndInstance(); ii++) {
         appendChild(new QTColladaObjectTreeItem((*ii), this));
      }
      return;
   }

   InstanceGeometryPtr ig = dynamic_pointer_cast<InstanceGeometry, ColladaObject>(co_);
   if(ig.get()) {
      itemData_ << "<instance_geometry>";
      // Loop through materials and append
      // Append geometry
      for(MaterialMapIterator mmi = ig->getFirstMaterial(); mmi != ig->getEndMaterial(); mmi++) {
         appendChild(new QTColladaObjectTreeItem((*mmi).second, this));
      }
      appendChild(new QTColladaObjectTreeItem(ig->getGeometry(), this));
      return;
   }

   GeometryPtr geo = dynamic_pointer_cast<Geometry, ColladaObject>(co_);
   if(geo.get()) {
      itemData_ << string("<geometry id=\"" + geo->getId() + "\" name=\"" + geo->getName() + "\">").c_str();
      // TODO: Add sub items
      return;
   }

   MaterialPtr mat = dynamic_pointer_cast<Material, ColladaObject>(co_);
   if(mat.get()) {
      itemData_ << string("<material id=\"" + mat->getId() +"\" name=\"" + mat->getName() + "\">").c_str();
      // TODO: Add sub items
      return;
   }

   itemData_ << string("UNKNOWN: id=\"" + co_->getId() + "\" name=\"" + co_->getName() + "\"").c_str();

   DEBUG_M("Done here");
}

QVariant QTColladaObjectTreeItem::data(int column) const {
   return itemData_.value(column);  
}
