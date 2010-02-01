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
      virtual void render(Camera* camera);
      virtual void render(Grid* grid);
      virtual void render(Geometry* geometry);
      virtual void render(InstanceGeometry* ig);
      virtual void render(GeometricPrimitive* geometry);
      virtual void render(Triangles* triangles);

   private:
      void fixAxis_(const Collada* collada);
      void renderAxis_();
      void debugRotationHack(const Collada* collada);

};

#endif /* COLLADACPP_COLLADARENDERERGL_HPP_ */
