#include "GLMatrixStack.hpp"

GLMatrixStack::GLMatrixStack() {
   matricies_.push(glm::mat4());
}
