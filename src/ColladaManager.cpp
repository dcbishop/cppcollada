#include "ColladaManager.hpp"

#include "Collada.hpp"
#include "ColladaDoc.hpp"
#include "Scene.hpp"
#include "VisualScene.hpp"

/**
 * 
 */
Collada* ColladaManager::getCollada(string url) {
   // See if the collada is already loaded...
   ColladaMapIterator iter = colladas_.find(url);
   if(iter != colladas_.end()) {
      return iter->second;
   }

   ColladaDoc *colladaDoc = colladaDocManager_.getColladaDoc(url);
   Collada *collada = colladaDoc->getCollada();
   
   colladas_.insert(ColladaMapPair(url, collada));
   return collada;
}

VisualScene* ColladaManager::getVisualScene(string url) {
   ColladaDoc* colladaDoc = colladaDocManager_.getColladaDoc(url);
   #warning ['TODO']: Strip id from url...
   string id = url;
   return colladaDoc->getVisualScene(id);
}
