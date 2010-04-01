#include "../QTGui/QTEditScene.hpp"
#include "../Viewport/ViewWindowQT.hpp"

#include "../Debug/console.h"

QTEditScene::QTEditScene(shared_ptr<Scene> scene) {
   scene_ = scene_;

   editButton = new QPushButton("Edit VisualScene");
   connect(editButton, SIGNAL(clicked()), this, SLOT(edit()));

   setWindowTitle(tr("Scene"));

   layout = new QVBoxLayout;
   layout->setMargin(5);
   layout->addWidget(editButton);
   setLayout(layout);
}

void QTEditScene::edit() {
   WARNING("STUB FUNCTION");
   //setChildEditor(new QTEditVisualScene(collada_->getScene()));
   //QTEditGeneric::edit();
}
