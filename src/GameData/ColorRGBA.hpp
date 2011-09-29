#ifndef COLLADACPP_COLORRGBA_HPP_
#define COLLADACPP_COLORRGBA_HPP_

#include "../GameData/SmartPointers.hpp"

enum { INDEX_RED, INDEX_GREEN, INDEX_BLUE, INDEX_ALPHA };

class ColorRGBA {
   public:
      ColorRGBA() {
        setColor(1.0f, 1.0f, 1.0f, 1.0f);
     }

      ColorRGBA(const float& red, const float& green, const float& blue, const float& alpha) {
         setColor(red, green, blue, alpha);
     }
     ColorRGBA(const float& red, const float& green, const float& blue) {
         setColor(red, green, blue);
      }
      
      inline void setRed(const float& red) { rgba[INDEX_RED] = red; }
      inline void setGreen(const float& green) { rgba[INDEX_GREEN] = green; }
      inline void setBlue(const float& blue) { rgba[INDEX_BLUE] = blue; }
      inline void setAlpha(const float& alpha) { rgba[INDEX_ALPHA] = alpha; }
      inline void setColor(const shared_ptr<ColorRGBA> color) { setRed(color->getRed()); setGreen(color->getGreen()); setBlue(color->getBlue()); setAlpha(color->getAlpha()); }
      inline void setColor(const float& red, const float& green, const float& blue, const float& alpha) { setRed(red); setGreen(green); setBlue(blue); setAlpha(alpha); }
      inline void setColor(const float& red, const float& green, const float& blue) { setColor(red, green, blue, 1.0f); }
      inline float getRed() const { return rgba[INDEX_RED]; }
      inline float getGreen() const { return rgba[INDEX_GREEN]; }
      inline float getBlue() const { return rgba[INDEX_BLUE]; }
      inline float getAlpha() const { return rgba[INDEX_ALPHA]; }
      inline const float (&getArray() const)[4] {return rgba; } 

   private:
      float rgba[4];
};

typedef shared_ptr<ColorRGBA> ColorRGBAPtr;

#endif /* COLLADACPP_COLORRGBA_HPP_ */
