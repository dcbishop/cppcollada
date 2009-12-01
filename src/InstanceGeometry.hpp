#ifndef COLLADACPP_INSTANCEGEOMETRY_HPP_
#define COLLADACPP_INSTANCEGEOMETRY_HPP_

class InstanceGeometry {
   public:
      void bindMaterial(shared_ptr<Material> material) {material_ = material;}

   private:
      shared_ptr<Material> material_;
};

#endif /* COLLADACPP_INSTANCEGEOMETRY_HPP_ */
