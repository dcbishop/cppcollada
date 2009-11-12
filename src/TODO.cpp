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

using namespace std;
using namespace xercesc;

int main(int argc, char* args[]) {
   string filename = "/home/hegemon/tmp/cube.dae";

   ColladaManager cm;
   shared_ptr<Collada> collada(cm.getCollada(filename));

   ViewWindow vw(800, 600);
   vw.setCollada(collada);
   vw.setTitle(filename);
   vw.mainLoop();
   
   shared_ptr<int> test(new int(10));
}
