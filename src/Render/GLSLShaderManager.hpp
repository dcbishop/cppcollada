#ifndef COLLADACPP_COLLADARENDERERGL_GLSLSHADERMANAGER_HPP_
#define COLLADACPP_COLLADARENDERERGL_GLSLSHADERMANAGER_HPP_

#include <string>
using namespace std;

#include "../Render/GLSLShader.hpp"

class GLSLShaderManager {
   public:
      GLSLShaderPtr getLambert();
      GLSLShaderPtr getBlinnPhong();
      GLSLShaderPtr getPhong();
      GLSLShaderPtr getFlat();
      GLSLShaderPtr loadShaders(const string& vertex, const string& fragment);
      void displayInfoLog(const int& id);

   private:
      string getInfoLog_(const int& id);
      string getShaderInfoLog_(const int& shader_id);
      string getProgramInfoLog_(const int& program_id);

      static GLSLShaderPtr blinn_phong_;
      string loadFile_(const string& filename);
};

#endif /* COLLADACPP_COLLADARENDERERGL_GLSLSHADERMANAGER_HPP_ */
