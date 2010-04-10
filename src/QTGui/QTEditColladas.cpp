#include "../QTGui/QTEditColladas.hpp"

#include "../Viewport/ViewWindowQT.hpp"
#include "../Debug/console.h"

QTEditColladas::QTEditColladas(ColladaManagerPtr cm) {
   cm_ = cm;

   //sceneButton_ = new QPushButton("Edit Scene");
   //connect(sceneButton_, SIGNAL(clicked()), this, SLOT(edit()));
   
   //filenameLabel_ = new QLabel(collada_->getFilename().c_str());
   filenameLabel_ = new QLabel("Edit COLLADAs.");
   tree_ = new QTreeView();
   model_ = new TreeModel(cm_);
   tree_->setModel(model_);


   setWindowTitle(tr("Collada"));

   QVBoxLayout *layout = new QVBoxLayout;
   layout->setMargin(5);
   layout->addWidget(filenameLabel_);
   layout->addWidget(tree_);
   //layout->addWidget(sceneButton_);
   setLayout(layout);
}

void QTEditColladas::edit() {
   DEBUG_A("Oh boy, PANCAKES! %p");
   if(!cm_.get()) {
      ERROR("Collada edit window with no collada attached...");
      return;
   }

   //setChildEditor(new QTEditScene(collada_->getScene()));
   //QTEditGeneric::edit();
   WARNING("STUB FUNCTION");
}
