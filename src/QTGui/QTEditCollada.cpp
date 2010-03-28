#include "../QTGui/QTEditCollada.hpp"
#include "../Viewport/ViewWindowQT.hpp"

#include "../Debug/console.h"

QTEditCollada::QTEditCollada(shared_ptr<Collada> collada) {
   collada_ = collada;

   QPushButton* sceneButton_ = new QPushButton("Edit Scene");
   connect(sceneButton_, SIGNAL(clicked()), this, SLOT(editScene()));
   
   QLabel* filename = new QLabel(collada_->getFilename().c_str());

   setWindowTitle(tr("Collada"));

   QVBoxLayout *layout = new QVBoxLayout;
   layout->setMargin(5);
   layout->addWidget(filename);
   layout->addWidget(sceneButton_);
   setLayout(layout);
}

void QTEditCollada::editScene() {
   DEBUG_A("Oh boy, PANCAKES!");
   OpenGLScene* parent = (OpenGLScene*)parentWidget();
   QTEditCollada* newSceneEditTest = new QTEditCollada(collada_);
   //parent->addOverlayedWidget(newSceneEditTest);
}
