#ifndef COLLADACPP_COLLADADOC_HPP_
#define COLLADACPP_COLLADADOC_HPP_

class Scene;
class Collada;
class ColladaDocManager;
class VisualScene;

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "../GameData/SmartPointers.hpp"

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
class InstanceGeometry;
class Sampler2D;
class Image;

#include "../GameData/SmartPointers.hpp"
#include "../Collada/ColladaObject.hpp"
#include "../Collada/Scene.hpp"
#include "../Collada/Phong.hpp"
#include "../Collada/Lambert.hpp"
#include "../Collada/ColladaShader.hpp"
#include "../Collada/GeometricPrimitive.hpp"
#include "../Collada/Triangles.hpp"

typedef unordered_map<string, DOMElement*> ElementIdMap;
typedef ElementIdMap::iterator ElementIdMapIterator;
typedef pair<string, DOMElement*> ElementIdMapPair;

typedef unordered_map<string, ColladaObjectPtr> ColladaObjectMap;
typedef ColladaObjectMap::iterator ColladaObjectMapIterator;
typedef pair<string, ColladaObjectPtr> ColladaObjectMapPair;

typedef vector<int> VectorOfInts;
typedef shared_ptr<VectorOfInts> VectorOfIntsPtr;


class ColladaDoc {
   public:
      ColladaDoc(ColladaDocManager* manager, string url);
      ~ColladaDoc();
      DOMDocument* loadColladaDoc(const string& url);
      DOMDocument* loadColladaDocFile(const string& filename);
      DOMNodeList* getElementsByTagName(const DOMElement* element, string tag);
      DOMElement* getElementById(string id);
      ColladaObjectPtr getColladaObjectById(string id);

      //TODO: Consider seperating these into a namespace
      shared_ptr< vector<float> > getFloatsVector(const string& text);
      ColladaObjectPtr loadColladaObject(const DOMElement* element);
      string getAttribute(const DOMElement* element, string attribute);
      void loadId(const DOMElement* element, Id* id);
      void loadName(const DOMElement* element, Name* name);
      shared_ptr<VisualScene> loadVisualScene(const DOMElement* element);
      shared_ptr<ColladaNode> loadColladaNode(const DOMElement* element);
      shared_ptr<Geometry> loadGeometry(const DOMElement* element);
      void loadGeometricPrimitiveInput(GeometricPrimitivePtr gp, const DOMElement* element);
      void loadTranslation(const DOMElement* element, Position* position);
      void loadRotation(const DOMElement* element, RotationGL* rotation, int number);
      void loadRotations(const DOMElement* element, RotationGL* rotation);
      void loadScale(const DOMElement* element, Scale* scale);
      void loadInstances(const DOMElement* element, ColladaNode* node);
      shared_ptr<ColladaLight> loadColladaLight(const DOMElement* element);
      ColladaObjectPtr loadInstance(const DOMElement* element, ColladaNode* node);
      shared_ptr<InstanceGeometry> loadInstanceGeometry(const DOMElement* element);
      shared_ptr<ColladaCamera> loadColladaCamera(const DOMElement* element);
      shared_ptr<Mesh> loadMesh(const DOMElement* element);
      shared_ptr<Vertices> loadVertices(const DOMElement* element);
      TrianglesPtr loadTriangles(const DOMElement* element);
      TrianglesPtr loadPolygons(const DOMElement* element);
      TrianglesPtr loadPolylist(const DOMElement* element);
      shared_ptr<Source> loadSource(const DOMElement* element);
      shared_ptr<Material> loadMaterial(const DOMElement* element);
      ColladaObjectPtr loadSampler2D(const DOMElement* profileCommon, const DOMElement* element);
      void loadSourceTechnique(const DOMElement* element, shared_ptr<Source> source);
      DOMElement* getElementByTagName(const DOMElement* element, string tag);
      shared_ptr<Collada> getCollada();
      ScenePtr getScene();
      bool isUrlLocal(const string& url);
      string getUrlId(const string& url);
      shared_ptr<VisualScene> getVisualScene(const string& url);
      ColladaObjectPtr getColladaObjectByUrl(const string& url);
      shared_ptr<Input> loadInput(const DOMElement* element);
      VectorOfIntsPtr loadPrimitives(const DOMElement* element);
      shared_ptr<Effect> loadEffect(const DOMElement* element);
      ColladaObjectPtr loadNewparam(const DOMElement* profileCommon, const DOMElement* node);
      ColladaObjectPtr loadSurface(const DOMElement* element);
      shared_ptr<Image> loadImage(const DOMElement* element);

   private:
      void buildIdMap_();
      void loadInstanceGeometry_BindMaterials_(shared_ptr<InstanceGeometry> ig, const DOMElement* element);
      void loadInstanceGeometry_BindMaterial_(shared_ptr<InstanceGeometry> ig, const DOMElement* element);
      bool isString_(const XMLCh* tag1, string tag2);
      ColladaObjectPtr loadEffectNewparamBySid_(const DOMElement* profileCommon, string sid);
      void loadShaderAttributes_(ColladaShaderPtr shader, const DOMElement* element, const DOMElement* texturehack);
      PhongPtr loadPhong_(const DOMElement* element, const DOMElement* texturehack);
      LambertPtr loadLambert_(const DOMElement* element, const DOMElement* texturehack);


      string url_;
      XercesDOMParser* parser_;
      DOMDocument* xmlDoc_;
      ColladaDocManager* colladaDocManager_;
      ElementIdMap idMap_;
      ColladaObjectMap objectMap_;
      shared_ptr<Collada> collada_;
      ScenePtr scene_;
};

#endif /* COLLADACPP_COLLADADOC_HPP_ */
