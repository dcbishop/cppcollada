#ifndef COLLADACPP_RENDERERGL_GLSLSHADERMANAGER_HPP_
#define COLLADACPP_RENDERERGL_GLSLSHADERMANAGER_HPP_

#include <string>
using namespace std;

#include "../Render/GLSLShader.hpp"

class GLSLShaderManager {
   public:
      GLSLShaderPtr getLambert();
      GLSLShaderPtr getBlinnPhong();
      GLSLShaderPtr getPhong();
      GLSLShaderPtr getFlat();
      GLSLShaderPtr getNormalDebug();
      GLSLShaderPtr loadShaders(const string& vertex, const string& fragment);
      void displayInfoLog(const int& id);
      static GLuint getVertexAttribId();
      static GLuint getNormalAttribId();
      static GLuint getTextureAttribId();
      static GLuint getColorAttribId();

   private:
      string getInfoLog_(const int& id);
      string getShaderInfoLog_(const int& shader_id);
      string getProgramInfoLog_(const int& program_id);
      string loadFile_(const string& filename);

      static GLSLShaderPtr phong_;
      static GLSLShaderPtr blinn_phong_;
      static GLSLShaderPtr flat_;
      static GLSLShaderPtr normal_debug_;
};

inline GLuint GLSLShaderManager::getVertexAttribId() {
   return 0;
}

inline GLuint GLSLShaderManager::getNormalAttribId() {
   return 1;
}

inline GLuint GLSLShaderManager::getTextureAttribId() {
   return 2;
}

inline GLuint GLSLShaderManager::getColorAttribId() {
   return 3;
}

#endif /* COLLADACPP_RENDERERGL_GLSLSHADERMANAGER_HPP_ */
