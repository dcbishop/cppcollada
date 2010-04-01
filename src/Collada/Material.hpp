#ifndef COLLADACPP_MATERIAL_HPP_
#define COLLADACPP_MATERIAL_HPP_

#include "../Collada/ColladaObject.hpp"
#include "../Collada/Effect.hpp"

class Material : public ColladaObject {
   public:
      COLLADA_RENDER_FUNCTION
      void setEffect(shared_ptr<Effect> effect) { effect_ = effect; }
      shared_ptr<Effect> getEffect() { return effect_; }

   private:
      shared_ptr<Effect> effect_;
};
typedef shared_ptr<Material> MaterialPtr;


#endif /* COLLADACPP_MATERIAL_HPP_ */

