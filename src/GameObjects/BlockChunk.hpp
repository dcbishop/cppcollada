#ifndef GAMEOBJECTS_BlockChunk_HPP_
#define GAMEOBJECTS_BlockChunk_HPP_

#include "../GameObjects/GameObject.hpp"
#include "../GameData/ColorRGBA.hpp"
#include "../Debug/console.h"

class BlockChunk;
typedef shared_ptr<BlockChunk> BlockChunkPtr;
typedef unsigned char block;

class BlockChunk : public GameObject {
   public:
      BlockChunk();
      ~BlockChunk() {
         free(blocks_);
      }

      void setChunkSize(const unsigned int& width, const unsigned int& height, const unsigned int& depth) {
         width_ = width;
         height_ = height;
         depth_ = depth;
         blocks_ = (block*)malloc(width_ * height_ * depth_ * sizeof(block));
      }

      unsigned int getChunkWidth() {
         return width_;
      }
      unsigned int getChunkHeight() {
         return height_;
      }
      unsigned int getChunkDepth() {
         return depth_;
      }

      unsigned int getBlockIndex(const unsigned int& x, const unsigned int& y, unsigned const int& z) {
         return (x + (y * height_ + z) * width_);
      }
      void setBlock(const unsigned int& x, const unsigned int& y, const unsigned int& z, const unsigned char& block) {
         *(blocks_ + getBlockIndex(x, y, z)) = block;
      }

      block getBlock(const unsigned int& x, const unsigned int& y, const unsigned int& z) {
         return *(blocks_ + getBlockIndex(x, y, z));
      }

      void generateRandomBlockChunk(BlockChunk* BlockChunk);

      COLLADA_RENDER_FUNCTION

   private:
      int chunk_x_;
      int chunk_y_;
      unsigned int width_;
      unsigned int height_;
      unsigned int depth_;
      block* blocks_;
};

#endif /* GAMEOBJECTS_BlockChunk_HPP_ */
