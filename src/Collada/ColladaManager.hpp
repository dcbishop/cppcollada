#ifndef COLLADACPP_COLLADAMANAGER_HPP_
#define COLLADACPP_COLLADAMANAGER_HPP_

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

class VisualScene;

typedef map<string, shared_ptr<Collada>> ColladaMap;
typedef ColladaMap::iterator ColladaMapIterator;
typedef pair<string, shared_ptr<Collada>> ColladaMapPair;

class ColladaManager {
   public:
      shared_ptr<Collada> getCollada(const string& url);
      void scrub();

   private:
      ColladaMap colladas_;
      ColladaDocManager colladaDocManager_;
};

#endif /* COLLADACPP_COLLADAMANAGER_HPP_ */
