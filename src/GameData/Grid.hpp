#include "../Render/Renderable.hpp"
#include "../GameData/ColorRGBA.hpp"

/**
 * A simple grid.
 */
class Grid: public Renderable, public ColorRGBA {
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
      inline float getSpacing() const {return spacing_;}
      inline int getSizeX() const {return sx_;}
      inline int getSizeY() const {return sy_;}
      inline int getSizeZ() const {return sz_;}
      inline void setSpacing(const float spacing) { spacing_ = spacing; }
      inline void setSizeX(const int sx) { sx_ = sx; }
      inline void setSizeY(const int sy) { sy_ = sy; }
      inline void setSizeZ(const int sz) { sz_ = sz; }
      //ColorRGBA getColor(){return color_;}
      COLLADA_RENDER_FUNCTION

   private:
      int sx_, sy_, sz_;
      float spacing_;
      ColorRGBA color_;
};
