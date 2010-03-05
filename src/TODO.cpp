#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>

#include "Collada.hpp"
#include "ColladaManager.hpp"
#include "ColladaDocManager.hpp"
#include "ColladaDoc.hpp"
#include "ViewWindowSDL.hpp"
#include "ViewWindowQT.hpp"

#include "SmartPointers.hpp"

#include "Camera.hpp"

//#include "NetworkedSensor.hpp"

#include "console.h"
#include "RotationGL.hpp"

using namespace std;
using namespace xercesc;

int main(int argc, char* args[]) {
   //DEBUG_A("Starting...");
   //string filename = "/home/hegemon/tmp/monkeyhead.dae";
   string filename = "/home/hegemon/tmp/cubeuvmap.dae";
   //string filename = "/home/hegemon/tmp/planetest.dae";


   DEBUG_A("Spawning ColladaManager...");
   ColladaManager cm;
   DEBUG_A("Loading '%s'...", filename.c_str());
   shared_ptr<Collada> collada(cm.getCollada(filename));
   DEBUG_A("Scrubbing Collada docs...");
   cm.scrub();

   shared_ptr<Position> position = shared_ptr<Position>(new Position);
   position->setX(0.0f);
   position->setY(0.0f);
   position->setZ(0.0f);

   shared_ptr<Camera> camera = shared_ptr<Camera>(new Camera);
   camera->setTarget(position);
   camera->setZoom(10.0f);

   //ViewWindowQT vwq(800, 600);
   //ViewWindowSDL vw(800, 600);
   ViewWindowQT vw(800, 600);
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
   //int a;
   //cin >> a;
   LOG("Goodbye...");

}
