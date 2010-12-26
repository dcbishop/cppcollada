#ifndef COLLADACPP_SOURCE_HPP_
#define COLLADACPP_SOURCE_HPP_

#include "../GameData/SmartPointers.hpp"
#include "../Collada/ColladaObject.hpp"

#include "../Debug/console.h"

class Source: public ColladaObject {
   public:
      /*void setFloats(shared_ptr< vector<float> > floats) {
         floats_ = floats;
         if(!floats_) {
            WARNING("Setting of floats screwed up");
         }
      }*/
      Source() {
			floats_ = NULL;
			num_ = 0;
		}
		
		~Source() {
			delete floats_;
		}
 
		/**
		 * Sets the sources floats based on a array of floats and number of floats.
		 */
      void setFloats(float* floats, const int &num) {
			floats_ = floats;
			num_ = num;
		}
		
		/**
		 * Sets the sources floats based on a shared pointer to a vector of floats.
		 */
		void setFloats(shared_ptr< vector<float> > floats) {
			floats_ = new float[floats->size()];

			for(unsigned int i = 0; i < floats->size(); i++) {
				floats_[i] = floats->at(i);
			}
			
			num_ = floats->size();
		}
		
		float* getFloats() {
			return floats_;
		}

      //virtual int getCount() { return floats_->size(); }
      virtual int getCount() { return num_; }
      inline void setXOff(const int& xOffset) { xOffset_ = xOffset; }
      inline void setYOff(const int& yOffset) { yOffset_ = yOffset; }
      inline void setZOff(const int& zOffset) { zOffset_ = zOffset; }
      inline void setSOff(const int& sOffset) { sOffset_ = sOffset; }
      inline void setTOff(const int& tOffset) { tOffset_ = tOffset; }
      inline void setStride(const int& stride) { stride_ = stride; }
      inline int getStride() const { return stride_; }

      /*inline virtual float getXPos(const int& num) const { return floats_->at(xOffset_ + (num * getStride())); }
      inline virtual float getYPos(const int& num) const { return floats_->at(yOffset_ + (num * getStride())); }
      inline virtual float getZPos(const int& num) const { return floats_->at(zOffset_ + (num * getStride())); }
      inline virtual float getSPos(const int& num) const { return floats_->at(sOffset_ + (num * getStride())); }
      inline virtual float getTPos(const int& num) const { return floats_->at(tOffset_ + (num * getStride())); }*/

      inline virtual float getXPos(const int& num) const { return floats_[xOffset_ + (num * getStride())]; }
      inline virtual float getYPos(const int& num) const { return floats_[yOffset_ + (num * getStride())]; }
      inline virtual float getZPos(const int& num) const { return floats_[zOffset_ + (num * getStride())]; }
      inline virtual float getSPos(const int& num) const { return floats_[sOffset_ + (num * getStride())]; }
      inline virtual float getTPos(const int& num) const { return floats_[tOffset_ + (num * getStride())]; }

   private:
      //shared_ptr< vector<float> > floats_;
      float* floats_;
      int num_;
      int xOffset_;
      int yOffset_;
      int zOffset_;
      int sOffset_;
      int tOffset_;
      int stride_;
};

#endif /* COLLADACPP_SOURCE_HPP_ */
