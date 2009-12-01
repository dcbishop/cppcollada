#ifndef COLLADACPP_MATERIAL_HPP_
#define COLLADACPP_MATERIAL_HPP_

#include "ColladaObject.hpp"
#include "Effect.hpp"

class Material : public ColladaObject {
   public:
      void setEffect(shared_ptr<Effect> effect) { effect_ = effect; }
   private:
      shared_ptr<Effect> effect_;
};

#endif /* COLLADACPP_MATERIAL_HPP_ */

