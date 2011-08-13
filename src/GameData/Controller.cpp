#include "../GameData/Controller.hpp"

Controller::Controller() {
   defaultForwardSpeed_ = 3.0f;
   defaultBackwardSpeed_ = defaultForwardSpeed_;
   defaultMoveLeftSpeed_ = defaultForwardSpeed_;
   defaultMoveRightSpeed_ = defaultForwardSpeed_;
   defaultMoveUpSpeed_ = defaultForwardSpeed_;
   defaultMoveDownSpeed_ = defaultForwardSpeed_;
   
   for(int i = 0; i < MAX_FLAGS; i++) {
      setFlag(i, false);
   }
   // TODO: Set Actions
}

void Controller::setFlag(const int flag, const bool value) {
   if(flag < 0 || flag > MAX_FLAGS);
   flags_[flag] = value;
}

void Controller::setIsMovingForward(const bool value) {
   setFlag(IS_MOVING_FORWARD, value);
}

void Controller::setIsMovingBackward(const bool value) {
   setFlag(IS_MOVING_BACKWARD, value);
}

void Controller::setIsMovingLeft(const bool value) {
   setFlag(IS_MOVING_LEFT, value);
}

void Controller::setIsMovingRight(const bool value) {
   setFlag(IS_MOVING_RIGHT, value);
}

void Controller::setIsMovingUp(const bool value) {
   setFlag(IS_MOVING_UP, value);
}

void Controller::setIsMovingDown(const bool value) {
   setFlag(IS_MOVING_DOWN, value);
}

void Controller::setIsPitchingUp(const bool value) {
   setFlag(IS_PITCHING_UP, value);
}

void Controller::setIsPitchingDown(const bool value) {
   setFlag(IS_PITCHING_DOWN, value);
}

void Controller::setIsYawingLeft(const bool value) {
   setFlag(IS_YAWING_LEFT, value);
}

void Controller::setIsYawingRight(const bool value) {
   setFlag(IS_YAWING_RIGHT, value);
}

void Controller::setIsRollingLeft(const bool value) {
   setFlag(IS_ROLLING_LEFT, value);
}

void Controller::setIsRollingRight(const bool value) {
   setFlag(IS_ROLLING_RIGHT, value);
}

void Controller::setAction(const int index, const bool value) {
   if(index < 1 || index > 10) {
      return;
   }
   isAction_[index-1] = value;
}

void Controller::addYaw(const float value) {
   if(isAction_[0] || getCamera()->getZoom() <= 0.1) {
      camera_->setRotX(camera_->getRotX() + value);
      controlled_->setRotationGL(0, 0, 1.0, 0, -camera_->getRotX());
   }
}

void Controller::addPitch(const float value) {
   if(isAction_[0] || getCamera()->getZoom() <= 0.1) {
      camera_->setRotY(camera_->getRotY() - value);
   }
}

void Controller::addRoll(const float value) {
   return;
}

void Controller::Increment() {
   getCamera()->setZoom(getCamera()->getZoomTarget() - ZOOM_STEP);
}

void Controller::Decrement() {
   getCamera()->setZoom(getCamera()->getZoomTarget() + ZOOM_STEP);
}

void Controller::setControlled(GameObjectPtr controlled) {
   controlled_ = controlled;
}
     
void Controller::setCamera(CameraPtr camera) {
   camera_ = camera;
}

CameraPtr Controller::getCamera() const {
   return camera_;
}

void Controller::Update(const float dt) {
   if(flags_[IS_MOVING_FORWARD]) {
      controlled_->setX(controlled_->getX() + cos(camera_->getRotX()*(PI/180)) * (-defaultForwardSpeed_ * dt));
      controlled_->setZ(controlled_->getZ() + sin(camera_->getRotX()*(PI/180)) * (-defaultForwardSpeed_ * dt));
   }
   if(flags_[IS_MOVING_BACKWARD]) {
      controlled_->setX(controlled_->getX() + cos(camera_->getRotX()*(PI/180)) * (defaultBackwardSpeed_ * dt));
      controlled_->setZ(controlled_->getZ() + sin(camera_->getRotX()*(PI/180)) * (defaultBackwardSpeed_ * dt));
   }
   if(flags_[IS_MOVING_LEFT]) {
      controlled_->setX(controlled_->getX() - sin(camera_->getRotX()*(PI/180)) * (defaultMoveLeftSpeed_ * dt));
      controlled_->setZ(controlled_->getZ() + cos(camera_->getRotX()*(PI/180)) * (defaultMoveLeftSpeed_ * dt));
   }
   if(flags_[IS_MOVING_RIGHT]) {
      controlled_->setX(controlled_->getX() - sin(camera_->getRotX()*(PI/180)) * (-defaultMoveRightSpeed_ * dt));
      controlled_->setZ(controlled_->getZ() + cos(camera_->getRotX()*(PI/180)) * (-defaultMoveRightSpeed_ * dt));
   }
   if(flags_[IS_MOVING_UP]) {
      controlled_->setY(controlled_->getY() + (defaultMoveUpSpeed_ * dt));
   }
   if(flags_[IS_MOVING_DOWN]) {
      controlled_->setY(controlled_->getY() - (defaultMoveDownSpeed_ * dt));
   }
}
