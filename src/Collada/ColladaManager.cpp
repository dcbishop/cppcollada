#include "../Collada/ColladaManager.hpp"

#include "../Collada/Collada.hpp"
#include "../Collada/ColladaDoc.hpp"
#include "../Collada/Scene.hpp"
#include "../Collada/VisualScene.hpp"

ColladaManager::ColladaManager() {
   colladaDocManager_.setColladaManager(this);
}

/**
 * Gets a Collada object from a URL.
 * @param url No remote urls, only 'file://somedir/file.dae' or '/somedir/file.dae'.
 * @return A Collada object.
 */
shared_ptr<Collada> ColladaManager::getCollada(const string& url) {
   // See if the collada is already loaded...
   ColladaMapIterator iter = colladas_.find(url);
   if(iter != colladas_.end()) {
      return iter->second;
   }

   shared_ptr<ColladaDoc> colladaDoc(colladaDocManager_.getColladaDoc(url));
   ColladaPtr collada(colladaDoc->getCollada());
   addCollada(url, collada);
   
   
   return collada;
}

void ColladaManager::addCollada(const string& url, ColladaPtr collada) {
   colladas_.insert(ColladaMapPair(url, collada));
}

/**
 * Unloads raw COLLARA XML documents from memory. Doesn't effect loaded
 * Collada objects. Usefull to call after batch loading a bunch of .dae.
 */
void ColladaManager::scrub() {
   colladaDocManager_.unloadColladaDocs();
}

/**
 * Get the COLLADA based on its index number.
 * I assume this isn't 'safe' for unsorted_map's as they don't seem to
 * include retrevial by index, but its just for the editor GUI.
 */
ColladaMapIterator ColladaManager::getColladaNum(const int& num) {
   if(num > (int)colladas_.size() || num < 0) {
      return colladas_.end();
   }

   ColladaMapIterator cmapIter = colladas_.begin();
   int i = 0;
   while(cmapIter != colladas_.end()) {
      if(i == num) {
         return cmapIter;
      }
      i++;
      cmapIter++;
   }
   return colladas_.end();
}
