#include "../QTGui/QTEditCollada.hpp"

#include "../Viewport/ViewWindowQT.hpp"
#include "../Debug/console.h"

QTEditCollada::QTEditCollada(shared_ptr<Collada> collada) {
   collada_ = collada;

   sceneButton_ = new QPushButton("Edit Scene");
   connect(sceneButton_, SIGNAL(clicked()), this, SLOT(edit()));
   
   filenameLabel_ = new QLabel(collada_->getFilename().c_str());
   //tree_ = new QTreeView();
   //model_ = new TreeModel(collada_);
   //tree_->setModel(model_);


   setWindowTitle(tr("Collada"));

   QVBoxLayout *layout = new QVBoxLayout;
   layout->setMargin(5);
   layout->addWidget(filenameLabel_);
   //layout->addWidget(tree_);
   layout->addWidget(sceneButton_);
   setLayout(layout);
}

void QTEditCollada::edit() {
   DEBUG_A("Oh boy, PANCAKES! %p");
   if(!collada_) {
      ERROR("Collada edit window with no collada attached...");
      return;
   }

   setChildEditor(new QTEditScene(collada_->getScene()));
   QTEditGeneric::edit();
}
