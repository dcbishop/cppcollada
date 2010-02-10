#ifndef COLLADACPP_COLORRGBA_HPP_
#define COLLADACPP_COLORRGBA_HPP_

#include "SmartPointers.hpp"

/*#define INDEX_RED = 0;
#define INDEX_GREEN = 1;
#define INDEX_BLUE = 2;
#define INDEX_ALPHA = 3;*/

enum { INDEX_RED, INDEX_GREEN, INDEX_BLUE, INDEX_ALPHA };

class ColorRGBA {
   public:
      void setRed(const float& red) { rgba[INDEX_RED] = red; }
      void setGreen(const float& green) { rgba[INDEX_GREEN] = green; }
      void setBlue(const float& blue) { rgba[INDEX_BLUE] = blue; }
      void setAlpha(const float& alpha) { rgba[INDEX_ALPHA] = alpha; }
      void setColor(const shared_ptr<ColorRGBA> color) { setRed(color->getRed()); setGreen(color->getGreen()); setBlue(color->getBlue()); setAlpha(color->getAlpha()); }
      void setColor(const float& red, const float& green, const float& blue, const float& alpha) { setRed(red); setGreen(green); setBlue(blue); setAlpha(alpha); }
      void setColor(const float& red, const float& green, const float& blue) { setColor(red, green, blue, 1.0f); }
      const float getRed() const { return rgba[INDEX_RED]; }
      const float getGreen() const { return rgba[INDEX_GREEN]; }
      const float getBlue() const { return rgba[INDEX_BLUE]; }
      const float getAlpha() const { return rgba[INDEX_ALPHA]; }
      const float (&getArray() const)[4] {return rgba; } 

   private:
      /*float red_;
      float green_;
      float blue_;
      float alpha_;*/
      float rgba[4];
};

#endif /* COLLADACPP_COLORRGBA_HPP_ */
