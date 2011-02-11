#ifndef COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_
#define COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_

#include "../GameData/SmartPointers.hpp"
#include <GL/glew.h>

#include <GL/gl.h>

class GLSLShader {
   public:
      GLSLShader(const int& program_id): program_id_(program_id) {}
      const int& getProgramId() { return program_id_; }
      virtual inline void begin() { glUseProgram(getProgramId()); }

   private:
      int program_id_;
};
typedef shared_ptr<GLSLShader> GLSLShaderPtr;

#endif /* COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_ */
