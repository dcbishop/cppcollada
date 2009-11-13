#ifndef COLLADACPP_COLLADAURL_HPP_
#define COLLADACPP_COLLADAURL_HPP_

#include <string>
using namespace std;

/**
 * Functions for dealing with Collada URLs
 */
namespace ColladaUrl {
   string getId(string url);
   string getStrippedUrl(string url);
   bool isInternal(string url);
   string getFilename(string url);
};

#endif /* COLLADACPP_COLLADAURL_HPP_ */
