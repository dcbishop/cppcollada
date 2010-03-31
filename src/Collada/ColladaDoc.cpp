#include "../Collada/ColladaDoc.hpp"

#include "../Collada/ColladaManager.hpp"
#include "../Collada/ColladaDocManager.hpp"
#include "../Collada/ColladaUrl.hpp"

#include "../Collada/Collada.hpp"
#include "../Collada/Scene.hpp"
#include "../Collada/ColladaNode.hpp"
#include "../Collada/VisualScene.hpp"
#include "../Collada/ColladaObject.hpp"
#include "../GameData/Position.hpp"
#include "../GameData/Rotation.hpp"
#include "../GameData/Scale.hpp"
#include "../GameData/RotationGL.hpp"
#include "../Collada/Geometry.hpp"
#include "../Collada/ColladaCamera.hpp"
#include "../Collada/ColladaLight.hpp"
#include "Mesh.hpp"
#include "Vertices.hpp"
#include "../Collada/Triangles.hpp"
#include "../Collada/Source.hpp"
#include "../Collada/Material.hpp"
#include "../Collada/Phong.hpp"
#include "../Collada/InstanceGeometry.hpp"
#include "../Collada/Sampler2D.hpp"

#include "../Debug/console.h"

ColladaDoc::ColladaDoc(ColladaDocManager* manager, string url) {
   DEBUG_M("Entering function...");
   url_ = url;
   xmlDoc_ = loadColladaDoc(url);
   manager_ = manager;
   buildIdMap_();
}

ColladaDoc::~ColladaDoc() {
   // TODO: Delete xmlDoc_ here?
   DEBUG_M("~ColladaDoc()");
   delete parser_;
   XMLPlatformUtils::Terminate();
}

/**
 * Loads a COLLADA document from a URL.
 * @param url The URL of the document to load.
 */
DOMDocument* ColladaDoc::loadColladaDoc(const string& url) {
   DEBUG_M("Entering function...");
   #warning ['TODO']: Process other URL formats...

   // Check to ensure we are loading a file://
   /*const string fileSep = "file://";
   size_t fileIndex = url.find(fileSep);
   if(fileIndex != 0) { //If not we die...
      cerr << "Unsupported URL sceme!" << endl;
      return NULL;
   }*/

   /*string localFilename = url.substr(fileSep.length()-1);
   string localFilename = ColladaUrl::getFilename(url);*/
   return loadColladaDocFile(ColladaUrl::getFilename(url));
}

/**
 * Loads a collada document from a local file.
 * @param filename The filename of the document to load.
 */
DOMDocument* ColladaDoc::loadColladaDocFile(const string& filename) {
   DEBUG_M("loadColladaDocFile(%s)", filename.c_str());
   try {
      XMLPlatformUtils::Initialize();
   } catch (const XMLException& e) {
      char* errMsg = XMLString::transcode(e.getMessage());
      ERROR("Xerces XML ERROR: %s", errMsg);
      XMLString::release(&errMsg);
      return NULL;
   }

   parser_ = new XercesDOMParser();
   /*parser_->loadGrammar("/home/hegemon/tmp/collada_schema_1_5", Grammar::SchemaGrammarType); 
   parser_->setValidationScheme(XercesDOMParser::Val_Always);
   parser_->setDoNamespaces(true);
   parser_->setDoSchema(true);*/

   ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
   parser_->setErrorHandler(errHandler);

   try {
      parser_->parse(filename.c_str());
   } catch (const XMLException& e) {
      char* errMsg = XMLString::transcode(e.getMessage());
      ERROR("Xerces XML ERROR: %s", errMsg);
      XMLString::release(&errMsg);
      return NULL;
   } catch (const DOMException& e) {
      char* errMsg = XMLString::transcode(e.msg);
      ERROR("Xerces DOM ERROR: %s", errMsg);
      XMLString::release(&errMsg);
      return NULL;
   } catch (...) {
      ERROR("Unknown Xerces ERROR...");
      return NULL;
   }

   DOMDocument* xmlDoc = parser_->getDocument();
   DOMElement* elementRoot = xmlDoc->getDocumentElement();
   if(!elementRoot) {
      ERROR("Empty XML document...");
      return NULL;
   }


   //delete parser_;
   // TODO: Should errHandler be deleted here? Do we even need it in the first place?
   delete errHandler;

   return xmlDoc;
}

/**
 * This function builds a map of all the id's.
 * It shouldn't be required except xerces returns null for getElementById
 * It seems it might require validation to be turned on, but I couldn't
 * get it to work so we do it the stupid way.
 */
void ColladaDoc::buildIdMap_() {
   DEBUG_M("Entering function...");
   DOMElement* elementRoot = xmlDoc_->getDocumentElement();
   DOMTreeWalker *walker = xmlDoc_->createTreeWalker(elementRoot, DOMNodeFilter::SHOW_ELEMENT, NULL, true);
   XMLCh* xid = XMLString::transcode("id");
   for(DOMNode *currentNode = walker->nextNode(); currentNode != 0; currentNode = walker->nextNode()) {
      DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
      if(currentElement) {
         const XMLCh* thexid = currentElement->getAttribute(xid);
         if(!thexid || XMLString::stringLen(thexid) == 0) {
            continue;
         }

         char* theid = XMLString::transcode(thexid);
         idMap_.insert(ElementIdMapPair(theid, currentElement));
         XMLString::release(&theid);
      }
   }
   XMLString::release(&xid);
}

/**
 * Returns a DOMElement based on its id.
 * @param id The id of the element to find.
 * @return the DOMElement with the id or null.
 */
DOMElement* ColladaDoc::getElementById(string id) {
   DEBUG_M("Entering function... id='%s'", id.c_str());

   // See buildIDMap's comment...
   /*XMLCh* xid = XMLString::transcode(id.c_str());
   DOMElement* element = xmlDoc_->getElementById(xid);
   if(!element) {
      WARNING("ColladaDoc::getElementById couldn't find element with id '%s'", id);
   }
   XMLString::release(&xid);*/

   ElementIdMapIterator iter = idMap_.find(id);
   if(iter != idMap_.end()) {
      return iter->second;
   }

   return NULL;
}

/**
 * 
 */
DOMNodeList* ColladaDoc::getElementsByTagName(const DOMElement* element, string tag) {
   DEBUG_M("Entering function...");
   XMLCh* xtag = XMLString::transcode(tag.c_str());
   DOMNodeList* nl = element->getElementsByTagName(xtag);
   XMLString::release(&xtag);
   return nl;
}

shared_ptr<ColladaObject> ColladaDoc::getColladaObjectById(string id) {
   DEBUG_M("Entering function: id='%s'", id.c_str());
   shared_ptr<ColladaObject> colladaObject;
   DOMElement* element = getElementById(id);
   if(!element) {
      WARNING("Failed to find XML node with id '%s'", id.c_str());
      return shared_ptr<ColladaObject>();
   }

   #warning ['TODO']: Keep a list of colladaobjects and their ids for quick loading
   colladaObject = loadColladaObject(element);

   //TODO: Add to list of Objects/ids
   return colladaObject;
}

bool ColladaDoc::isString_(const XMLCh* tag1, string tag2) {
   DEBUG_V("Entering function...");
   XMLCh* tag2_c = XMLString::transcode(tag2.c_str());

   int result = XMLString::compareIString(tag1, tag2_c);

   XMLString::release(&tag2_c);
   if(result == 0) {
      return true;
   }
   return false;
}

shared_ptr<ColladaObject> ColladaDoc::loadColladaObject(const DOMElement* element) {
   DEBUG_M("Entering function...");

   const XMLCh* tagName = element->getTagName();
   shared_ptr<ColladaObject> colladaObject;

   char* tagName_c = XMLString::transcode(tagName);
   if(isString_(tagName, "visual_scene")) {
      shared_ptr<VisualScene> visualScene(loadVisualScene(element));
      colladaObject = visualScene;
   } else if(isString_(tagName, "node")) {
      shared_ptr<ColladaNode> node(loadColladaNode(element));
      colladaObject = node;
   } else if(isString_(tagName, "geometry")) {
      DEBUG_H("Load geometry");
      shared_ptr<Geometry> geometry(loadGeometry(element));
      colladaObject = geometry;
   } else if(isString_(tagName, "camera")) {
      DEBUG_H("Load camera");
      shared_ptr<ColladaCamera> camera(loadColladaCamera(element));
      colladaObject = camera;
   } else if(isString_(tagName, "light")) {
      DEBUG_H("Load light");
      shared_ptr<ColladaLight> light(loadColladaLight(element));
      colladaObject = light;
   } else if(isString_(tagName, "source")) {
      DEBUG_H("Load source");
      shared_ptr<Source> source(loadSource(element));
      colladaObject = source;
   } else if(isString_(tagName, "vertices")) {
      DEBUG_H("Load vertices");
      shared_ptr<Vertices> vertices(loadVertices(element));
      colladaObject = vertices;
   } else if(isString_(tagName, "material")) {
      DEBUG_H("Load material");
      shared_ptr<Material> material(loadMaterial(element));
      colladaObject = material;
   } else if(isString_(tagName, "effect")) {
      DEBUG_H("Load effect");
      shared_ptr<Effect> effect(loadEffect(element));
      colladaObject = effect;
   /*} else if(isString_(tagName, "sampler2D")) {
      DEBUG_H("Load sampler2D");
      shared_ptr<Sampler2D> sampler2D(loadSampler2D(element));
      colladaObject = sampler2D;*/
   } else if(isString_(tagName, "image")) {
      DEBUG_H("Load image");
      shared_ptr<Image> image(loadImage(element));
      colladaObject = image;
   } else {
      WARNING("Tried to load unsupported object '%s'.", tagName_c);
   }

   DEBUG_H("Loading: '%s'", tagName_c);

   XMLString::release(&tagName_c);
   if(colladaObject != NULL) {
      loadId(element, colladaObject.get());
      loadName(element, colladaObject.get());
   }

   return colladaObject;
   
}

shared_ptr<ColladaLight> ColladaDoc::loadColladaLight(const DOMElement* element) {
   DEBUG_M("Entering function...");
   WARNING("Stub function!");
   return shared_ptr<ColladaLight>();
}

shared_ptr<ColladaCamera> ColladaDoc::loadColladaCamera(const DOMElement* element) {
   DEBUG_M("Entering function...");
   WARNING("Stub function!");
   return shared_ptr<ColladaCamera>();
}

shared_ptr<Geometry> ColladaDoc::loadGeometry(const DOMElement* element) {
   DEBUG_M("Entering function...");
   // convex_mesh
   // mesh
   // spline
   // brep?
   shared_ptr<Geometry> geometry;
   
   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         const XMLCh* tagName = currentElement->getTagName();
         if(isString_(tagName, "mesh")) {
            shared_ptr<Mesh> mesh(loadMesh(currentElement));
            geometry = static_pointer_cast<Geometry, Mesh>(mesh);
            return mesh;
         } else if(isString_(tagName, "convex_mesh")) {
            WARNING("convex_mesh not supported!");
         } else if(isString_(tagName, "spline")) {
            WARNING("spline not supported!");
         } else if(isString_(tagName, "brep")) {
            WARNING("brep not supported!");
         }

         // TODO: Other types, convex_mesg, spline, brep, nodes...
      }
   }
   
   return shared_ptr<Geometry>();
}

shared_ptr<Mesh> ColladaDoc::loadMesh(const DOMElement* element) {
   DEBUG_M("Entering function...");

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();

   shared_ptr<Mesh> mesh(new Mesh);

   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         const XMLCh* tagName = currentElement->getTagName();
         if(isString_(tagName, "lines")) {
            WARNING("lines not yet supported.");
         } else if(isString_(tagName, "linestripes")) {
            WARNING("linestripes not yet supported.");
         } else if(isString_(tagName, "polygons")) {
            WARNING("polygons not yet supported.");
         } else if(isString_(tagName, "polylist")) {
            WARNING("polylist not yet supported.");
         } else if(isString_(tagName, "triangles")) {
            shared_ptr<Triangles> triangles = loadTriangles(currentElement);
            mesh->addPrimitive(triangles);
         } else if(isString_(tagName, "trifans")) {
            WARNING("trifans not yet supported.");
         } else if(isString_(tagName, "tristrips")) {
            WARNING("tristrips not yet supported.");
         }
      }
   }

   return mesh;
}

shared_ptr<Triangles> ColladaDoc::loadTriangles(const DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<Triangles> triangles(new Triangles);

   string count = getAttribute(element, "count");
   triangles->setCount(atoi(count.c_str()));

   int numInputs = 0;

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {

         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         const XMLCh* tagName = currentElement->getTagName();

         if(isString_(tagName, "input")) {
            numInputs++;
            shared_ptr<Input> input = loadInput(currentElement);
            string semantic = getAttribute(currentElement, "semantic");

            if(semantic.compare("VERTEX") == 0) {
               triangles->setVertex(input);
            } else if(semantic.compare("NORMAL") == 0) {
               triangles->setNormal(input);
            }
         } else if(isString_(tagName, "p")) {
            shared_ptr<vector<int>> primitives = loadPrimitives(currentElement);
            triangles->setPrimitives(primitives);
         }
      }
   }
   triangles->setInputCount(numInputs);

   string material = getAttribute(element, "material");
   /*if(materialUrl.length() > 0) {
      shared_ptr<ColladaObject> colladaObject(getColladaObjectById(materialUrl));
      //shared_ptr<Material> material(dynamic_pointer_cast<Material>(colladaObject));
      //triangles->setMaterial(material);
   }*/
   triangles->setMaterial(material);

   return triangles;
}

shared_ptr<vector<int>> ColladaDoc::loadPrimitives(const DOMElement* element) {
   DEBUG_M("Entering function...");

   const XMLCh* data_x = element->getTextContent();
   char* data_c = XMLString::transcode(data_x);

   shared_ptr<vector<int>> primitives(new vector<int>);

   //TODO: Do this in a C++ way... or at least look at using strtok_r...
   int i = 0;
   char* token = strtok(data_c, " ");
   while(token) {
      int num = atoi(token);
      primitives->push_back(num);
      i++;
      token = strtok(NULL, " ");
   }

   XMLString::release(&data_c);
   return primitives;
}

shared_ptr<Material> ColladaDoc::loadMaterial(const DOMElement* element) {
   DEBUG_M("Entering function...");

   DOMElement* instanceEffect = getElementByTagName(element, "instance_effect");
   if(!instanceEffect) {
      WARNING("No instance effect in material!");
      return shared_ptr<Material>();
   }

   shared_ptr<Material> material(new Material());
   string url = getAttribute(instanceEffect, "url");
   shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
   if(colladaObject) {
      shared_ptr<Effect> effect = dynamic_pointer_cast<Effect>(colladaObject);
      material->setEffect(effect);
   }

   return material;
}

void dumpElement(const DOMElement* element) {
   const XMLCh* tag_x = element->getTagName();
   char* tag_c = XMLString::transcode(tag_x);
   DEBUG_M("Element: '%s'", tag_c);
   XMLString::release(&tag_c);
}

shared_ptr<Effect> ColladaDoc::loadEffect(const DOMElement* element) {
   DEBUG_M("Entering function...");

   DOMElement* profileCommon = getElementByTagName(element, "profile_COMMON");
   if(!profileCommon) {
      WARNING("No profile_COMMON in effect.");
      return shared_ptr<Effect>();
   }

   DOMElement* technique = getElementByTagName(element, "technique");
   if(!technique) {
      WARNING("No technique in effect.");
      return shared_ptr<Effect>();
   }

   #warning ['TODO']: Handle other type (blinn).
   DOMElement* phongElement = getElementByTagName(element, "phong");
   if(!phongElement) {
      WARNING("No phong in effect.");
      return shared_ptr<Effect>();
   }

   shared_ptr<Phong> phong(new Phong);
   shared_ptr<Effect> effect(phong);

   // loadPhong
   DOMNodeList* children = phongElement->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {

         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         const XMLCh* tagName = currentElement->getTagName();

         DOMElement* data = getElementByTagName(currentElement, "color");
         if(!data) {
            data = getElementByTagName(currentElement, "float");
            //DEBUG_M("Got via secondry...");
         }
         if(!data) {
            data = getElementByTagName(currentElement, "texture");
            #warning ['TODO']: Handle texture'd images!
            if(data) {
               WARNING("Textures not yet handled!");
               string texcoord = getAttribute(data, "texcoord");
               string texture = getAttribute(data, "texture");
               shared_ptr<ColladaObject> sampler2D = loadEffectNewparamBySid_(profileCommon, texture);
               // TODO: Bind texture here...
               continue;
            }
         }
         if(!data) {
            WARNING("Unknown effect paramater data type...");
            continue;
         }
         #warning ['TODO']: The above float retrevial fails...

         dumpElement(currentElement);

         const XMLCh* data_x = data->getTextContent();
         char* data_c = XMLString::transcode(data_x);
         shared_ptr<vector<float>> floats = getFloats(data_c);
         XMLString::release(&data_c);

         if(isString_(tagName, "emission")) {
            phong->setEmission(floats->at(0), floats->at(1), floats->at(2), floats->at(3));
         } else if(isString_(tagName, "diffuse")) {
            phong->setDiffuse(floats->at(0), floats->at(1), floats->at(2), floats->at(3));
         } else if(isString_(tagName, "ambient")) {
            phong->setAmbient(floats->at(0), floats->at(1), floats->at(2), floats->at(3));
         } else if(isString_(tagName, "specular")) {
            phong->setSpecular(floats->at(0), floats->at(1), floats->at(2), floats->at(3));
         } else if(isString_(tagName, "shininess")) {
            phong->setShininess(floats->at(0));
         } else if(isString_(tagName, "reflective")) {
            phong->setReflective(floats->at(0), floats->at(1), floats->at(2), floats->at(3));
         } else if(isString_(tagName, "reflectivity")) {
            phong->setReflectivity(floats->at(0));
         } else if(isString_(tagName, "transparent")) {
            phong->setTransparent(floats->at(0), floats->at(1), floats->at(2), floats->at(3));
         } else if(isString_(tagName, "transparency")) {
            phong->setTransparency(floats->at(0));
         }
      }
   }

   return effect;
}

/**
 * Loads a newparam in a profileCommon.
 */
shared_ptr<ColladaObject> ColladaDoc::loadEffectNewparamBySid_(const DOMElement* profileCommon, string sid) {
   DEBUG_M("Entering function...");
   //return shared_ptr<ColladaObject>();


   DOMNodeList* elements = getElementsByTagName(profileCommon, "newparam");
   if(!elements) {
      WARNING("\tNo <newparam> tags found...");
      return shared_ptr<ColladaObject>();
   }

   //const XMLCh* tagName = profileCommon->getTagName();


   int length = elements->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = elements->item(i);
      DEBUG_M("The fantastic Mr. Loop strikes again, showing off his profound understanding of circular reasoning!");
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         string currentSid = getAttribute(currentElement, "sid");
         DEBUG_M("My name is '%s', and I love you.", sid.c_str());
         if(currentSid.compare(sid) == 0) {
            shared_ptr<ColladaObject> co = loadNewparam(profileCommon, currentElement);
         }
      }
   }
   DEBUG_M("Egads!, the end has occured!");
   return shared_ptr<ColladaObject>();
}

shared_ptr<ColladaObject> ColladaDoc::loadNewparam(const DOMElement* profileCommon, const DOMElement* node) {
   DEBUG_M("Entering function...");
   DOMNodeList* children = node->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         char *tagName = XMLString::transcode(currentElement->getTagName());
         string tagName_s = tagName;
         XMLString::release(&tagName);
         
         // We skip these
         if((tagName_s.compare("annotate") == 0) ||
            (tagName_s.compare("semantic") == 0) ||
            (tagName_s.compare("modifier") == 0)) {
            WARNING("<annotate>, <semantic> and <modifer> tags in <newparam> ignored...");
            continue;
         } else if((tagName_s.compare("float") == 0) || // And these
            (tagName_s.compare("float2") == 0) ||
            (tagName_s.compare("float3") == 0) ||
            (tagName_s.compare("float4") == 0)) {
            WARNING("float based <newparam>'s not supported");
            continue;
         } else if(tagName_s.compare("surface") == 0) { // We want these
            WARNING("<surface> not supported");
            return loadSurface(currentElement);
            continue;
         } else if(tagName_s.compare("sampler2D") == 0) {
            return loadSampler2D(profileCommon, currentElement);
         } else {
            WARNING("Unexpected '%s' in <newparam>", tagName_s.c_str());
            continue;
         }
      }
   }
   WARNING("Could now load newparam, missing its 'parameter_type' subtag.");
   return shared_ptr<ColladaObject>();
}

shared_ptr<ColladaObject> ColladaDoc::loadSampler2D(const DOMElement* profileCommon, const DOMElement* element) {
   DEBUG_M("Entering function...");

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         char *tagName = XMLString::transcode(currentElement->getTagName());
         string tagName_s = tagName;
         XMLString::release(&tagName);

         if(tagName_s.compare("source") == 0) {
            const XMLCh* data_x = currentElement->getTextContent();
            char* data_c = XMLString::transcode(data_x);
            string data_s = data_c;
            XMLString::release(&data_c);
            return loadEffectNewparamBySid_(profileCommon, data_s);
         }
      }
   }
   WARNING("Sampler2D failed to load...");
   return shared_ptr<ColladaObject>();
}

shared_ptr<ColladaObject> ColladaDoc::loadSurface(const DOMElement* element) {
   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         char *tagName = XMLString::transcode(currentElement->getTagName());
         string tagName_s = tagName;
         XMLString::release(&tagName);

         if(tagName_s.compare("init_from") == 0) {
            const XMLCh* data_x = currentElement->getTextContent();
            char* data_c = XMLString::transcode(data_x);
            string data_s = data_c;
            XMLString::release(&data_c);
            return getColladaObjectById(data_s);
         }
      }
   }
   WARNING("Sampler2D failed to load...");
   return shared_ptr<ColladaObject>();
}

shared_ptr<Image> ColladaDoc::loadImage(const DOMElement* element) {
   DEBUG_M("Entering function...");
   DOMNodeList* elements = getElementsByTagName(element, "init_from");
   if(!elements) {
      WARNING("\tNo <init_from> tag found...");
      return shared_ptr<Image>();
   }
   DOMNode* initFrom = elements->item(0);
   if(!initFrom) {
      WARNING("\t<init_from> error...");
      return shared_ptr<Image>();
   }
      
   const XMLCh* data_x = initFrom->getTextContent();
   char* data_c = XMLString::transcode(data_x);
   string data_s = data_c;
   XMLString::release(&data_c);
   
   shared_ptr<Image> image(new Image);
   image->setFilename(data_s);
   return image;
}

shared_ptr<Input> ColladaDoc::loadInput(const DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<Input> input(new Input);

   string offset = getAttribute(element, "offset");
   input->setOffset(atoi(offset.c_str()));
   
   string url = getAttribute(element, "source");
   shared_ptr<ColladaObject> sourceObj = getColladaObjectByUrl(url);
   shared_ptr<Source> source(static_pointer_cast<Source, ColladaObject>(sourceObj));
   input->setSource(source);
   
   loadId(element, input.get());
   loadName(element, input.get());

   return input;
}

#warning ['TODO']: Load the accessor first, that should pull in the float_array or whatever...
shared_ptr<Source> ColladaDoc::loadSource(const DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<Source> source(new Source);

   loadId(element, source.get());
   loadName(element, source.get());

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {

         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         const XMLCh* tagName = currentElement->getTagName();

         if(isString_(tagName, "float_array")) {
            const XMLCh* data_x = currentElement->getTextContent();
            char* data_c = XMLString::transcode(data_x);
            shared_ptr<vector<float>> floats(getFloats(data_c));
            source->setFloats(floats);
            XMLString::release(&data_c);
         } else if (isString_(tagName, "technique_common")) {
            loadSourceTechnique(currentElement, source);
         }
      }
   }

   return source;
}

void ColladaDoc::loadSourceTechnique(const DOMElement* element, shared_ptr<Source> source) {
   DEBUG_M("Entering function...");

   DOMNodeList* elements = getElementsByTagName(element, "accessor");

   // No translation on node...
   if(!elements) {
      return;
   }

   // Multiple translations on node...
   if(elements->getLength() > 1) {
      cerr << "ERROR: Multiple <translate>'s found in node..." << endl;
      return;
   }

   DOMNode* node = elements->item(0);
   if(!node) {
      cerr << "Weird. Could not get translation from element list..." << endl;
      return;
   }

   DOMElement* accessorElement = dynamic_cast<xercesc::DOMElement*>(node);
   string strideStr = getAttribute(accessorElement, "stride");
   source->setStride(atoi(strideStr.c_str()));
   
   int params = 0;
   DOMNodeList* children = node->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         
         const XMLCh* tagName = currentElement->getTagName();
         char* data_c = XMLString::transcode(tagName);

         DEBUG_M("LOOP: '%s'", data_c);

         if(isString_(tagName, "param")) {
            string name = getAttribute(currentElement, "name");
            if(name.compare("X") == 0) {
               DEBUG_M("SETXOFF");
               source->setXOff(params);
            } else if(name.compare("Y") == 0) {
               DEBUG_M("SETYOFF");
               source->setYOff(params);
            } else if(name.compare("Z") == 0) {
               DEBUG_M("SETZOFF");
               source->setZOff(params);
            }

            params++;
         }
         XMLString::release(&data_c);
      }
   }
}

shared_ptr<Vertices> ColladaDoc::loadVertices(const DOMElement* element) {
   DEBUG_M("Entering function...");

   /*XMLCh* tag = XMLString::transcode("input");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

   if(!elements) {
      ERROR("No <input> node found in file...");
      return shared_ptr<Vertices>();
   }

   int length = elements->getLength();
   if(length > 1) {
      WARNING("Multiple <input> node's found in file...");
      //return shared_ptr<Vertices>();
   }*/
   
   DOMNodeList* elements = getElementsByTagName(element, "input");
   if(!elements) {
      return shared_ptr<Vertices>();
   }

   int length = elements->getLength();
   shared_ptr<Vertices> vertices(new Vertices);
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = elements->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         string semantic = getAttribute(currentElement, "semantic");
         string url = getAttribute(currentElement, "source");
         if(semantic.compare("POSITION") == 0) {
            shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
            shared_ptr<Source> src(dynamic_pointer_cast<Source, ColladaObject>(colladaObject));
            vertices->setPosition(src);
         }
      }
   }

   return vertices;
}

/**
 * Gets an attribute from a DOMElement
 * @param element The DOMElement.
 * @param attribute The name of the attribute.
 * @return The atribute.
 */
string ColladaDoc::getAttribute(const DOMElement* element, string attribute) {
   DEBUG_V("Entering function... '%s'", attribute.c_str());
   XMLCh* attrx = XMLString::transcode(attribute.c_str());
   char *value_c = XMLString::transcode(element->getAttribute(attrx));
   string value_s = value_c;
   XMLString::release(&attrx);
   XMLString::release(&value_c);
   return value_s;
}

/**
 * Loads the Id into the ColladaObject.
 * @param element The element containing the objects ID.
 * @param id The object to apply the ID to.
 */
void ColladaDoc::loadId(const DOMElement* element, Id* id) {
   DEBUG_M("Entering function...");
   id->setId(getAttribute(element, "id"));
}

/**
 * Loads the Name into the ColladaObject.
 * @param element The element containting the objects name.
 * @param name The object to apply the name to.
 */
void ColladaDoc::loadName(const DOMElement* element, Name* name) {
   DEBUG_M("Entering function...");
   name->setName(getAttribute(element, "name"));
   DEBUG_M("Exiting function...");
}

/**
 * Loads a VisualScene from the DOMElement.
 * @param element The DOMElement.
 * @return A new VisualScene.
 */
shared_ptr<VisualScene> ColladaDoc::loadVisualScene(const DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<VisualScene> visualScene(new VisualScene());

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         shared_ptr<ColladaObject> colladaObject(getColladaObjectById(getAttribute(currentElement, "id")));
         shared_ptr<ColladaNode> node(static_pointer_cast<ColladaNode, ColladaObject>(colladaObject));
         visualScene->addColladaNode(node);
      }
   }
   return visualScene;
}

/**
 * Turns a string containing floats, into a float array.
 * @param text A string containing a float array.
 * @param floats A vector of floats.
 */
shared_ptr<vector<float>> ColladaDoc::getFloats(string text) {
   DEBUG_M("Entering function...");

   shared_ptr<vector<float>> floats(new vector<float>);

   char* data_clone = (char*)text.c_str();

   //TODO: Do this in a C++ way... or at least look at using strtok_r...
   int i = 0;
   char* token = strtok(data_clone, " ");

   while(token) {
      float f = atof(token);
      floats->push_back(f);
      i++;
      token = strtok(NULL, " ");
   }
   DEBUG_M("Exiting function...");
   return floats;
}

/**
 * Loads a translation from the DOMElement.
 * @param element The DOMElement.
 * @param position The object to apply the translation too.
 */
void ColladaDoc::loadTranslation(const DOMElement* element, Position* position) {
   DEBUG_M("Entering function...");

   DOMElement* node = getElementByTagName(element, "translate");
   if(!node) {
      return;
   }

   DOMNodeIterator* iterator = xmlDoc_->createNodeIterator(node, DOMNodeFilter::SHOW_TEXT, NULL, true);
   for(DOMNode* current = iterator->nextNode(); current != 0; current = iterator->nextNode() ) {
      const XMLCh* data_x = current->getTextContent();
      char* data_c = XMLString::transcode(data_x);

      shared_ptr<vector<float>> floats(getFloats(data_c));

      position->setX(floats->at(0));
      position->setY(floats->at(1));
      position->setZ(floats->at(2));

      XMLString::release(&data_c);
   }
}

/**
 * 
 */
void ColladaDoc::loadScale(const DOMElement* element, Scale* scale) {
   DEBUG_M("Entering function...");

   DOMElement* node = getElementByTagName(element, "scale");
   if(!node) {
      return;
   }

   DOMNodeIterator* iterator = xmlDoc_->createNodeIterator(node, DOMNodeFilter::SHOW_TEXT, NULL, true);
   for(DOMNode* current = iterator->nextNode(); current != 0; current = iterator->nextNode() ) {
      const XMLCh* data_x = current->getTextContent();
      char* data_c = XMLString::transcode(data_x);

      shared_ptr<vector<float>> floats(getFloats(data_c));

      scale->setScaleXYZ(floats->at(0), floats->at(1), floats->at(2));

      XMLString::release(&data_c);
   }
}

/**
 * Loads a specific rotation from the DOMElement.
 * @param element The DOMElement.
 * @param rotation The object to apply the rotation too.
 */
void ColladaDoc::loadRotation(const DOMElement* element, RotationGL* rotation, int number) {
   DEBUG_M("Entering function...");
   const XMLCh* data_x = element->getTextContent();
   char* data_c = XMLString::transcode(data_x);

   shared_ptr<vector<float>> floats(getFloats(data_c));

   rotation->setRotationGL(number, floats->at(0), floats->at(1), floats->at(2), floats->at(3));

   XMLString::release(&data_c);
}

/**
 * Loads the rotations from the DOMElement.
 * @param element The DOMElement.
 * @param rotation The object to apply the rotations too.
 */
void ColladaDoc::loadRotations(const DOMElement* element, RotationGL* rotation) {
   DEBUG_M("Entering function...");

   XMLCh* tag = XMLString::transcode("rotate");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

   // No rotations on node...
   if(!elements) {
      return;
   }

   int length = elements->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = elements->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         loadRotation(currentElement, rotation, i);
      }
   }
}

/**
 * Loads a ColladaNode from the DOMElement.
 * @param element The DOMElement.
 * @return A new ColladaNode.
 */
shared_ptr<ColladaNode> ColladaDoc::loadColladaNode(const DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<ColladaNode> node(new ColladaNode());
  
   loadTranslation(element, node.get());
   loadRotations(element, node.get());
   loadScale(element, node.get());
   loadInstances(element, node.get());
   return node;
}

void ColladaDoc::loadInstances(const DOMElement* element, ColladaNode* node) {
   DEBUG_M("Entering function...");

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         shared_ptr<ColladaObject> instance = loadInstance(currentElement, node);
         if(instance) {
            node->addInstance(instance);
         }
      }
   }
}


shared_ptr<InstanceGeometry> ColladaDoc::loadInstanceGeometry(const DOMElement* element) {
      DEBUG_M("Entering function...");
      shared_ptr<InstanceGeometry> ig(new InstanceGeometry);

      // Get the real geometry node
      string url = getAttribute(element, "url");
      shared_ptr<ColladaObject> colladaObject = getColladaObjectByUrl(url);
      shared_ptr<Geometry> geometry(static_pointer_cast<Geometry, ColladaObject>(colladaObject));
      ig->setGeometry(geometry);
     
      #warning ['TODO']: Bind materials!
      loadInstanceGeometry_BindMaterials_(ig, element);
      return ig;
}

void ColladaDoc::loadInstanceGeometry_BindMaterials_(shared_ptr<InstanceGeometry> ig, const DOMElement* element) {
   XMLCh* tag = XMLString::transcode("bind_material");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

   // No materials on instance geometry...
   if(!elements) {
      return;
   }

   int length = elements->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = elements->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         loadInstanceGeometry_BindMaterial_(ig, currentElement);
      }
   }
}

void ColladaDoc::loadInstanceGeometry_BindMaterial_(shared_ptr<InstanceGeometry> ig, const DOMElement* element) {
   DEBUG_M("Entering function...");
   
   DOMElement* tce = getElementByTagName(element, "technique_common");
   if(!tce) {
      WARNING("No <technique_common> in <bind_material>.");
      return;
   }

   DOMElement* ime = getElementByTagName(tce, "instance_material");
   if(!ime) {
      WARNING("No <instance_material> in <technique_common>.");
      return;
   }

   string symbol = getAttribute(ime, "symbol");
   string target = getAttribute(ime, "target");

   DOMElement* bvie = getElementByTagName(ime, "bind_vertex_input");
   if(!bvie) {
      WARNING("No <bind_vertex_input> in <instance_material>.");
      return;
   }

   string input_semantic = getAttribute(bvie, "input_semantic");
   string input_set = getAttribute(bvie, "input_set");
   string semantic = getAttribute(bvie, "semantic");
   
   shared_ptr<ColladaObject> colladaObject = getColladaObjectByUrl(target);
   shared_ptr<Material> material(static_pointer_cast<Material, ColladaObject>(colladaObject));
   ig->addInstanceMaterial(symbol, material);
}

shared_ptr<ColladaObject> ColladaDoc::loadInstance(const DOMElement* element, ColladaNode* node) {
   DEBUG_M("Entering function...");

   string instance_geometry_s = "instance_geometry";
   //XMLCh* light_tag = XMLString::transcode("instance_light");
   string url = getAttribute(element, "url");

   // Not an instance...
   if(url.length() == 0) {
      return shared_ptr<ColladaObject>();
   }

   const XMLCh* tagName = element->getTagName();
   XMLCh* geometry_tag = XMLString::transcode(instance_geometry_s.c_str());

   #warning ['TODO']: Add translate, camera, node, scale, etc... 
   /*if(XMLString::compareIString(tagName, geometry_tag) == 0) {
      //Geometry* geometry = loadGeometry(element);
      //colladaObject = geometry;
   } else if(XMLString::compareIString(tagName, light_tag) == 0) {
      //Light* light = loadLight(element);
      //colladaObject = light;
   } else {
      colladaObject = getColladaObjectByUrl(url);
   }*/

   //shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
   shared_ptr<ColladaObject> colladaObject;

   if(XMLString::compareIString(tagName, geometry_tag) == 0) {
      //shared_ptr<ColladaObject> colladaObject = instanceGeometry;
      //shared_ptr<ColladaObject> colladaObject(dynamic_pointer_cast<ColladaObject, InstanceGeometry>(instanceGeometry));
      //shared_ptr<ColladaObject> colladaObject = loadInstanceGeometry(element);
      shared_ptr<InstanceGeometry> instanceGeometry = loadInstanceGeometry(element);
      //shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
      colladaObject = instanceGeometry;
      
      //XMLString::release(&geometry_tag);
      //return instanceGeometry;
   } else {
      shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
      //XMLString::release(&geometry_tag);
      //return colladaObject;
   }
   XMLString::release(&geometry_tag);
   return colladaObject;
   // TODO: Handle instance_geometry's bind_material (instance_controller)

   

   /*char* testtag = XMLString::transcode(tagName);
   DEBUG_H("%s", testtag);*/

   //XMLString::release(&tagName);
   //XMLString::release(&geometry_tag);
   //XMLString::release(&light_tag);

   //loadId(element, colladaObject);
   //loadName(element, colladaObject);

   //return colladaObject;
}

// instance_camera x
// instance_controller +
// instance_geometry +
// instance_light x
// instance_node x

DOMElement* ColladaDoc::getElementByTagName(const DOMElement* element, string tag) {
   DOMNodeList* elements = getElementsByTagName(element, tag);
   if(!elements) {
      ERROR("No node with tag '%s' found...", tag.c_str());
      return NULL;
   }
   
   if(elements->getLength() > 1) {
      ERROR("Multiple node's found when expecting 1...");
      return NULL;
   }

   DOMNode* node = elements->item(0);
   if(!node) {
      //ERROR("Weird. Could not get node from nodelist... tag: '%s'", tag.c_str());
      //dumpElement(element);
      
      return NULL;
   }

   return dynamic_cast<xercesc::DOMElement*>(elements->item(0));
}

/**
 * Gets the main Scene of the Collada file.
 */
shared_ptr<Scene> ColladaDoc::getScene() {
   DEBUG_M("Entering function...");

   if(scene_) {
      return scene_;
   }

   DOMElement* node = getElementByTagName(xmlDoc_->getDocumentElement(), "scene");

   #warning ['TODO']: Keep a copy of the scene for quick retrevial...

   shared_ptr<Scene> scene_(new Scene());
   #warning ['TODO']: Load the scene into the Scene node...

   DOMNodeList* children = node->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);

         char *tagName = XMLString::transcode(currentElement->getTagName());
         XMLCh* url_x = XMLString::transcode("url");
         char *url = XMLString::transcode(currentElement->getAttribute(url_x));
         if(XMLString::compareIString(tagName, "instance_visual_scene") == 0) {
            DEBUG_H("getScene visual url: '%s'", url);
            shared_ptr<VisualScene> visualScene(getVisualScene(url));
            DEBUG_H(" got scene");
            scene_->setVisualScene(visualScene);
         } else if(XMLString::compareIString(tagName, "instance_physics_scene") == 0) {
            // TODO: Load physics scene...
            //PhysicsScene* physicsScene = getPhysicsScene(id);
            //scene->setPhysicsScene(physicsScene);
         }
         XMLString::release(&tagName);
         XMLString::release(&url);
         XMLString::release(&url_x);
      }
   }

   return scene_;
}

shared_ptr<VisualScene> ColladaDoc::getVisualScene(string url) {
   DEBUG_M("Entering function... url='%s'", url.c_str());
   shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
   shared_ptr<VisualScene> visualScene(static_pointer_cast<VisualScene, ColladaObject>(colladaObject));
   #warning ['TODO']: Safer dynamic cast?
   return visualScene;
}

shared_ptr<ColladaObject> ColladaDoc::getColladaObjectByUrl(string url) {
   DEBUG_M("Entering function... url='%s'", url.c_str());
   if(url.length() == 0) {
      WARNING("Tried to load blank url...");
      return shared_ptr<ColladaObject>();
   }

   if(!ColladaUrl::isInternal(url)) {
      DEBUG_H("It's an external url");
      if(!manager_) {
         // TODO: Alternativly, spawn its own manager...
         return shared_ptr<ColladaObject>();
      }
      return manager_->getColladaObjectByUrl(url);
   }

   return getColladaObjectById(ColladaUrl::getId(url));
}

/**
 * Returns a Collada object based on the xml file.
 */
shared_ptr<Collada> ColladaDoc::getCollada() {
   DEBUG_M("Entering function...");
   if(!collada_) {
      collada_ = shared_ptr<Collada>(new Collada());
      collada_->setScene(getScene());
      collada_->setFilename(url_);
   }
   return collada_;
}
