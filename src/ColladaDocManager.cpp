#include "ColladaDocManager.hpp"

#include "ColladaDoc.hpp"
#include "ColladaUrl.hpp"

/**
 * Gets a COLLADA XML document from URL.
 * Loads it if necessary.
 * @param url The URL to load...
 */
ColladaDoc* ColladaDocManager::getColladaDoc(string url) {
   // See if we have already loaded it...
   ColladaDocMapIterator iter = colladaDocs_.find(url);
   if(iter != colladaDocs_.end()) {
      return iter->second;
   }

   // Otherwise load it...
   ColladaDoc *colladaDoc = new ColladaDoc(this, url);
   colladaDocs_.insert(ColladaDocMapPair(url, colladaDoc));
   return colladaDoc;
}

/**
 * Gets a COLLADA scene from a url.
 * @param url The COLLADA .dae file in URL format.
 * @return The scene.
 */
Scene* ColladaDocManager::getScene(string url) {
   /*if(isLocal(url)) {
      cerr << "Tried to get local scene from global manager..." << endl;
      return NULL;
   }*/
   return NULL;
}

ColladaObject* ColladaDocManager::getColladaObjectByUrl(string url) {
   ColladaDoc* colladaDoc = getColladaDoc(ColladaUrl::getStrippedUrl(url));
   if(!colladaDoc) {
      return NULL;
   }
   return colladaDoc->getColladaObjectByUrl(url);
}
