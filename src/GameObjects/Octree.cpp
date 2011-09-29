#include "../GameObjects/Octree.hpp"

#include "../Debug/console.h"

#include <libnoise/noise.h>
using namespace noise;

Octree::Octree() {         
   level_ = 0;
   children_ = false;
   setGridSize(64, 64, 64);
   setIsSolid(false);
}

void Octree::debug() {
   generateRandomOctree(this);
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

void Octree::generateRandomOctree(Octree* octree) {
   //Use perlin for heightmap
   module::Perlin perlinModule;
   for(int z = 0; z < octree->getGridDepth(); z++) {
      for(int x = 0; x < octree->getGridWidth(); x++) {
         float value = (perlinModule.GetValue(0.0+(x/100.0), 0.75, 0.0+(z/100.0))+1.0)/2.0;
         if(value > 1.0) {
            value = 1.0;
         } else if(value < 0.0f) {
            value = 0.0f;
         }
         int height = (int)(value*octree->getGridHeight()/2);
         
         for(int y = 0; y < height; y++) {

            //int y = 0;
            //DEBUG_A("x=%d, y=%d, z=%d, value=%f", x, y, z, value);
            OctreePtr test = octree->digCell(x, y, z);
            test->setIsSolid(true);
            ColorRGBAPtr defcol(new ColorRGBA(0.2, 0.75, 0.3));
            test->setColor(defcol);
         }
      }
   }
   
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

/*
   // Solid Fill
   for(int z = 0; z < octree->getGridDepth(); z++) {
     for(int y = 0; y < octree->getGridHeight(); y++) {
      for(int x = 0; x < octree->getGridWidth(); x++) {
          OctreePtr test = octree->digCell(x, y, z);
          test->setIsSolid(true);
          ColorRGBAPtr defcol(new ColorRGBA(0.2, 0.75, 0.3));
          test->setColor(defcol);
      }
      }
   }
*/   
   /*OctreePtr test = digCell(0, 0, 0);
   test->setIsSolid(true);
   test = digCell(1, 0, 0);
   test->setIsSolid(true);*/
}

