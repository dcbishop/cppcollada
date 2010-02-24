#include "Renderable.hpp"
#include "ColorRGBA.hpp"

/**
 * A simple grid.
 */
class Grid: public Renderable {
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
         color_.setRed(1.0f);
         color_.setGreen(1.0f);
         color_.setBlue(1.0f);
         color_.setAlpha(1.0f);
      }
      float getSpacing() {return spacing_;}
      int getSizeX(){return sx_;}
      int getSizeY(){return sy_;}
      int getSizeZ(){return sz_;}
      void setSpacing(const float spacing) { spacing_ = spacing; }
      void setSizeX(const int sx) { sx_ = sx; }
      void setSizeY(const int sy) { sy_ = sy; }
      void setSizeZ(const int sz) { sz_ = sz; }
      ColorRGBA getColor(){return color_;}
      COLLADA_RENDER_FUNCTION
};
