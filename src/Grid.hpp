#include "Renderable.hpp"
#include "ColorRGBA.hpp"

/**
 * A simple grid.
 */
class Grid: public Renderable, public ColorRGBA {
   private:
      int sx_, sy_, sz_;
      float spacing_;
      ColorRGBA color_;
   public:
      Grid(){ 
         sx_ = 10;
         sy_ = 10;
         sz_ = 10;
         spacing_ = 1.0f;
         setRed(0.2f);
         setGreen(0.2f);
         setBlue(0.2f);
         setAlpha(1.0f);
      }
      float getSpacing() const {return spacing_;}
      int getSizeX() const {return sx_;}
      int getSizeY() const {return sy_;}
      int getSizeZ() const {return sz_;}
      void setSpacing(const float spacing) { spacing_ = spacing; }
      void setSizeX(const int sx) { sx_ = sx; }
      void setSizeY(const int sy) { sy_ = sy; }
      void setSizeZ(const int sz) { sz_ = sz; }
      //ColorRGBA getColor(){return color_;}
      COLLADA_RENDER_FUNCTION
};
