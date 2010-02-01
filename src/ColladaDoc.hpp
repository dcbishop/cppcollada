#ifndef COLLADACPP_COLLADADOC_HPP_
#define COLLADACPP_COLLADADOC_HPP_

class Scene;
class Collada;
class ColladaDocManager;
class VisualScene;


#include <iostream>
#include <string>
#include <map>
#include <vector>
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
class ColladaCamera;
class ColladaLight;
class Mesh;
class Vertices;
class Triangles;
class Input;
class Source;
class Material;
class Effect;

#include "SmartPointers.hpp"

typedef map<string, DOMElement*> ElementIdMap;
typedef ElementIdMap::iterator ElementIdMapIterator;
typedef pair<string, DOMElement*> ElementIdMapPair;

class ColladaDoc {
   public:
      ColladaDoc(ColladaDocManager* manager, string url);
      ~ColladaDoc();
      DOMDocument* loadColladaDoc(const string& url);
      DOMDocument* loadColladaDocFile(const string& filename);
      DOMNodeList* getElementsByTagName(const DOMElement* element, string tag);
      DOMElement* getElementById(string id);
      shared_ptr<ColladaObject> getColladaObjectById(string id);

      //TODO: Consider seperating these into a namespace
      shared_ptr<vector<float>> getFloats(string text);
      shared_ptr<ColladaObject> loadColladaObject(const DOMElement* element);
      string getAttribute(const DOMElement* element, string attribute);
      void loadId(const DOMElement* element, Id* id);
      void loadName(const DOMElement* element, Name* name);
      shared_ptr<VisualScene> loadVisualScene(const DOMElement* element);
      shared_ptr<ColladaNode> loadColladaNode(const DOMElement* element);
      shared_ptr<Geometry> loadGeometry(const DOMElement* element);
      void loadTranslation(const DOMElement* element, Position* position);
      void loadRotation(const DOMElement* element, RotationGL* rotation, int number);
      void loadRotations(const DOMElement* element, RotationGL* rotation);
      void loadScale(const DOMElement* element, Scale* scale);
      void loadInstances(const DOMElement* element, ColladaNode* node);
      shared_ptr<ColladaLight> loadColladaLight(const DOMElement* element);
      shared_ptr<ColladaObject> loadInstance(const DOMElement* element, ColladaNode* node);
      shared_ptr<ColladaCamera> loadColladaCamera(const DOMElement* element);
      shared_ptr<Mesh> loadMesh(const DOMElement* element);
      shared_ptr<Vertices> loadVertices(const DOMElement* element);
      shared_ptr<Triangles> loadTriangles(const DOMElement* element);
      shared_ptr<Source> loadSource(const DOMElement* element);
      shared_ptr<Material> loadMaterial(const DOMElement* element);
      void loadSourceTechnique(const DOMElement* element, shared_ptr<Source> source);
      DOMElement* getElementByTagName(const DOMElement* element, string tag);
      shared_ptr<Collada> getCollada();
      shared_ptr<Scene> getScene();
      bool isUrlLocal(string url);
      string getUrlId(string url);
      shared_ptr<VisualScene> getVisualScene(string url);
      shared_ptr<ColladaObject> getColladaObjectByUrl(string url);
      shared_ptr<Input> loadInput(const DOMElement* element);
      shared_ptr<vector<int>> loadPrimitives(const DOMElement* element);
      shared_ptr<Effect> loadEffect(const DOMElement* element);


   private:
      void buildIdMap_();
      bool isString_(const XMLCh* tag1, string tag2);

      string url_;
      XercesDOMParser* parser_;
      DOMDocument* xmlDoc_;
      ColladaDocManager* manager_;
      ElementIdMap idMap_;
      shared_ptr<Collada> collada_;
      shared_ptr<Scene> scene_;
};

#endif /* COLLADACPP_COLLADADOC_HPP_ */
