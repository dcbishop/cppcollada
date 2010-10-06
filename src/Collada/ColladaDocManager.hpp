#ifndef COLLADACPP_COLLADADOCMANAGER_HPP_
#define COLLADACPP_COLLADADOCMANAGER_HPP_

#include <string>
using namespace std;

#include "../GameData/SmartPointers.hpp"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

#include "../GameData/SmartPointers.hpp"
#include "../Collada/ColladaObject.hpp"

class VisualScene;
class ColladaDoc;
class Scene;
class ColladaObject;
class ColladaManager;

typedef unordered_map< string, shared_ptr<ColladaDoc> > ColladaDocMap;
typedef ColladaDocMap::iterator ColladaDocMapIterator;
typedef pair< string, shared_ptr<ColladaDoc> > ColladaDocMapPair;

/**
 * 
 */
class ColladaDocManager {
   public:
      shared_ptr<ColladaDoc> getColladaDoc(const string& url);
      void unloadColladaDocs();
      ColladaObjectPtr getColladaObjectByUrl(const string& url);
      void setColladaManager(ColladaManager* cm);
      ColladaManager* getColladaManager() {return colladaManager_; }

   private:
      ColladaDocMap colladaDocs_;
      ColladaManager* colladaManager_;
};
typedef shared_ptr<ColladaDocManager> ColladaDocManagerPtr;

#endif /* COLLADACPP_COLLADADOCMANAGER_HPP_ */
