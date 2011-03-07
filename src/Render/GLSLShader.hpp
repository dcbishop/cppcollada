#ifndef COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_
#define COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_

#include "../GameData/SmartPointers.hpp"
#include <GL/glew.h>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../Collada/ColladaLitShader.hpp"

#include "../Debug/console.h"

struct light {
   glm::vec4 position;
};

struct matrial {
   glm::vec4 diffuseColor;
   glm::vec4 ambientColor;
};

class GLSLShader {
   public:
      GLSLShader(const int& program_id): program_id_(program_id) {
         mvp_loc_ = glGetUniformLocation(program_id_, "MVPMatrix");
         mv_loc_ = glGetUniformLocation(program_id_, "MVMatrix");
         nmatrix_loc_ = glGetUniformLocation(program_id_, "NormalMatrix");
         material_d_loc_ = glGetUniformLocation(program_id_, "material.diffuseColor");
         material_a_loc_ = glGetUniformLocation(program_id_, "material.ambientColor");
         light_loc_ = glGetUniformLocation(program_id_, "Lights[0].position");
         DEBUG_M("Found locations %d, %d", mvp_loc_, mv_loc_);
      }

      const int& getProgramId() { return program_id_; }

      virtual inline void begin() { glUseProgram(getProgramId()); }

      void bindModelviewMatrix(const glm::mat4& MVMatrix) {
         bindMatrix(MVMatrix, mv_loc_);
      }

      void bindModelviewProjectionMatrix(const glm::mat4& MVPMatrix) {
         bindMatrix(MVPMatrix, mvp_loc_);
      }

      void bindNormalMatrix(const glm::mat3& NormalMatrix) {
         bindMatrix(NormalMatrix, nmatrix_loc_);
      }

      void bindMatrix(const glm::mat4& matrix, const int& loc) {
         if(loc == -1) {
            return;
         }
         glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
      }

      void bindMatrix(const glm::mat3& matrix, const int& loc) {
         if(loc == -1) {
            return;
         }
         glUniformMatrix3fv(loc, 1, GL_FALSE, &matrix[0][0]);
      }

      void bindLights(const light* lights) {
         glUniform4fv(light_loc_, 1, &lights[0].position[0]);
      }

      void bindMaterial(const ColladaLitShader* colladaMaterial) {
         glUniform4fv(material_d_loc_, 1, colladaMaterial->getDiffuse().getArray());
      }

      void bindAttributes() {
         glBindAttribLocation(program_id_, 0, "MCVertex");
         glBindAttribLocation(program_id_, 1, "MCNormal");
         glBindAttribLocation(program_id_, 3, "VertexColor");
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
      int nmatrix_loc_;
      int light_loc_;
      int material_a_loc_;
      int material_d_loc_;
};
typedef shared_ptr<GLSLShader> GLSLShaderPtr;

#endif /* COLLADACPP_COLLADARENDERERGL_GLSLSHADER_HPP_ */
