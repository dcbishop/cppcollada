#ifndef COLLADACPP_COLLADARENDERERGL_MATRIXSTACK_HPP_
#define COLLADACPP_COLLADARENDERERGL_MATRIXSTACK_HPP_

#include <GL/gl.h>

class GLMatrixStack {
   public:
      void pushMatrix();
      void popMatrix();
      void rotate(const float& x, const float& y, const float& z, const float& angle);
      void translate(const float& x, const float& y, const float& z);
      void scale(const float& x, const float& y, const float& z);
};

inline void GLMatrixStack::pushMatrix() {
   glPushMatrix();
}

inline void GLMatrixStack::popMatrix() {
   glPopMatrix();
}

inline void GLMatrixStack::rotate(const float& x, const float& y, const float& z, const float& angle) {
   glRotatef(x, y, z, angle);
}

inline void GLMatrixStack::translate(const float& x, const float& y, const float& z) {
   glTranslatef(x, y, z);
}

inline void GLMatrixStack::scale(const float& x, const float& y, const float& z) {
   glScalef(x, y, z);
}

#endif /* COLLADACPP_COLLADARENDERERGL_MATRIXSTACK_HPP_ */
