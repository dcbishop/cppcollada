#include "../Collada/ColladaUrl.hpp"

#include <string>

/**
 * Returns true if the url is within the current Collada doc (ie starts with #).
 * @param url The URL to test.
 * @return true if url is local.
 */
const bool ColladaUrl::isInternal(const string& url) {
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
const string ColladaUrl::getId(const string& url) {
   int hashPos = url.rfind("#");
   if(hashPos < 0) {
      return "";
   }
   return url.substr(hashPos+1);
}

/**
 * Returns the fragment+id part of the URL 
 * @param url The URL.
 * @return the id (the # and text after it).
 */
const string ColladaUrl::getFragment(const string& url) {
   int hashPos = url.rfind("#");
   if(hashPos < 0) {
      return "";
   }
   return url.substr(hashPos);
}

/**
 * Returns the URL without the id part.
 * @param url The url to return.
 * @return The url without the id.
 */
const string ColladaUrl::getStrippedUrl(const string& url) {
   int hashPos = url.rfind("#");
   if(hashPos < 0) {
      return url;
   }

   return url.substr(0, hashPos);
}

/**
 * Gets the filaname from the url.
 */
const string ColladaUrl::getFilename(const string& url) {
   string filePrefix = "file://";

   int filePos = url.find(filePrefix);
   if(filePos != 0) {
      return getStrippedUrl(url);
   }
   return getStrippedUrl(url.substr(filePrefix.length()-1));
}
