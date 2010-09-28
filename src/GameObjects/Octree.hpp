#ifndef GAMEOBJECTS_OCTREE_HPP_
#define GAMEOBJECTS_OCTREE_HPP_

#include "../GameObjects/GameObject.hpp"
#include "../Debug/console.h"

class Octree;
typedef shared_ptr<Octree> OctreePtr;

class Octree : public GameObject {
   public:
      Octree();

      void setLevel(int level) { level_ = level; }
      int getLevel() { return level_; }

      void setParent(OctreePtr parent) {
         parent_ = parent;
         setLevel(parent->getLevel()+1);
         setGridSize(parent->getGridWidth()/2, parent->getGridHeight()/2, parent->getGridDepth()/2);
      }

      OctreePtr getParent() {
         return parent_;
      }

      void setGridSize(int width, int height, int depth) {
         width_ = width;
         height_ = height;
         depth_ = depth;
      }

      int getGridWidth() {
         return width_;
      }
      int getGridHeight() {
         return height_;
      }
      int getGridDepth() {
         return depth_;
      }

      void setIsSolid(bool solid) {
         solid_ = solid;
      }
      bool getIsSolid() {
         return solid_;
      }

      void setChild(int num, OctreePtr octree) { branches_[num] = octree; octree->setParent(OctreePtr(this)); children_ = true; }
      void setFrontTopLeft(OctreePtr octree) { setChild(0, octree); }
      void setFrontTopRight(OctreePtr octree) { setChild(1, octree); }
      void setFrontBottomLeft(OctreePtr octree) { setChild(2, octree); }
      void setFrontBottomRight(OctreePtr octree) { setChild(3, octree); }
      void setBackTopLeft(OctreePtr octree) { setChild(4, octree); }
      void setBackTopRight(OctreePtr octree) { setChild(5, octree); }
      void setBackBottomLeft(OctreePtr octree) { setChild(6, octree); }
      void setBackBottomRight(OctreePtr octree) { setChild(7, octree); }

      OctreePtr getChild(int num) { return branches_[num]; }      
      OctreePtr getFrontTopLeft() { return branches_[0]; }
      OctreePtr getFrontTopRight() { return branches_[1]; }
      OctreePtr getFrontBottomLeft() { return branches_[2]; }
      OctreePtr getFrontBottomRight() { return branches_[3]; }
      OctreePtr getBackTopLeft() { return branches_[4]; }
      OctreePtr getBackTopRight() { return branches_[5]; }
      OctreePtr getBackBottomLeft() { return branches_[6]; }
      OctreePtr getBackBottomRight() { return branches_[7]; }

      OctreePtr digCell(const int x, const int y, const int z);


      bool getHasChildren() { return children_; }

      void debug(); // DEBUG

      COLLADA_RENDER_FUNCTION

   private:
      int level_;
      bool children_;
      OctreePtr branches_[8];
      OctreePtr parent_;
      int width_;
      int height_;
      int depth_;
      bool solid_;
};

#endif /* GAMEOBJECTS_OCTREE_HPP_ */
