#ifndef COLLADACPP_SOURCE_HPP_
#define COLLADACPP_SOURCE_HPP_

#include "SmartPointers.hpp"

#include "ColladaObject.hpp"

#include "console.h"

class Source: public ColladaObject {
   public:
      void setFloats(shared_ptr<vector<float>> floats) {
         DEBUG_H("%s.setFloats()", getId().c_str());
         DEBUG_H("floats = %p", floats.get());
         floats_ = floats;
         if(!floats_) {
            WARNING("Setting of floats screwed up");
         } else {
            DEBUG_H("Setting of floats successful %f.", floats->at(2));
         }
         
      }
      void setXOff(int xOffset) { xOffset_ = xOffset; }
      void setYOff(int yOffset) { yOffset_ = yOffset; }
      void setZOff(int zOffset) { zOffset_ = zOffset; }
      void setStride(int stride) { stride_ = stride; }
      int getStride() { return stride_; }

      virtual float getXPos(int num) { return floats_->at(xOffset_ + (num * getStride())); }
      virtual float getYPos(int num) { return floats_->at(yOffset_ + (num * getStride())); }
      virtual float getZPos(int num) { return floats_->at(zOffset_ + (num * getStride())); }

   private:
      shared_ptr<vector<float>> floats_;
      int xOffset_;
      int yOffset_;
      int zOffset_;
      int stride_;
};

#endif /* COLLADACPP_SOURCE_HPP_ */
