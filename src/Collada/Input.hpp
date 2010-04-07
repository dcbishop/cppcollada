#ifndef COLLADACPP_COLLADA_INPUT_HPP_
#define COLLADACPP_COLLADA_INPUT_HPP_

#include "../Collada/Source.hpp"

#include "../Debug/console.h"

class Input : public ColladaObject {
   public:
      void setOffset(int offset) { offset_ = offset; }
      int getOffset() const { return offset_; }
      void setSource(shared_ptr<Source> source) { source_ = source; }
      void setSemantic(string semantic) { semantic_ = semantic; }

      virtual int getCount() {return source_->getCount();}
      virtual float getX(const int& num) const { return source_->getXPos(num); }
      virtual float getY(const int& num) const { return source_->getYPos(num); }
      virtual float getZ(const int& num) const { return source_->getZPos(num); }
      virtual float getS(const int& num) const { return source_->getSPos(num); }
      virtual float getT(const int& num) const { return source_->getTPos(num); }

   private:
      int offset_;
      shared_ptr<Source> source_;
      string semantic_;
};
typedef shared_ptr<Input> InputPtr;


#endif /* COLLADACPP_COLLADA_INPUT_HPP_ */
