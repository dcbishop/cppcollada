#include "Renderer.hpp"

#include "../GameData/Globals.hpp"
#include "../GameObjects/Camera.hpp"
#include "../Debug/console.h"

bool Renderer::initstate_ = false;

Renderer::Renderer() {
   DEBUG_M("Created Renderer.");
   setInitState_(false);
   init();
}

void Renderer::init() {
   if(getInitState_()) {
      return;
   }
   DEBUG_M("Initilizing Renderer.");
   if(g.getRenderer() == NULL) {
      g.setRenderer(this);
      setInitState_(true);
   } else if(g.getRenderer() != this) {
      ERROR("Tried to create multiple renderers!");
   }
}

void Renderer::setInitState_(const bool initstate) {
   initstate_ = initstate;
};

bool Renderer::getInitState_() {
   return initstate_;
}
