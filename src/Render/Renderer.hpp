#ifndef COLLADACPP_RENDERER_HPP_
#define COLLADACPP_RENDERER_HPP_

class Renderable;
class Collada;
class ColladaObject;
class Scene;
class VisualScene;
class ColladaNode;
class Position;
class RotationGL;
class Scale;
class Camera;
class Grid;
class Triangles;
class GeometricPrimitive;
class Geometry;
class InstanceGeometry;
class Material;
class Phong;
class Lambert;
class TestRenderable;
class ColladaLitShader;
class GameObject;
class Area;
class ColladaMesh;
class Octree;
class BlockChunk;
class GLSLShader;

class Renderer {
   public:
      Renderer();
      virtual void init();

      virtual void setCameraMatrix(Camera* camera) = 0;
      virtual void setSize(const int width, const int height) = 0;
      virtual void preFrame() = 0;
      virtual void postFrame() = 0;

      virtual void render(Renderable* renderable) = 0;
      virtual void render(GameObject* gameObject) = 0;
      virtual void render(ColladaMesh* colladaMesh) = 0;
      virtual void render(Area* area) = 0;
      virtual void render(Collada* collada) = 0;
      virtual void render(ColladaObject* colladaObject) = 0;
      virtual void render(Scene* scene) = 0;
      virtual void render(VisualScene* vs) = 0;
      virtual void render(ColladaNode* node) = 0;
      virtual void render(Position* position) = 0;
      virtual void render(RotationGL* rotation) = 0;
      virtual void render(Scale* scale) = 0;
      virtual void render(Camera* camera) = 0;
      virtual void render(Grid* grid) = 0;
      virtual void render(Geometry* geometry) = 0;
      virtual void render(InstanceGeometry* ig) = 0;
      virtual void render(GeometricPrimitive* prim) = 0;
      virtual void render(Triangles* triangles) = 0;
      virtual void render(Material* material) = 0;
      virtual void render(ColladaLitShader* lit) = 0;
      virtual void render(Phong* phong) = 0;
      virtual void render(Lambert* lambert) = 0;
      virtual void render(TestRenderable* tr) = 0;
      virtual void render(Octree* octree) = 0;
      virtual void render(BlockChunk* blockchunk) = 0;

   private:
      static void setInitState_(const bool initstate);
      static bool getInitState_();

      static bool initstate_;
};

#endif /* COLLADACPP_RENDERER_HPP_ */
