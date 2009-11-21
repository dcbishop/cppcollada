#include "ColladaDoc.hpp"

#include "ColladaManager.hpp"
#include "ColladaDocManager.hpp"
#include "ColladaUrl.hpp"

#include "Collada.hpp"
#include "Scene.hpp"
#include "ColladaNode.hpp"
#include "VisualScene.hpp"
#include "ColladaObject.hpp"
#include "Position.hpp"
#include "Rotation.hpp"
#include "Scale.hpp"
#include "RotationGL.hpp"
#include "Geometry.hpp"
#include "ColladaCamera.hpp"
#include "ColladaLight.hpp"
#include "Mesh.hpp"
#include "Vertices.hpp"
#include "Triangles.hpp"
#include "Source.hpp"

#include "console.h"

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
}

/**
 * Loads a COLLADA document from a URL.
 * @param url The URL of the document to load.
 */
DOMDocument* ColladaDoc::loadColladaDoc(string url) {
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
DOMDocument* ColladaDoc::loadColladaDocFile(string filename) {
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
DOMNodeList* ColladaDoc::getElementsByTagName(string tag) {
   DEBUG_M("Entering function...");
   XMLCh* xtag = XMLString::transcode(tag.c_str());
   return xmlDoc_->getElementsByTagName(xtag);
   XMLString::release(&xtag);
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
   DEBUG_H("Entering function...");
   XMLCh* tag2_c = XMLString::transcode(tag2.c_str());

   int result = XMLString::compareIString(tag1, tag2_c);

   XMLString::release(&tag2_c);
   if(result == 0) {
      return true;
   }
   return false;
}

shared_ptr<ColladaObject> ColladaDoc::loadColladaObject(DOMElement* element) {
   DEBUG_M("Entering function...");

   const XMLCh* tagName = element->getTagName();
   shared_ptr<ColladaObject> colladaObject;

   const char* tagName_c = XMLString::transcode(tagName);
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
   } else {
      WARNING("Tried to load unsupported object'%s'", tagName_c);
   }

   DEBUG_H("Loading: '%s'", tagName_c);

   if(colladaObject != NULL) {
      loadId(element, colladaObject.get());
      loadName(element, colladaObject.get());
   }

   return colladaObject;
   
}

shared_ptr<ColladaLight> ColladaDoc::loadColladaLight(DOMElement* element) {
   DEBUG_M("Entering function...");
   WARNING("Stub function!");
   return shared_ptr<ColladaLight>();
}

shared_ptr<ColladaCamera> ColladaDoc::loadColladaCamera(DOMElement* element) {
   DEBUG_M("Entering function...");
   WARNING("Stub function!");
   return shared_ptr<ColladaCamera>();
}

shared_ptr<Geometry> ColladaDoc::loadGeometry(DOMElement* element) {
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

shared_ptr<Mesh> ColladaDoc::loadMesh(DOMElement* element) {
   DEBUG_M("Entering function...");

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   DEBUG_M("Children: %i", length);
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
            WARNING("triangles not yet supported.");
            shared_ptr<Triangles> triangles = loadTriangles(currentElement);
         } else if(isString_(tagName, "trifans")) {
            WARNING("trifans not yet supported.");
         } else if(isString_(tagName, "tristrips")) {
            WARNING("tristrips not yet supported.");
         }
      }
   }

   return shared_ptr<Mesh>();
}

shared_ptr<Triangles> ColladaDoc::loadTriangles(DOMElement* element) {
   DEBUG_M("Entering function...");
   WARNING("STUB FUNCTION!");

   shared_ptr<Triangles> triangles(new Triangles);

   string count = getAttribute(element, "count");
   string material = getAttribute(element, "material");

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {

         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         const XMLCh* tagName = currentElement->getTagName();

         if(isString_(tagName, "input")) {
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

   return shared_ptr<Triangles>();
}

shared_ptr<vector<int>> ColladaDoc::loadPrimitives(DOMElement* element) {
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

   return primitives;
}

shared_ptr<Input> ColladaDoc::loadInput(DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<Input> input(new Input);

   string offset = getAttribute(element, "offset");
   input->setOffset(atoi(offset.c_str()));
   
   string url = getAttribute(element, "source");
   shared_ptr<ColladaObject> sourceObj = getColladaObjectByUrl(url);
   shared_ptr<Source> source(static_pointer_cast<Source, ColladaObject>(sourceObj));
   input->setSource(source);

   return input;
}

#warning ['TODO']: Load the accessor first, that should pull in the float_array or whatever...
shared_ptr<Source> ColladaDoc::loadSource(DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<Source> source(new Source);

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
            source->setFloats(getFloats(data_c));
            XMLString::release(&data_c);
         } else if (isString_(tagName, "technique_common")) {
            loadSourceTechnique(currentElement, source);
         }
      }
   }

   return source;
}

void ColladaDoc::loadSourceTechnique(DOMElement* element, shared_ptr<Source> source) {
   DEBUG_M("Entering function...");

   XMLCh* tag = XMLString::transcode("accessor");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

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
   DEBUG_M("Children: %i", length);
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

shared_ptr<Vertices> ColladaDoc::loadVertices(DOMElement* element) {
   DEBUG_M("Entering function...");
   WARNING("STUB FUNCTION!");

   XMLCh* tag = XMLString::transcode("input");
   DOMNodeList* elements = xmlDoc_->getElementsByTagName(tag);
   XMLString::release(&tag);

   if(!elements) {
      ERROR("No <input> node found in file...");
      return shared_ptr<Vertices>();
   }

   if(elements->getLength() > 1) {
      ERROR("Multiple <input> node's found in file...");
      return shared_ptr<Vertices>();
   }

   return shared_ptr<Vertices>();
}


/*string ColladaDoc::getStringFromXMLCh(XMLCh* xmlch) {
   char* ch = XMLString::transcode(xmlch);
   string str = ch;
   XMLString::release(&ch);
   return ch;
}*/

/**
 * Gets an attribute from a DOMElement
 * @param element The DOMElement.
 * @param attribute The name of the attribute.
 * @return The atribute.
 */
string ColladaDoc::getAttribute(DOMElement* element, string attribute) {
   DEBUG_M("Entering function... '%s'", attribute.c_str());
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
void ColladaDoc::loadId(DOMElement* element, Id* id) {
   DEBUG_M("Entering function...");
   id->setId(getAttribute(element, "id"));
}

/**
 * Loads the Name into the ColladaObject.
 * @param element The element containting the objects name.
 * @param name The object to apply the name to.
 */
void ColladaDoc::loadName(DOMElement* element, Name* name) {
   DEBUG_M("Entering function...");
   name->setName(getAttribute(element, "name"));
}

/**
 * Loads a VisualScene from the DOMElement.
 * @param element The DOMElement.
 * @return A new VisualScene.
 */
shared_ptr<VisualScene> ColladaDoc::loadVisualScene(DOMElement* element) {
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
   return floats;
}

/**
 * Loads a translation from the DOMElement.
 * @param element The DOMElement.
 * @param position The object to apply the translation too.
 */
void ColladaDoc::loadTranslation(DOMElement* element, Position* position) {
   DEBUG_M("Entering function...");

   XMLCh* tag = XMLString::transcode("translate");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

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
void ColladaDoc::loadScale(DOMElement* element, Scale* scale) {
   DEBUG_M("Entering function...");

   XMLCh* tag = XMLString::transcode("scale");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

   // No scale on node...
   if(!elements) {
      return;
   }

   // Multiple scale on node...
   if(elements->getLength() > 1) {
      cerr << "ERROR: Multiple <scale>'s found in node..." << endl;
      return;
   }

   DOMNode* node = elements->item(0);
   if(!node) {
      cerr << "Weird. Could not get scale from element list..." << endl;
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
void ColladaDoc::loadRotation(DOMElement* element, RotationGL* rotation, int number) {
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
void ColladaDoc::loadRotations(DOMElement* element, RotationGL* rotation) {
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
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
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
shared_ptr<ColladaNode> ColladaDoc::loadColladaNode(DOMElement* element) {
   DEBUG_M("Entering function...");

   shared_ptr<ColladaNode> node(new ColladaNode());
  
   loadTranslation(element, node.get());
   loadRotations(element, node.get());
   loadScale(element, node.get());
   loadInstances(element, node.get());
   return node;
}

void ColladaDoc::loadInstances(DOMElement* element, ColladaNode* node) {
   DEBUG_M("Entering function...");

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentNode = children->item(i);
      if(currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
         shared_ptr<ColladaObject> instance = loadInstance(currentElement, node);
         if(instance != NULL) {
            //TODO: node->addInstance(instance); or whatever...
         }
      }
   }
}

shared_ptr<ColladaObject> ColladaDoc::loadInstance(DOMElement* element, ColladaNode* node) {
   DEBUG_M("Entering function...");

   //const XMLCh* tagName = element->getTagName();
   //XMLCh* geometry_tag = XMLString::transcode("instance_geometry");
   //XMLCh* light_tag = XMLString::transcode("instance_light");
   string url = getAttribute(element, "url");

   // Not an instance...
   if(url.length() == 0) {
      return shared_ptr<ColladaObject>();
   }

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

   // TODO: Handle instance_geometry's bind_material (instance_controller)

   shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));

   /*char* testtag = XMLString::transcode(tagName);
   DEBUG_H("%s", testtag);*/

   //XMLString::release(&tagName);
   //XMLString::release(&geometry_tag);
   //XMLString::release(&light_tag);

   //loadId(element, colladaObject);
   //loadName(element, colladaObject);

   return colladaObject;
}

// instance_camera x
// instance_controller +
// instance_geometry +
// instance_light x
// instance_node x

/**
 * Gets the main Scene of the Collada file.
 */
shared_ptr<Scene> ColladaDoc::getScene() {
   DEBUG_M("Entering function...");

   if(scene_) {
      return scene_;
   }
   // TODO: Check for an already loaded Scene!

   XMLCh* tag = XMLString::transcode("scene");
   DOMNodeList* elements = xmlDoc_->getElementsByTagName(tag);
   XMLString::release(&tag);

   if(!elements) {
      ERROR("No <scene> node found in file...");
      return shared_ptr<Scene>();
   }
   
   if(elements->getLength() > 1) {
      ERROR("Multiple <scene> node's found in file...");
      return shared_ptr<Scene>();
   }

   DOMNode* node = elements->item(0);
   if(!node) {
      ERROR("Weird. Could not get node from <scene> list...");
      return shared_ptr<Scene>();
   }

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
   }
   return collada_;
}
