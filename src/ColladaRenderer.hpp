#ifndef COLLADACPP_COLLADARENDERER_HPP_
#define COLLADACPP_COLLADARENDERER_HPP_

class Renderable;
class Collada;
class ColladaObject;
class Scene;
class VisualScene;
class ColladaNode;
class Position;
class RotationGL;
class Scale;

class ColladaRenderer {
   public:
      virtual void render(Renderable* renderable) = 0;
      virtual void render(Collada* collada) = 0;
      virtual void render(ColladaObject* colladaObject) = 0;
      virtual void render(Scene* scene) = 0;
      virtual void render(VisualScene* vs) = 0;
      virtual void render(ColladaNode* node) = 0;
      virtual void render(Position* position) = 0;
      virtual void render(RotationGL* rotation) = 0;
      virtual void render(Scale* scale) = 0;
};

#endif /* COLLADACPP_COLLADARENDERER_HPP_ */
