#ifndef COLLADACPP_COLLADA_COLLADAMANAGER_HPP_
#define COLLADACPP_COLLADA_COLLADAMANAGER_HPP_

/**
 * Stores open Collada files for processing...
 */

#include <map>
#include <string>
using namespace std;

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;


#include "../Collada/Collada.hpp"
#include "../Collada/ColladaDocManager.hpp"
#include "../GameData/SmartPointers.hpp"

class VisualScene;
class ColladaDocManager;

typedef map<string, shared_ptr<Collada>> ColladaMap;
typedef ColladaMap::iterator ColladaMapIterator;
typedef pair<string, shared_ptr<Collada>> ColladaMapPair;

class ColladaManager : public ColladaObject {
   public:
      ColladaManager();
      ColladaPtr getCollada(const string& url);
      void addCollada(const string& url, ColladaPtr collada);
      ColladaMap* getColladaMap() { return &colladas_; }
      ColladaMapIterator getColladaNum(const int& num);
      void scrub();

   private:
      ColladaMap colladas_;
      ColladaDocManager colladaDocManager_;
};
typedef shared_ptr<ColladaManager> ColladaManagerPtr;

#endif /* COLLADACPP_COLLADA_COLLADAMANAGER_HPP_ */
