#ifndef COLLADACPP_INPUT_HPP_
#define COLLADACPP_INPUT_HPP_

#include "Source.hpp"

#include "console.h"

class Input : public ColladaObject {
   public:
      void setOffset(int offset) { offset_ = offset; }
      int getOffset() { return offset_; }
      void setSource(shared_ptr<Source> source) { source_ = source; }

      virtual float getX(int num) { return source_->getXPos(num); }
      virtual float getY(int num) { return source_->getYPos(num); }
      virtual float getZ(int num) { return source_->getZPos(num); }

   private:
      int offset_;
      shared_ptr<Source> source_;
};

#endif /* COLLADACPP_INPUT_HPP_ */
