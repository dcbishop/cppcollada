#include "../Render/ColladaRendererGL_DevIL.hpp"

#include <IL/il.h>
#include "../Debug/console.h"

ColladaRendererGL_DevIL::~ColladaRendererGL_DevIL() {
   #warning ['TODO']: Unload all the images...
}

void ColladaRendererGL_DevIL::init() {
   LOG("Initilizing DevIL image loader...");
   if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
         ERROR("DevIL library version '%d' is different to '%d'... This might crash...\n", ilGetInteger(IL_VERSION_NUM), IL_VERSION);
   }
   ilInit();
   LOG("Initilized DevIL image loader.");
}


int ColladaRendererGL_DevIL::loadImage(ImagePtr image) {
   string filename = image->getFilename();
   DEBUG_M("Loading image '%s'...", filename.c_str());

   GLuint gTexId = 0;
   ILuint dTexId = 0;
   ilGenImages(1, &dTexId);
   ilBindImage(dTexId);

   DEBUG_M("Preload...");
   if(ilLoadImage(filename.c_str())) {
      DEBUG_M("Loaded ok... binding...");
      glGenTextures(1, &gTexId);
      glBindTexture(GL_TEXTURE_2D, gTexId);

      #warning ['TODO']: This code shouldn't be here...
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      // Bind DevIL texture to OpenGL texture...
      glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP),
         ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
         ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
   } else {
      WARNING("Failed to load texture '%s'...", filename.c_str());
      ilDeleteImages(1, &dTexId);
      return -1;
   }

   // Add the image to the list of images...
   images_.insert(pair<string, GLuint>(filename, gTexId));

   // Now that the DevIL texture had been bound, we can delete it...
   ilDeleteImages(1, &dTexId);
   return gTexId;
}
