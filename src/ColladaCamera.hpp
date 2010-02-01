#ifndef COLLADACPP_COLLADACAMERA_HPP_
#define COLLADACPP_COLLADACAMERA_HPP_

class ColladaCamera : public ColladaObject {
   public:
      float getFov() const;
      void setFov(const float& fov);
      
      float getNear() const;
      void setNear(const float& near);

   private:
      float fov_;
      float near_;
      float far_;
};

float ColladaCamera::getFov() const {
   return fov_;
}

void ColladaCamera::setFov(const float& fov) {
   fov_ = fov;
}

float ColladaCamera::getNear() const {
   return near_;
}

void ColladaCamera::setNear(const float& near) {
   near_ = near;
}

#endif /* COLLADACPP_COLLADACAMERA_HPP_ */
