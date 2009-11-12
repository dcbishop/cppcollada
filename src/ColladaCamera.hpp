#ifndef COLLADACPP_COLLADACAMERA_HPP_
#define COLLADACPP_COLLADACAMERA_HPP_

class ColladaCamera {
   public:
      float getFov();
      void setFov(float fov);
      
      float getNear();
      void setNear(float near);

   private:
      float fov_;
      float near_;
      float far_;
};

float ColladaCamera::getFov() {
   return fov_;
}

void ColladaCamera::setFov(float fov) {
   fov_ = fov;
}

float ColladaCamera::getNear() {
   return near_;
}

void ColladaCamera::setNear(float near) {
   near_ = near;
}

#endif /* COLLADACPP_COLLADACAMERA_HPP_ */
