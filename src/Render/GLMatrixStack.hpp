#ifndef COLLADACPP_COLLADARENDERERGL_MATRIXSTACK_HPP_
#define COLLADACPP_COLLADARENDERERGL_MATRIXSTACK_HPP_

#include <cmath>
#include <stack>
using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Debug/console.h"

/*inline void printMatrix(glm::mat4& matrix) {
   DEBUG_M("------------------");
   DEBUG_M("[ %f, %f, %f, %f ]", matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0]);
   DEBUG_M("[ %f, %f, %f, %f ]", matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1]);
   DEBUG_M("[ %f, %f, %f, %f ]", matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2]);
   DEBUG_M("[ %f, %f, %f, %f ]", matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
}

inline void printMatrices(GLfloat* glmatrix, glm::mat4& matrix) {
   DEBUG_M("------------------");
   DEBUG_M("[ %f, %f, %f, %f ] [ %f, %f, %f, %f ]", glmatrix[0], glmatrix[4], glmatrix[8], glmatrix[12], matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0]);
   DEBUG_M("[ %f, %f, %f, %f ] [ %f, %f, %f, %f ]", glmatrix[1], glmatrix[5], glmatrix[9], glmatrix[13], matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1]);
   DEBUG_M("[ %f, %f, %f, %f ] [ %f, %f, %f, %f ]", glmatrix[2], glmatrix[6], glmatrix[10], glmatrix[14], matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2]);
   DEBUG_M("[ %f, %f, %f, %f ] [ %f, %f, %f, %f ]", glmatrix[3], glmatrix[7], glmatrix[11], glmatrix[15], matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
}*/

class GLMatrixStack {
   public:
      GLMatrixStack();
      void pushMatrix();
      void popMatrix();
      void rotate(const float& x, const float& y, const float& z, const float& angle);
      void translate(const float& x, const float& y, const float& z);
      void scale(const float& x, const float& y, const float& z);
      void loadIdentity();
      void setPerspective(const float& fovy, const float& aspect, const float& near, const float& far);
      float* getOpenGLMatrix();
      glm::mat4& getMatrix();
      glm::mat3 getNormalMatrix(const bool normalized);

   private:
      stack<glm::mat4> matricies_;
};

inline void GLMatrixStack::pushMatrix() {
   matricies_.push(matricies_.top());
   glLoadMatrixf(getOpenGLMatrix());
}

inline void GLMatrixStack::popMatrix() {
   if(matricies_.size() <= 1) {
      ERROR("Tried to pop last stack element");
      return;
   }
   matricies_.pop();
   glLoadMatrixf(getOpenGLMatrix());
}

inline void GLMatrixStack::rotate(const float& angle, const float& x, const float& y, const float& z) {
   if(angle == 0) {
      return;
   }
   
   matricies_.top() = glm::rotate(matricies_.top(), angle, glm::vec3(x, y, z));
   glLoadMatrixf(getOpenGLMatrix());
}

inline void GLMatrixStack::translate(const float& x, const float& y, const float& z) {
   matricies_.top() = glm::translate(matricies_.top(), glm::vec3(x, y, z));
   glLoadMatrixf(getOpenGLMatrix());
}

inline void GLMatrixStack::scale(const float& x, const float& y, const float& z) {
   matricies_.top() = glm::scale(matricies_.top(), glm::vec3(x, y, z));
   glLoadMatrixf(getOpenGLMatrix());
}

inline void GLMatrixStack::loadIdentity() {
   matricies_.pop();
   matricies_.push(glm::mat4());   
}

inline void GLMatrixStack::setPerspective(const float& fovy, const float& aspect, const float& near, const float& far) {
   matricies_.pop();
   matricies_.push(glm::perspective(fovy, aspect, near, far));
}

inline float* GLMatrixStack::getOpenGLMatrix() {
   return &matricies_.top()[0][0];
}

inline glm::mat4& GLMatrixStack::getMatrix() {
   return matricies_.top();
}

inline glm::mat3 GLMatrixStack::getNormalMatrix(const bool normalized = true) {
   // We should be able to just use the upper 3x3 portion of the matrix unless there is nonuniform scaling...
   //return glm::mat3x3(matricies_.top());
   return glm::transpose(glm::inverse(glm::mat3x3(matricies_.top())));
}

#endif /* COLLADACPP_COLLADARENDERERGL_MATRIXSTACK_HPP_ */
