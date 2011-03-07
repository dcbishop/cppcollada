class OpenGLBuffer {
   OpenGLBuffer(const float[] floats, const int typesize = 3, const int target = GL_ARRAY_BUFFER) {
      glGenBuffers(1, &id_);
      target_ = GL_ARRAY_BUFFER;
      data_ = floats;
   }

   ~OpenGLBuffer() {
      glDeleteBuffers(1, &id_);
   }

   OpenGLBuffer(const void* data) {
      glGenBuffers(1, &id_);
      glBindBuffer(GL_ARRAY_BUFFER, id_);
   }
   
   int getSize() {
      return sizeof(data_);
   }
   
   float* data_;
   GLuint id_;
   GLenum target_;
};

class VertexArrayObject {
   
   public:
      VertexArrayObject() {
         glGenVertexArrays(1, &id);
      }

      addBuffer(const OpenGLBuffer& buff, const int& attrib_id = -1 ) {
         glBindVertexArray(id);
         glBufferData(GL_ARRAY_BUFFER, buff.getSize(), &buff, GL_STATIC_DRAW);
      }


   private:
   
   map<GLuint id, float> inputs;
   GLUint id;
   
};
