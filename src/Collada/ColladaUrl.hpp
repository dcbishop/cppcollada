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

   /**
    * A class for working with URLs
    */
   class ColladaUrl {
      public:
         ColladaUrl(string url) {
            setUrl(url);
         }

         void setUrl(string url) {
            // TODO: If this is used for anything that could be transfered
            // out, stop stuff like "data/../../../../../etc/passwd",
            // "/etc/passwd", "C:\secretfile.txt".
            int colonPos = url.rfind(":");
            if(colonPos < 0) {
               // Not a URL, assume a raw filename...
               url = "file://" + url;
            } else if(colonPos == 1) {
               // TODO: Stupid windows path
            }
            url_ = url;
         }

         string getUrl() {
            return url_;
         }

         string getFilename() {
            #warning ['TODO']: Download the file from a webserver or whatever if necessary...
            // TODO: Strip file:// from the URL

            // TODO: Try various locations of the file on disk...
            // file as given, data, data/models, data/images, cache,
            // override, patch directories, home, etc...
         }

      private:
         bool getIsFile_(string url) {
            int colonPos = url.rfind(":");
            if(colonPos < 0) {
               // Not a URL, assume a raw filename...
               url = "file://" + url;
            } else if(colonPos == 1) {
               // TODO: Stupid windows path
            }
         }
         string url_;
   };

};

#endif /* COLLADACPP_COLLADAURL_HPP_ */
