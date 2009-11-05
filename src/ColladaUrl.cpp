#include "ColladaUrl.hpp"

#include <string>

/**
 * Returns true if the url is within the current Collada doc (ie starts with #).
 * @param url The URL to test.
 * @return true if url is local.
 */
bool ColladaUrl::isInternal(string url) {
   if(url.rfind("#") == 0) {
      return true;
   }
   return false;
}

/**
 * Returns the id part of the URL 
 * @param url The URL.
 * @return the id (the bit after the #).
 */
string ColladaUrl::getId(string url) {
   int hashPos = url.rfind("#");
   if(hashPos < 0) {
      return "";
   }
   return url.substr(hashPos+1);
}

/**
 * Returns the URL without the id part.
 * @param url The url to return.
 * @return The url without the id.
 */
string ColladaUrl::getStrippedUrl(string url) {
   int hashPos = url.rfind("#");
   if(hashPos < 0) {
      return url;
   }

   return url.substr(0, hashPos);
}

/**
 * Gets the filaname from the url.
 */
string ColladaUrl::getFilename(string url) {
   string filePrefix = "file://";

   int filePos = url.find(filePrefix);
   if(filePos != 0) {
      return getStrippedUrl(url);
   }
   return getStrippedUrl(url.substr(filePrefix.length()-1));
}
