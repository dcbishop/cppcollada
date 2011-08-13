#ifndef COLLADACPP_GLOBALS_HPP_
#define COLLADACPP_GLOBALS_HPP_

#include <string>
using namespace std;

class Renderer;

class Globals {
   public:
      const string& getBuildDate() const {
         return build_date_;
      }
      const string& getGitVersion() const {
         return git_version_;
      }
      const string& getGitSHA1() const {
         return git_sha1_;
      }

      Renderer* getRenderer() const {
         return renderer_;
      }
      void setRenderer(Renderer* const renderer) {
         renderer_ = renderer;
      }

   private:
      static const string build_date_;
      static const string git_version_;
      static const string git_sha1_;
      static Renderer* renderer_;
};

extern Globals g;

#endif /* COLLADACPP_GLOBALS_HPP_ */
