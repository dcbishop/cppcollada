#ifndef COLLADACPP_COLLADARENDERERGL_HPP_
#define COLLADACPP_COLLADARENDERERGL_HPP_



#include "ColladaRenderer.hpp"

class ColladaRendererGL : public ColladaRenderer {
   public:
      virtual void render(Renderable* renderable);
      virtual void render(Collada* collada);
      virtual void render(ColladaObject* colladaObject);
      virtual void render(Scene* scene);
      virtual void render(VisualScene* vs);
      virtual void render(ColladaNode* node);
      virtual void render(Position* position);
      virtual void render(RotationGL* rotation);
      virtual void render(Scale* scale);
};

#endif /* COLLADACPP_COLLADARENDERERGL_HPP_ */
