#ifndef COLLADACPP_COLLADADOCMANAGER_HPP_
#define COLLADACPP_COLLADADOCMANAGER_HPP_

#include <map>
#include <string>
using namespace std;

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

class VisualScene;
class ColladaDoc;
class Scene;

#warning ['TODO']: Used for ColladaObject, remove me when its a real thing...
#include "ColladaDoc.hpp"

typedef map<string, ColladaDoc*> ColladaDocMap;
typedef ColladaDocMap::iterator ColladaDocMapIterator;
typedef pair<string, ColladaDoc*> ColladaDocMapPair;

/**
 * 
 */
class ColladaDocManager {
   public:
      ColladaDoc* getColladaDoc(string url);
      Scene* getColladaScene(string url);
      VisualScene* getColladaVisualScene(string url, string id);
      Scene* getScene(string url);

      string stripUrlId(string url);
      ColladaObject* getColladaObjectByUrl(string url);

   private:
      ColladaDocMap colladaDocs_;
};

#endif /* COLLADACPP_COLLADADOCMANAGER_HPP_ */
