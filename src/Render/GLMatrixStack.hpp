/*
 * GLMatricStack.hpp - Implements a simple replacement for the deprecated
 * OpenGL matrix functions using GLM.
 *
 * Written in 2011 by David C. Bishop <david@davidbishop.org>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef GLMMATRIXSTACK_HPP_
#define GLMMATRIXSTACK_HPP_

#include <stack>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GLMatrixStack {
   public:
      GLMatrixStack();
      void pushMatrix();
      void popMatrix();
      void rotate(const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& angle);
      void translate(const GLfloat& x, const GLfloat& y, const GLfloat& z);
      void scale(const GLfloat& x, const GLfloat& y, const GLfloat& z);
      void loadIdentity();
      void setPerspective(const GLfloat& fovy, const GLfloat& aspect, const GLfloat& near, const GLfloat& far);
      GLfloat* getOpenGLMatrix();
      glm::mat4& getMatrix();
      glm::mat3 getNormalMatrix();

   private:
      stack<glm::mat4> matricies_;
};

inline GLMatrixStack::GLMatrixStack() {
   matricies_.push(glm::mat4());
}

inline void GLMatrixStack::pushMatrix() {
   matricies_.push(matricies_.top());
}

inline void GLMatrixStack::popMatrix() {
   if(matricies_.size() <= 1) {
      return;
   }
   matricies_.pop();
}

inline void GLMatrixStack::rotate(const GLfloat& angle, const GLfloat& x, const GLfloat& y, const GLfloat& z) {
   if(angle == 0) {
      return;
   }
   
   matricies_.top() = glm::rotate(matricies_.top(), angle, glm::vec3(x, y, z));
}

inline void GLMatrixStack::translate(const GLfloat& x, const GLfloat& y, const GLfloat& z) {
   matricies_.top() = glm::translate(matricies_.top(), glm::vec3(x, y, z));
}

inline void GLMatrixStack::scale(const GLfloat& x, const GLfloat& y, const GLfloat& z) {
   matricies_.top() = glm::scale(matricies_.top(), glm::vec3(x, y, z));
}

inline void GLMatrixStack::loadIdentity() {
   matricies_.pop();
   matricies_.push(glm::mat4());   
}

inline void GLMatrixStack::setPerspective(const GLfloat& fovy, const GLfloat& aspect, const GLfloat& near, const GLfloat& far) {
   matricies_.pop();
   matricies_.push(glm::perspective(fovy, aspect, near, far));
}

inline GLfloat* GLMatrixStack::getOpenGLMatrix() {
   return &matricies_.top()[0][0];
}

inline glm::mat4& GLMatrixStack::getMatrix() {
   return matricies_.top();
}

inline glm::mat3 GLMatrixStack::getNormalMatrix() {
   return glm::transpose(glm::inverse(glm::mat3x3(matricies_.top())));
}

#endif /* GLMMATRIXSTACK_HPP_ */
