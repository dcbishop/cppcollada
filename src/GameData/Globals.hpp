#ifndef COLLADACPP_GLOBALS_HPP_
#define COLLADACPP_GLOBALS_HPP_

#include <string>
using namespace std;

class Globals {
   public:
      const string& getBuildDate() const {
         return build_date;
      }
      const string& getGitVersion() const {
         return git_version;
      }
      const string& getGitSHA1() const {
         return git_sha1;
      }

   private:
      static const string build_date;
      static const string git_version;
      static const string git_sha1;      
};

#endif /* COLLADACPP_GLOBALS_HPP_ */
