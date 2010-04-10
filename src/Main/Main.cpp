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

#include "../GameData/Camera.hpp"

//#include "../Unused/NetworkedSensor.hpp"

#include "../Debug/console.h"
#include "../GameData/RotationGL.hpp"

using namespace std;
using namespace xercesc;

int main(int argc, char* argv[]) {
   LOG("Starting main...");
   //DEBUG_A("Starting...");
   //string filename = "/home/hegemon/tmp/monkeyhead.dae";
   //string filename = "/home/hegemon/tmp/cubeuvmap.dae";
   string filename = "/home/hegemon/tmp/externtest.dae";
   //string filename = "/home/hegemon/tmp/planetest.dae";
   //string filename = "/home/hegemon/tmp/materialtest.dae";

   DEBUG_A("Spawning ColladaManager...");
   ColladaManagerPtr cm(new ColladaManager());
   DEBUG_A("Loading '%s'...", filename.c_str());
   ColladaPtr collada(cm->getCollada(filename));
   DEBUG_A("Scrubbing Collada docs...");
   cm->scrub();

   shared_ptr<Position> position = shared_ptr<Position>(new Position);
   position->setX(0.0f);
   position->setY(0.0f);
   position->setZ(0.0f);

   shared_ptr<Camera> camera = shared_ptr<Camera>(new Camera);
   camera->setTarget(position);
   camera->setZoom(10.0f);

   //ViewWindowSDL vw(800, 600);
   ViewWindowQT vw(800, 600);
   vw.setColladaManager(cm);
   vw.setCollada(collada);
   vw.setTitle(filename);
   vw.setCamera(camera);
   vw.mainLoop();
   
   
   //DEBUG_A("Entering main loop...");
   
   /*shared_ptr<RotationGL> rotation(new RotationGL);
   collada->debugRotationHack = rotation;
   
   NetworkedSensor ns;
   ns.setOrientationTarget(rotation);
   ns.start();*/

   LOG("Goodbye...");
}
