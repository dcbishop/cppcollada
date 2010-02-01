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
      inline void setXOff(const int& xOffset) { xOffset_ = xOffset; }
      inline void setYOff(const int& yOffset) { yOffset_ = yOffset; }
      inline void setZOff(const int& zOffset) { zOffset_ = zOffset; }
      inline void setStride(const int& stride) { stride_ = stride; }
      inline int getStride() const { return stride_; }

      inline virtual float getXPos(const int& num) const { return floats_->at(xOffset_ + (num * getStride())); }
      inline virtual float getYPos(const int& num) const { return floats_->at(yOffset_ + (num * getStride())); }
      inline virtual float getZPos(const int& num) const { return floats_->at(zOffset_ + (num * getStride())); }

   private:
      shared_ptr<vector<float>> floats_;
      int xOffset_;
      int yOffset_;
      int zOffset_;
      int stride_;
};

#endif /* COLLADACPP_SOURCE_HPP_ */
