#ifndef COLLADACPP_SOURCE_HPP_
#define COLLADACPP_SOURCE_HPP_

#include "ColladaObject.hpp"

class Source: public ColladaObject {
   public:
      void setFloats(shared_ptr<vector<float>> floats) { floats_ = floats; }
      void setXOff(int xOffset) { xOffset_ = xOffset; }
      void setYOff(int yOffset) { yOffset_ = yOffset; }
      void setZOff(int zOffset) { zOffset_ = zOffset; }
      void setStride(int stride) { stride_ = stride; }
      int getStride() { return stride_; }

      float getX(int num) { return floats_->at(xOffset_ + (num * getStride())); }
      float getY(int num) { return floats_->at(yOffset_ + (num * getStride())); }
      float getZ(int num) { return floats_->at(zOffset_ + (num * getStride())); }

   private:
      shared_ptr<vector<float>> floats_;
      int xOffset_;
      int yOffset_;
      int zOffset_;
      int stride_;
};

#endif /* COLLADACPP_SOURCE_HPP_ */
