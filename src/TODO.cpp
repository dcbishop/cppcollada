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
#include "ViewWindow.hpp"

#include "SmartPointers.hpp"

#include "console.h"

using namespace std;
using namespace xercesc;

int main(int argc, char* args[]) {
   //DEBUG_A("Starting...");
   string filename = "/home/hegemon/tmp/monkeyhead.dae";

   DEBUG_A("Spawning ColladaManager...");
   ColladaManager cm;
   DEBUG_A("Loading '%s'...", filename.c_str());
   shared_ptr<Collada> collada(cm.getCollada(filename));
   DEBUG_A("Scrubbing Collada docs...");
   cm.scrub();

   //DEBUG_A("Spawning window...");
   ViewWindow vw(800, 600);
   //DEBUG_A("Setting up window...");
   vw.setCollada(collada);
   vw.setTitle(filename);
   //DEBUG_A("Entering main loop...");
   vw.mainLoop();
}
