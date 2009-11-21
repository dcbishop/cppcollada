#ifndef COLLADACPP_INPUT_HPP_
#define COLLADACPP_INPUT_HPP_

#include "Source.hpp"

class Input {
   public:
      void setOffset(int offset) { offset_ = offset; }
      int getOffset() { return offset_; }
      void setSource(shared_ptr<Source> source) { source_ = source; }

      int getX(int num) { return source_->getX(num); }
      int getY(int num) { return source_->getY(num); }
      int getZ(int num) { return source_->getZ(num); }

   private:
      int offset_;
      shared_ptr<Source> source_;
};

#endif /* COLLADACPP_INPUT_HPP_ */
