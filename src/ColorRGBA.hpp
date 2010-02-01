#ifndef COLLADACPP_COLORRGBA_HPP_
#define COLLADACPP_COLORRGBA_HPP_

#include "SmartPointers.hpp"

class ColorRGBA {
   public:
      void setRed(const float& red) { red_ = red; }
      void setGreen(const float& green) { green_ = green; }
      void setBlue(const float& blue) { blue_ = blue; }
      void setAlpha(const float& alpha) { alpha_ = alpha; }
      void setColor(const shared_ptr<ColorRGBA> color) { red_ = color->getRed(); green_ = color->getGreen(); blue_ = color->getBlue(); alpha_ = color->getAlpha(); }
      void setColor(const float& red, const float& green, const float& blue, const float& alpha) { red_ = red; green_ = green; blue_ = blue; alpha_ = alpha; }
      void setColor(const float& red, const float& green, const float& blue) { setColor(red, green, blue, 1.0f); }
      float getRed() const { return red_; }
      float getGreen() const { return green_; }
      float getBlue() const { return blue_; }
      float getAlpha() const { return alpha_; }

   private:
      float red_;
      float green_;
      float blue_;
      float alpha_;
};

#endif /* COLLADACPP_COLORRGBA_HPP_ */
