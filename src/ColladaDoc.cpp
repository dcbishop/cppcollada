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



ColladaDoc::ColladaDoc(ColladaDocManager* manager, string url) {
   url_ = url;
   xmlDoc_ = loadColladaDoc(url);
   manager_ = manager;
   buildIdMap_();
}

ColladaDoc::~ColladaDoc() {
   // TODO: Delete xmlDoc_ here?
   delete parser_;
}

/**
 * Loads a COLLADA document from a URL.
 * @param url The URL of the document to load.
 */
DOMDocument* ColladaDoc::loadColladaDoc(string url) {
   #warning ['TODO']: Process other URL formats...

   // Check to ensure we are loading a file://
   /*const string fileSep = "file://";
   size_t fileIndex = url.find(fileSep);
   if(fileIndex != 0) { //If not we die...
      cerr << "Unsupported URL sceme!" << endl;
      return NULL;
   }*/

   /*string localFilename = url.substr(fileSep.length()-1);
   string localFilename = ColladaUrl::getFilename(url);
   cout << localFilename << endl;*/
   return loadColladaDocFile(ColladaUrl::getFilename(url));
}

/**
 * Loads a collada document from a local file.
 * @param filename The filename of the document to load.
 */
DOMDocument* ColladaDoc::loadColladaDocFile(string filename) {
   cout << "DEBUG: loadColladaDocFile(" << filename << ")" << endl;
   try {
      XMLPlatformUtils::Initialize();
   } catch (const XMLException& e) {
      char* errMsg = XMLString::transcode(e.getMessage());
      cout << "Xerces XML ERROR: " << errMsg << endl;
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
      cout << "Xerces XML ERROR: " << errMsg << endl;
      XMLString::release(&errMsg);
      return NULL;
   } catch (const DOMException& e) {
      char* errMsg = XMLString::transcode(e.msg);
      cout << "Xerces DOM ERROR: " << errMsg << endl;
      XMLString::release(&errMsg);
      return NULL;
   } catch (...) {
      cout << "Unknown Xerces ERROR...\n";
      return NULL;
   }

   DOMDocument* xmlDoc = parser_->getDocument();
   DOMElement* elementRoot = xmlDoc->getDocumentElement();
   if(!elementRoot) {
      cout << "Empty XML document...\n";
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
   cout << "DEBUG: ColladaDoc::buildIdMap_()\n";
   DOMElement* elementRoot = xmlDoc_->getDocumentElement();
   DOMTreeWalker *walker = xmlDoc_->createTreeWalker(elementRoot, DOMNodeFilter::SHOW_ELEMENT, NULL, true);
   XMLCh* xid = XMLString::transcode("id");
   for(DOMNode *currentColladaNode = walker->nextNode(); currentColladaNode != 0; currentColladaNode = walker->nextNode()) {
      DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentColladaNode);
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
   cout << "DEBUG: ColladaDoc::getElementById(" << id << ")\n";

   // See buildIDMap's comment...
   /*XMLCh* xid = XMLString::transcode(id.c_str());
   DOMElement* element = xmlDoc_->getElementById(xid);
   if(!element) {
      cout << "WARNING: ColladaDoc::getElementById couldn't find element with id '" << id << "'\n";
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
   XMLCh* xtag = XMLString::transcode(tag.c_str());
   return xmlDoc_->getElementsByTagName(xtag);
   XMLString::release(&xtag);
}

shared_ptr<ColladaObject> ColladaDoc::getColladaObjectById(string id) {
   cout << "DEBUG: ColladaDoc::getColladaObjectById(" << id << ")\n";
   shared_ptr<ColladaObject> colladaObject;
   DOMElement* element = getElementById(id);
   if(!element) {
      cout << "WARNING: Failed to find XML node with id '" << id << "'\n";
      return shared_ptr<ColladaObject>();
   }

   #warning ['TODO']: Keep a list of colladaobjects and their ids for quick loading
   colladaObject = loadColladaObject(element);

   //TODO: Add to list of Objects/ids
   return colladaObject;
}

bool ColladaDoc::isString_(const XMLCh* tag1, string tag2) {
   XMLCh* tag2_c = XMLString::transcode(tag2.c_str());

   int result = XMLString::compareIString(tag1, tag2_c);

   XMLString::release(&tag2_c);
   if(result == 0) {
      return true;
   }
   return false;
}

shared_ptr<ColladaObject> ColladaDoc::loadColladaObject(DOMElement* element) {
   cout << "DEBUG: ColladaDoc::loadColladaObject(...)\n";

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
      cout << "Load geometry\n";
      shared_ptr<Geometry> geometry(loadGeometry(element));
      colladaObject = geometry;
   } else if(isString_(tagName, "camera")) {
      cout << "Load camera\n";
   } else {
      cout << "WARNING: Tried to load unsupported object '" << tagName_c << "'\n";
   }

   cout << "Loading: " << tagName_c << endl;

   if(colladaObject != NULL) {
      loadId(element, colladaObject.get());
      loadName(element, colladaObject.get());
   }

   return colladaObject;
   
}

shared_ptr<Geometry> ColladaDoc::loadGeometry(DOMElement* element) {
   // convex_mesh
   // mesh
   // spline
   // brep?
   return shared_ptr<Geometry>();
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
   cout << "DEBUG: ColladaDoc::loadId(...)\n";
   id->setId(getAttribute(element, "id"));
}

/**
 * Loads the Name into the ColladaObject.
 * @param element The element containting the objects name.
 * @param name The object to apply the name to.
 */
void ColladaDoc::loadName(DOMElement* element, Name* name) {
   cout << "DEBUG: ColladaDoc::loadName(...)\n";
   name->setName(getAttribute(element, "name"));
}

/**
 * Loads a VisualScene from the DOMElement.
 * @param element The DOMElement.
 * @return A new VisualScene.
 */
shared_ptr<VisualScene> ColladaDoc::loadVisualScene(DOMElement* element) {
   cout << "DEBUG: ColladaDoc::loadVisualScene(...)\n";
   shared_ptr<VisualScene> visualScene(new VisualScene());

   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentColladaNode = children->item(i);
      if(currentColladaNode->getNodeType() && currentColladaNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentColladaNode);
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
 * @param count The number of floats.
 */
float* ColladaDoc::getFloatArray(string text, int count) {
   float* array = new float[count];

   char* data_clone = (char*)text.c_str();  //TODO: How safe is this?

   //TODO: Do this in a C++ way... or at least look at using strtok_r...
   int i = 0;
   char* token = strtok(data_clone, " ");
   while(token) {
      float f = atof(token);
      if(i > count) {
         cout << "ERROR: ColladaDoc::getFloatArray: Too many elements in array...\n";
         return array;
      }
      array[i] = f;
      i++;
      token = strtok(NULL, " ");
   }
   
   return array;
}

/**
 * Loads a translation from the DOMElement.
 * @param element The DOMElement.
 * @param position The object to apply the translation too.
 */
void ColladaDoc::loadTranslation(DOMElement* element, Position* position) {
   cout << "DEBUG: loadTranslation(...)\n";

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

      float* array = getFloatArray(data_c, 3);
      position->setX(array[0]);
      position->setY(array[1]);
      position->setZ(array[2]);

      delete(array);
      XMLString::release(&data_c);
   }
}

/**
 * 
 */
void ColladaDoc::loadScale(DOMElement* element, Scale* scale) {
   cout << "DEBUG: loadScale(...)\n";

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

      float* array = getFloatArray(data_c, 3);
      scale->setScaleXYZ(array[0], array[1], array[2]);

      delete(array);
      XMLString::release(&data_c);
   }
}

/**
 * Loads a specific rotation from the DOMElement.
 * @param element The DOMElement.
 * @param rotation The object to apply the rotation too.
 */
void ColladaDoc::loadRotation(DOMElement* element, RotationGL* rotation, int number) {
   const XMLCh* data_x = element->getTextContent();
   char* data_c = XMLString::transcode(data_x);

   float* array = getFloatArray(data_c, 4);
   rotation->setRotationGL(number, array[0], array[1], array[2], array[3]);

   delete(array);
   XMLString::release(&data_c);
}

/**
 * Loads the rotations from the DOMElement.
 * @param element The DOMElement.
 * @param rotation The object to apply the rotations too.
 */
void ColladaDoc::loadRotations(DOMElement* element, RotationGL* rotation) {
   cout << "DEBUG: loadRotations(...)\n";

   XMLCh* tag = XMLString::transcode("rotate");
   DOMNodeList* elements = element->getElementsByTagName(tag);
   XMLString::release(&tag);

   // No rotations on node...
   if(!elements) {
      return;
   }

   int length = elements->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentColladaNode = elements->item(i);
      if(currentColladaNode->getNodeType() && currentColladaNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentColladaNode);
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
   cout << "DEBUG: loadColladaNode(...)\n";
   shared_ptr<ColladaNode> node(new ColladaNode());
  
   loadTranslation(element, node.get());
   loadRotations(element, node.get());
   loadScale(element, node.get());
   loadInstances(element, node.get());
   return node;
}

void ColladaDoc::loadInstances(DOMElement* element, ColladaNode* node) {
   cout << "DEBUG: ColladaDoc::loadInstances(...)\n";
   DOMNodeList* children = element->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentColladaNode = children->item(i);
      if(currentColladaNode->getNodeType() && currentColladaNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentColladaNode);
         shared_ptr<ColladaObject> instance = loadInstance(currentElement, node);
         if(instance != NULL) {
            //TODO: node->addInstance(instance); or whatever...
         }
      }
   }
}

shared_ptr<ColladaObject> ColladaDoc::loadInstance(DOMElement* element, ColladaNode* node) {
   cout << "DEBUG: ColladaDoc::loadInstance(...)\n";

   const XMLCh* tagName = element->getTagName();
   XMLCh* geometry_tag = XMLString::transcode("instance_geometry");
   XMLCh* light_tag = XMLString::transcode("instance_light");
   string url = getAttribute(element, "url");

   // Not an instance...
   if(url.length() == 0) {
      return shared_ptr<ColladaObject>();
   }

   #warning ['TODO']: Add translate, camera, node, scale, etc... 
   /*if(XMLString::compareIString(tagName, geometry_tag) == 0) {
      cout << "Geometry\n";
      //Geometry* geometry = loadGeometry(element);
      //colladaObject = geometry;
   } else if(XMLString::compareIString(tagName, light_tag) == 0) {
      cout << "Light\n";
      //Light* light = loadLight(element);
      //colladaObject = light;
   } else {
      colladaObject = getColladaObjectByUrl(url);
   }*/

   // TODO: Handle instance_geometry's bind_material (instance_controller)

   shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));

   char* testtag = XMLString::transcode(tagName);
   cout << testtag << endl;

   //XMLString::release(&tagName);
   XMLString::release(&geometry_tag);
   XMLString::release(&light_tag);

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
   cout << "DEBUG: ColladaDoc::getScene()" << endl;
   // TODO: Check for an already loaded Scene!
   
   XMLCh* tag = XMLString::transcode("scene");
   DOMNodeList* elements = xmlDoc_->getElementsByTagName(tag);
   XMLString::release(&tag);

   if(!elements) {
      cerr << "No <scene> node found in file..." << endl;
      return shared_ptr<Scene>();
   }
   
   if(elements->getLength() > 1) {
      cerr << "Multiple <scene> node's found in file..." << endl;
      return shared_ptr<Scene>();
   }

   DOMNode* node = elements->item(0);
   if(!node) {
      cerr << "Weird. Could not get node from <scene> list..." << endl;
      return shared_ptr<Scene>();
   }

   #warning ['TODO']: Keep a copy of the scene for quick retrevial...

   shared_ptr<Scene> scene(new Scene());
   #warning ['TODO']: Load the scene into the Scene node...

   DOMNodeList* children = node->getChildNodes();
   int length = children->getLength();
   for(int i = 0; i < length; i++) {
      DOMNode* currentColladaNode = children->item(i);
      if(currentColladaNode->getNodeType() && currentColladaNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
         DOMElement* currentElement = dynamic_cast<xercesc::DOMElement*>(currentColladaNode);

         char *tagName = XMLString::transcode(currentElement->getTagName());
         XMLCh* url_x = XMLString::transcode("url");
         char *url = XMLString::transcode(currentElement->getAttribute(url_x));
         cout << "DEBUG: getScene " << tagName << endl;
         if(XMLString::compareIString(tagName, "instance_visual_scene") == 0) {
            cout << "DEBUG: getScene visual url: '" << url << "'\n";
            shared_ptr<VisualScene> visualScene(getVisualScene(url));
            cout << "DEBUG: got scene\n";
            scene->setVisualScene(visualScene);
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
   return scene;
}

shared_ptr<VisualScene> ColladaDoc::getVisualScene(string url) {
   cout << "DEBUG: ColladaDoc::getVisualScene(" << url << ")\n";
   shared_ptr<ColladaObject> colladaObject(getColladaObjectByUrl(url));
   shared_ptr<VisualScene> visualScene(static_pointer_cast<VisualScene, ColladaObject>(colladaObject));
   #warning ['TODO']: Safer dynamic cast?
   return visualScene;
}

shared_ptr<ColladaObject> ColladaDoc::getColladaObjectByUrl(string url) {
   cout << "DEBUG: ColladaDoc::getColladaObjectByUrl(" << url << ")" << endl;
   if(url.length() == 0) {
      cout << "DEBUG: Tried to load blank url..." << endl;
      return shared_ptr<ColladaObject>();
   }

   if(!ColladaUrl::isInternal(url)) {
      cout << "Its External...\n";
      if(!manager_) {
         // TODO: Alternativly, spawn its own manager...
         return shared_ptr<ColladaObject>();
      }
      return manager_->getColladaObjectByUrl(url);
   }

   return getColladaObjectById(ColladaUrl::getId(url));
}

shared_ptr<Collada> ColladaDoc::getCollada() {
   shared_ptr<Collada> collada(new Collada());
   collada->setScene(getScene());
   return collada;
}
