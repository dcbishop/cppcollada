#include "../GameObjects/BlockChunk.hpp"

#include "../Debug/console.h"

#include <time.h>


BlockChunk::BlockChunk() {
   chunk_x_ = 0;
   chunk_y_ = 0;
   setChunkSize(16, 16, 16);
}

void BlockChunk::generateRandomBlockChunk(BlockChunk* BlockChunk) {
   // TODO: Check for a better way to seed this?
   srand(chunk_x_);
   srand(chunk_y_ * rand());

   for(unsigned int z = 0; z < getChunkDepth(); z++) {
      for(unsigned int y = 0; y < getChunkDepth(); y++) {
         for(unsigned int x = 0; x < getChunkWidth(); x++) {
            if(rand() % 2) {
               setBlock(x, y, z, true);
            } else {
               setBlock(x, y, z, false);
            }
         }
      }
   }
}



