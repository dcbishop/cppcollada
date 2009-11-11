#ifndef COLLADACPP_COLLADAINSTANCE_HPP_
#define COLLADACPP_COLLADAINSTANCE_HPP_


class ColladaObject;

typedef void Material;

class ColladaInstance {
   public:
      void setInstance(ColladaObject* colladaObject);
      void bindMaterial(Material* material);

   private
      ColladaObject* colladaObject;
      Material* material_;
}

void ColladaInstance::bindMaterial(Material* material) {
   material_ = material;
}

#endif /* COLLADACPP_COLLADAINSTANCE_HPP_ */
