#include "../Collada/ColladaDocManager.hpp"

#include "../Collada/ColladaManager.hpp"
#include "../Collada/ColladaDoc.hpp"
#include "../Collada/ColladaUrl.hpp"

#include "../Debug/console.h"

/**
 * Gets a COLLADA XML document from URL.
 * Loads it if necessary.
 * @param url The URL to load...
 */
shared_ptr<ColladaDoc> ColladaDocManager::getColladaDoc(const string& url) {
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
ColladaObjectPtr ColladaDocManager::getColladaObjectByUrl(const string& url) {
   DEBUG_M("getColladaObjectByUrl(%s)", url.c_str());

   string strippedUrl = ColladaUrl::getStrippedUrl(url);
   string filename = ColladaUrl::getFilename(url);
   string fragment = ColladaUrl::getFragment(url);
   DEBUG_M("strippedUrl='%s', filename='%s', fragment='%s'", strippedUrl.c_str(), filename.c_str(), fragment.c_str());
   shared_ptr<ColladaDoc> colladaDoc(getColladaDoc(filename));
   if(!colladaDoc) {
      return ColladaObjectPtr();
   }

   return colladaDoc->getColladaObjectByUrl(fragment);
}

/**
 * Unloads all the raw XML COLLADA docs from memory.
 */
void ColladaDocManager::unloadColladaDocs() {
   colladaDocs_.clear();
}

void ColladaDocManager::setColladaManager(ColladaManager* cm) {
   colladaManager_ = cm;
}

