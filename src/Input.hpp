#ifndef COLLADACPP_INPUT_HPP_
#define COLLADACPP_INPUT_HPP_

#include "Source.hpp"

#include "console.h"

class Input : public ColladaObject {
   public:
      void setOffset(int offset) { offset_ = offset; }
      int getOffset() const { return offset_; }
      void setSource(shared_ptr<Source> source) { source_ = source; }

      virtual float getX(const int& num) const { return source_->getXPos(num); }
      virtual float getY(const int& num) const { return source_->getYPos(num); }
      virtual float getZ(const int& num) const { return source_->getZPos(num); }

   private:
      int offset_;
      shared_ptr<Source> source_;
};

#endif /* COLLADACPP_INPUT_HPP_ */
