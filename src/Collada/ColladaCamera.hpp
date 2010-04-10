#ifndef COLLADACPP_COLLADACAMERA_HPP_
#define COLLADACPP_COLLADACAMERA_HPP_

#warning ['TODO']: This isn't actually used yet...

#include "../GameData/SmartPointers.hpp"
#include "../Collada/ColladaObject.hpp"

class ColladaCamera : public ColladaObject {
   public:
      float getFov() const { return fov_; }
      void setFov(const float& fov) { fov_ = fov; }
      float getNear() const { return near_; }
      void setNear(const float& near) { near_ = near; }

   private:
      float fov_;
      float near_;
      float far_;
};
typedef shared_ptr<ColladaCamera> ColladaCameraPtr;

#endif /* COLLADACPP_COLLADACAMERA_HPP_ */
