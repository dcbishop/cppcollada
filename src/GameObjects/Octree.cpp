#include "../GameObjects/Octree.hpp"

#include "../Debug/console.h"

Octree::Octree() {         
   level_ = 0;
   children_ = false;
   setGridSize(128, 128, 128);
   setIsSolid(false);
}

void Octree::debug() {
   /*if(getLevel() < 4) {
      for(int i = 0; i < 8; i++) {
         OctreePtr octree(new Octree());
         setChild(i, octree);
         octree->debug();
      }
   }

   for(int i = 0; i < 8; i++) {
      int test = -1;
      if(branches_[i] != OctreePtr()) {
         test = branches_[i]->getLevel();
      }
      //DEBUG_M("%d: %d", i, test);
   }*/
   for(int z = 0; z < getGridDepth(); z++) {
      for(int x = 0; x < getGridWidth(); x++) {
         OctreePtr test = digCell(x, getGridHeight()/2, z);
         test->setIsSolid(true);
         /*test = digCell(x, getGridHeight()-1, z);
         test->setIsSolid(true);*/
      }
   }
   /*OctreePtr test = digCell(0, 0, 0);
   test->setIsSolid(true);
   test = digCell(1, 0, 0);
   test->setIsSolid(true);*/
}

/**
 * Tunnels down to a specific cordinate, creating new Octree nodes as
 * required.
 */
OctreePtr Octree::digCell(const int x, const int y, const int z) {
   int branchNum = 0;
   OctreePtr found;
   int subx = x;
   int suby = y;
   int subz = z;

   if(x < 0 || x >= getGridWidth() ||
      y < 0 || y >= getGridHeight() ||
      z < 0 || z >= getGridDepth()) {
      ERROR("Octree coordinates out of bounds (%d, %d, %d) of (%d, %d, %d)... You fell out of the tree...", x, y, z, getGridWidth(), getGridHeight(), getGridDepth());
      return found;
   }

   if(x < (getGridWidth()/2)) {
      // Go left
   } else {
      // Go right
      branchNum+=1;
      subx = x-(getGridWidth()/2);
   }

   if(y < (getGridHeight()/2)) {
      // Top
   } else {
      // Bottom
      branchNum+=2;
      suby = y-(getGridHeight()/2);
   }

   if(z < (getGridHeight()/2)) {
      // Front
   } else {
      branchNum+=4;
      subz = z-(getGridDepth()/2);
   }

   OctreePtr child = getChild(branchNum);
   if(child == OctreePtr()) {
      child = OctreePtr(new Octree);
      setChild(branchNum, child);
   }

   if(child->getGridWidth() == 1) {
      found = child;
   } else {
      found = child->digCell(subx, suby, subz);
   }

   return found;
}
