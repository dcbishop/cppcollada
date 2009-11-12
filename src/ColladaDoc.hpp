#ifndef COLLADACPP_COLLADADOC_HPP_
#define COLLADACPP_COLLADADOC_HPP_

class Scene;
class Collada;
class ColladaDocManager;
class VisualScene;


#include <iostream>
#include <string>
#include <map>
using namespace std;

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

class ColladaObject;
class ColladaNode;
class Id;
class Name;
class Position;
class Rotation;
class RotationGL;
class Scale;
class Geometry;

#include "SmartPointers.hpp"

typedef map<string, DOMElement*> ElementIdMap;
typedef ElementIdMap::iterator ElementIdMapIterator;
typedef pair<string, DOMElement*> ElementIdMapPair;

class ColladaDoc {
   public:
      ColladaDoc(ColladaDocManager* manager, string url);
      ~ColladaDoc();
      DOMDocument* loadColladaDoc(string url);
      DOMDocument* loadColladaDocFile(string filename);
      DOMNodeList* getElementsByTagName(string tag);
      DOMElement* getElementById(string id);
      shared_ptr<ColladaObject> getColladaObjectById(string id);

      //TODO: Consider seperating these into a namespace
      float* getFloatArray(string text, int count);
      shared_ptr<ColladaObject> loadColladaObject(DOMElement* element);
      string getAttribute(DOMElement* element, string attribute);
      void loadId(DOMElement* element, Id* id);
      void loadName(DOMElement* element, Name* name);
      shared_ptr<VisualScene> loadVisualScene(DOMElement* element);
      shared_ptr<ColladaNode> loadColladaNode(DOMElement* element);
      shared_ptr<Geometry> loadGeometry(DOMElement* element);
      void loadTranslation(DOMElement* element, Position* position);
      void loadRotation(DOMElement* element, RotationGL* rotation, int number);
      void loadRotations(DOMElement* element, RotationGL* rotation);
      void loadScale(DOMElement* element, Scale* scale);
      void loadInstances(DOMElement* element, ColladaNode* node);
      shared_ptr<ColladaObject> loadInstance(DOMElement* element, ColladaNode* node);

      shared_ptr<Collada> getCollada();
      shared_ptr<Scene> getScene();
      bool isUrlLocal(string url);
      string getUrlId(string url);
      shared_ptr<VisualScene> getVisualScene(string url);
      shared_ptr<ColladaObject> getColladaObjectByUrl(string url);

   private:
      void buildIdMap_();
      bool isString_(const XMLCh* tag1, string tag2);

      string url_;
      XercesDOMParser* parser_;
      DOMDocument* xmlDoc_;
      ColladaDocManager* manager_;
      ElementIdMap idMap_;
};

#endif /* COLLADACPP_COLLADADOC_HPP_ */
