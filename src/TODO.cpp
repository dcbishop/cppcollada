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

using namespace std;
using namespace xercesc;

int main(int argc, char* args[]) {
   string filename = "/home/hegemon/tmp/cube.dae";

   /*ColladaDocManager cdm;
   ColladaDoc* test = cdm.getColladaDoc(filename);*/
   
   ColladaManager cm;
   Collada *collada = cm.getCollada(filename);
}
