#ifndef COLLADACPP_GAMEDATA_CONTROLLER_HPP_
#define COLLADACPP_GAMEDATA_CONTROLLER_HPP_

enum {
   IS_MOVING_FORWARD,
   IS_MOVING_BACKWARD,
   IS_MOVING_LEFT,
   IS_MOVING_RIGHT,
   IS_MOVING_UP,
   IS_MOVING_DOWN,
   
   IS_PITCHING_UP,
   IS_PITCHING_DOWN,
   IS_YAWING_LEFT,
   IS_YAWING_RIGHT,
   IS_ROLLING_LEFT,
   IS_ROLLING_RIGHT
};
const int MAX_FLAGS = 12;

/*
 * TODO: Make some kind of a bridge for applying physics rather than
 * editing values directly here.
 * 
 * TODO: Work out the best way to seperate the 'rotation' component.
 * Currently it's considered a 'camera' which only works for 3rd person
 * but in a space ship it would rotate the whole ship and a FPS would
 * rotate the camera up/down but rotate the body left/right around the
 * worlds Y-Axis.
 * 
 * TODO: Some kind of way to interface with the UI. For example popup
 * menu on ESC. Possibly a 'global' controller that sits about this one.
 * 
 * TODO: Named bindings for setting custom inputs at runtime.
 * 
 * TODO: Non-direct controlling systems. Clicking on the ground to
 * move a unit their.
 */
 
#include <math.h>

#include "../GameData/Updateable.hpp"
#include "../GameObjects/Camera.hpp"

#include "../Debug/console.h"

class Controller;
typedef shared_ptr<Controller> ControllerPtr;

class Controller : public Updateable {
   public:
      Controller() {
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

      /**
       * Sets a flag indicating that the controller is in a mode.
       * The appropriate action should be applied to the controlled object in the update function.
       */
      void setFlag(const int flag, const bool value) {
         if(flag < 0 || flag > MAX_FLAGS);
         flags_[flag] = value;
      }

      /**
       * Tells the controlled object if it should be moving forward.
       * Default Key: W / Up Arrow.
       * May result in:
       * Accelerating a car.
       * A bipedal humanoid taking steps forward.
       * Forward thrusters on a spacecraft.
       */
      void setIsMovingForward(const bool value) {
         setFlag(IS_MOVING_FORWARD, value);
      }

      /**
       * Tells the controlled object if it should be moving backward.
       * Default Key: S / Down Arrow.
       * May result in:
       * Breaking and then reversing a car.
       * A bipedal humanoid taking steps backwards.
       * Reverse thrusters on a spacecraft.
       */
      void setIsMovingBackward(const bool value) {
         setFlag(IS_MOVING_BACKWARD, value);
      }

      /**
       * Tells the controlled object if it should be moving left.
       * Default Key: A / Left Arrow.
       * May result in:
       * Turning the wheels left on a car.
       * A bipedal humanoid strafing left.
       * Left thrusters on a spacecraft.
       */
      void setIsMovingLeft(const bool value) {
         setFlag(IS_MOVING_LEFT, value);
      }

      /**
       * Tells the controlled object if it should be moving right.
       * Default Key: D / Right Arrow.
       * May result in:
       * Turning the wheels right on a car.
       * A bipedal humanoid strafing right.
       * Right thrusters on a spacecraft.
       */
      void setIsMovingRight(const bool value) {
         setFlag(IS_MOVING_RIGHT, value);
      }

      /**
       * Tells the controlled object if it should be moving up.
       * Default Key: Spacebar.
       * May result in:
       * No action on a car.
       * A bipedal humanoid jumping. Or swiming towards the surface if in water.
       * Up thrusters on a spacecraft.
       */
      void setIsMovingUp(const bool value) {
         setFlag(IS_MOVING_UP, value);
      }

      /**
       * Tells the controlled object if it should be moving down.
       * Default Key: Ctrl.
       * May result in:
       * No action on a car.
       * A bipedal humanoid crouching. Or swiming away from the surface if in water.
       * Down thrusters on a spacecraft.
       */
      void setIsMovingDown(const bool value) {
         setFlag(IS_MOVING_DOWN, value);
      }

      /**
       * Tells the controlled object if it should be pitching up.
       * NOTE: Normally this would be done via an analog controller that inputs the values directly.
       * May result in:
       * Orbiting a 3rd person camera more overhead.
       * Looking the head up towards the sky/celing in first person.
       * Turning a spacecraft up relative to it's rotation.
       */
      void setIsPitchingUp(const bool value) {
         setFlag(IS_PITCHING_UP, value);
      }

      /**
       * Tells the controlled object if it should be pitching down.
       * NOTE: Normally this would be done via an analog controller that inputs the values directly.
       * May result in:
       * Orbiting a 3rd person camera closer to the ground.
       * Turning the head down towards the ground in first person.
       * Turning a spacecraft down relative to it's rotation.
       */
      void setIsPitchingDown(const bool value) {
         setFlag(IS_PITCHING_DOWN, value);
      }

      /**
       * Tells the controlled object if it should be yawing left.
       * NOTE: Normally this would be done via an analog controller that inputs the values directly.
       * May result in:
       * Orbiting a 3rd person camera left around the Y-axis of its tracked object.
       * Turning the player's body left around the worlds Y-axis in first person.
       * Turning a spacecraft left relative to it's rotation.
       */
      void setIsYawingLeft(const bool value) {
         setFlag(IS_YAWING_LEFT, value);
      }

      /**
       * Tells the controlled object if it should be yawing right.
       * NOTE: Normally this would be done via an analog controller that inputs the values directly.
       * May result in:
       * Orbiting a 3rd person camera right around the Y-axis of its tracked object.
       * Turning the player's body left around the worlds Y-axis in first person.
       * Turning a spacecraft left relative to it's rotation.
       */
      void setIsYawingRight(const bool value) {
         setFlag(IS_YAWING_RIGHT, value);
      }

      /**
       * Tells the controlled object if it should be rolling left.
       * May result in:
       * No action for a car/3rd person camera.
       * A bipedal humanoid leaning left.
       * Rotating a spacecraft left.
       */
      void setIsRollingLeft(const bool value) {
         setFlag(IS_ROLLING_LEFT, value);
      }

      /**
       * Tells the controlled object if it should be rolling right.
       * May result in:
       * No action for a car/3rd person camera.
       * A bipedal humanoid leaning right.
       * Rotating a spacecraft right.
       */
      void setIsRollingRight(const bool value) {
         setFlag(IS_ROLLING_RIGHT, value);
      }

      /**
       * Tells the controlled object if it should be performing an action.
       * Actions are indexed begining at 1.
       * 
       * May result in:
       * [Action 1] Primary Action - Default: Mouse 1.
       * Honking a horn.
       * Pulling a handgun's trigger.
       * Firing ze lasers.
       * 
       * [Action 2] Secondary Action - Default: Mouse 2.
       * Handbreak.
       * Aim mode.
       * Firing the missles.
       * 
       * [Action 3] 'Quick' Action - Default: Mouse 3.
       * Melee attack.
       * Throw grenade.
       * Change fire mode.
       * 
       * [Action 4] 'Use' Action - Default: E (if no leaning/roll ability) or F.
       * Open a door.
       * Pull a lever.
       * Push a switch.
       * 
       * Other ideas: Flashlight, Reload, Throw Grenade, Open Map, 
       *              Open Inventory, Open Journal. Change fire mode,
       *              Quick swap weapons, thermal vision.
       */
      void setAction(const int index, const bool value) {
         if(index < 1 || index > 10) {
            return;
         }
         isAction_[index-1] = value;
      }

      // Instantly applied inputs.
      /**
       * Adds or subtracts from the yaw value.
       */
      void addYaw(const float value) {
         if(isAction_[0] || getCamera()->getZoom() <= 0.1) {
            camera_->setRotX(camera_->getRotX() + value);
            controlled_->setRotationGL(0, 0, 1.0, 0, -camera_->getRotX());
         }
      }

      /**
       * Adds or subtracts from the pitch value.
       */
      void addPitch(const float value) {
         if(isAction_[0] || getCamera()->getZoom() <= 0.1) {
            camera_->setRotY(camera_->getRotY() - value);
         }
      }

      /**
       * Adds or subtracts from the roll value.
       */
      void addRoll(const float value) {
         return;
      }

      /**
       * A generic incrementing function.
       * Default: Mouse Wheel +, '=' key.
       * 
       * May result in:
       * Movinging a 3rd person camera closer to the target.
       * Selecting the next weapon/item.
       * Zooming a scope in.
       */
      void Increment() {
         getCamera()->setZoom(getCamera()->getZoomTarget() - ZOOM_STEP);
      }

      /**
       * A generic incrementing function.
       * Default: Mouse Wheel +, '=' key.
       * 
       * May result in:
       * Movinging a 3rd person camera away from the target.
       * Selecting the previous weapon/item.
       * Zooming a scope out.
       */
      void Decrement() {
         getCamera()->setZoom(getCamera()->getZoomTarget() + ZOOM_STEP);
      }

      /**
       * Sets the object to move.
       */
      void setControlled(GameObjectPtr controlled) {
         controlled_ = controlled;
      }

      /**
       * Sets the object to rotate.
       */      
      void setCamera(CameraPtr camera) {
         camera_ = camera;
      }

      CameraPtr getCamera() const {
         return camera_;
      }

      void Update(const float dt) {
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

   private:
      bool flags_[MAX_FLAGS];

      // Default speeds in m/s
      float defaultForwardSpeed_;
      float defaultBackwardSpeed_;
      float defaultMoveLeftSpeed_;
      float defaultMoveRightSpeed_;
      float defaultMoveUpSpeed_;
      float defaultMoveDownSpeed_;

      // Actions.
      bool isAction_[9];

      GameObjectPtr controlled_;
      CameraPtr camera_;
};

#endif /* COLLADACPP_GAMEDATA_CONTROLLER_HPP_ */
