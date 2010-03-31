#include "../QTGui/QTEditGeneric.hpp"

#include "../Viewport/ViewWindowQT.hpp"

void QTEditGeneric::setOpenGLScene(OpenGLScene* openGLScene) {
   openGLScene_ = openGLScene;
}

void QTEditGeneric::edit() {
   DEBUG_M("Entering function...");
   if(childEditor_ && openGLScene_) {
      openGLScene_->addOverlayedWidget(childEditor_);
   } else {
      WARNING("Failed to add child editor window.");
   }
}

void QTEditGeneric::setChildEditor(QWidget* childEditor) {
   childEditor_ = childEditor;
}

QWidget* QTEditGeneric::getChildEditor() {
   return childEditor_;
}
