#ifndef COLLADACPP_COLLADARENDERERGL_HPP_
#define COLLADACPP_COLLADARENDERERGL_HPP_

#include "../Render/ColladaRenderer.hpp"
#include "../Collada/Phong.hpp"
#include "../Render/ColladaRendererGL_DevIL.hpp"

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
      virtual void render(Material* material);
      virtual void render(Phong* phong);
      virtual void preFrame();
      virtual void postFrame();
      virtual void init();
      virtual void setSize(const int width, const int height);
      int debugPrimDraw;

   private:
      void renderDefaultMaterial_();
      void fixAxis_(const Collada* collada);
      void renderAxis_();
      void setPerspective_();
      void setPolygonMode_();
      void setRenderMode_();
      void setUnlitMode_();
      void setLights_();


      Phong defaultMaterial_;
      int width_;
      int height_;
      ColladaRendererGL_DevIL imageLoader_;
};

#endif /* COLLADACPP_COLLADARENDERERGL_HPP_ */
