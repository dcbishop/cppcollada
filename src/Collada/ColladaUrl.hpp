#ifndef COLLADACPP_COLLADAURL_HPP_
#define COLLADACPP_COLLADAURL_HPP_

#include <string>
using namespace std;

/**
 * Functions for dealing with Collada URLs
 */
namespace ColladaUrl {
   const string getId(const string& url);
   const string getFragment(const string& url);
   const string getStrippedUrl(const string& url);
   const bool isInternal(const string& url);
   const string getFilename(const string& url);
};

#endif /* COLLADACPP_COLLADAURL_HPP_ */
