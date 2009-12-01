#include "ColladaDocManager.hpp"

#include "ColladaDoc.hpp"
#include "ColladaUrl.hpp"

/**
 * Gets a COLLADA XML document from URL.
 * Loads it if necessary.
 * @param url The URL to load...
 */
shared_ptr<ColladaDoc> ColladaDocManager::getColladaDoc(string url) {
   // See if we have already loaded it...
   ColladaDocMapIterator iter = colladaDocs_.find(url);
   if(iter != colladaDocs_.end()) {
      return iter->second;
   }

   // Otherwise load it...
   shared_ptr<ColladaDoc> colladaDoc(new ColladaDoc(this, url));
   colladaDocs_.insert(ColladaDocMapPair(url, colladaDoc));
   return colladaDoc;
}

/**
 * Returns a Collada object from a URL.
 * @param url The URL.
 * @return the loaded object or NULL.
 */
shared_ptr<ColladaObject> ColladaDocManager::getColladaObjectByUrl(string url) {
   string strippedUrl = ColladaUrl::getStrippedUrl(url);
   shared_ptr<ColladaDoc> colladaDoc(getColladaDoc(strippedUrl));
   if(!colladaDoc) {
      return shared_ptr<ColladaObject>();
   }
   return colladaDoc->getColladaObjectByUrl(url);
}

/**
 * Unloads all the raw XML COLLADA docs from memory.
 */
void ColladaDocManager::unloadColladaDocs() {
   colladaDocs_.clear();
}
