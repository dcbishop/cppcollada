#ifndef COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_
#define COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_

#include "../GameData/SmartPointers.hpp"
#include <GL/glew.h>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../Debug/console.h"

class GLSLShader {
   public:
      GLSLShader(const int& program_id): program_id_(program_id) {
         mvp_loc_ = glGetUniformLocation(program_id_, "MVPMatrix");
         mv_loc_ = glGetUniformLocation(program_id_, "MVMatrix");
         DEBUG_M("Found locations %d, %d", mvp_loc_, mv_loc_);
      }
      const int& getProgramId() { return program_id_; }
      virtual inline void begin() { glUseProgram(getProgramId()); }
      void bindModelviewMatrix(const glm::mat4 MVMatrix) {
         bindMatrix(MVMatrix, mv_loc_);
      }
      void bindModelviewProjectionMatrix(const glm::mat4 MVPMatrix) {
         bindMatrix(MVPMatrix, mvp_loc_);
      }
      void bindMatrix(const glm::mat4 matrix, const int& loc) {
         if(loc == -1) {
            return;
         }
         glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
      }
      void bindAttributes() {
         glBindAttribLocation(program_id_, 0, "mcVertex");
         glBindAttribLocation(program_id_, 1, "mcNormal");
      }
      
   private:
      string getProgramInfoLog_() {
         int buff_size = 0;
         int bytes = 0;
         glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &buff_size);
         char info_log[buff_size];
         glGetProgramInfoLog(program_id_, buff_size, &bytes, info_log);
         return info_log;
      }

      int program_id_;
      int mvp_loc_;
      int mv_loc_;
};
typedef shared_ptr<GLSLShader> GLSLShaderPtr;

#endif /* COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_ */
