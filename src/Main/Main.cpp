#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>

#include "../Collada/Collada.hpp"
#include "../Collada/ColladaManager.hpp"
#include "../Collada/ColladaDocManager.hpp"
#include "../Collada/ColladaDoc.hpp"
#include "../Viewport/ViewWindowSDL.hpp"
#include "../Viewport/ViewWindowQT.hpp"

#include "../GameData/SmartPointers.hpp"

#include "../GameObjects/Camera.hpp"

//#include "../Unused/NetworkedSensor.hpp"

#include "../Debug/console.h"
#include "../GameData/RotationGL.hpp"
#include "../Debug/TestRenderable.hpp"
#include "../Collada/Scene.hpp"

#include "../GameObjects/Area.hpp"
#include "../GameObjects/ColladaMesh.hpp"
#include "../GameObjects/Octree.hpp"

using namespace std;
using namespace xercesc;

int main(int argc, char* argv[]) {
   LOG("Starting main...");
	string filename;

	// Assume the last arg is the uri to open if it doesn't start with a '-'.
   if(argv[argc-1][0] != '-' && argc > 1) {
      filename = argv[argc-1];
   } else {
		ERROR("No filename specified.");
		return 1;
	}

   DEBUG_A("Spawning ColladaManager...");
   ColladaManagerPtr cm(new ColladaManager());
   DEBUG_A("Loading '%s'...", filename.c_str());
   ColladaPtr collada(cm->getCollada(filename));
   DEBUG_A("Scrubbing Collada docs...");
   cm->scrub();

   ColladaMeshPtr colladaMesh = ColladaMeshPtr(new ColladaMesh);
   colladaMesh->setCollada(collada);

   /*OctreePtr octreeTest = OctreePtr(new Octree);
   octreeTest->setScaleXYZ(10, 10, 10);
   octreeTest->debug();*/

   CameraPtr camera = CameraPtr(new Camera);
   camera->setTarget(colladaMesh);
   //camera->setTarget(octreeTest);
   camera->setZoom(10.0f);

   AreaPtr area = AreaPtr(new Area());
   area->addObject(camera);
   area->addObject(colladaMesh);
   //area->addObject(octreeTest);

   //ViewWindowSDL vw(800, 600);
   ViewWindowQT vw(800, 600);
   vw.setTitle(filename);
   vw.setCamera(camera);
   vw.mainLoop();

   /*shared_ptr<RotationGL> rotation(new RotationGL);
   collada->debugRotationHack = rotation;

   NetworkedSensor ns;
   ns.setOrientationTarget(rotation);
   ns.start();*/

   LOG("Goodbye...");
}
