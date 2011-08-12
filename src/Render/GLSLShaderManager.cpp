#include "GLSLShaderManager.hpp"

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/gl.h>

#include <fstream>
#include <sstream>
using namespace std;

#include "../Debug/console.h"

GLSLShaderPtr GLSLShaderManager::phong_;
GLSLShaderPtr GLSLShaderManager::blinn_phong_;
GLSLShaderPtr GLSLShaderManager::flat_;
GLSLShaderPtr GLSLShaderManager::normal_debug_;

GLSLShaderPtr GLSLShaderManager::getLambert() {
   // TODO
   return getBlinnPhong();
}

GLSLShaderPtr GLSLShaderManager::getPhong() {
   if(phong_.get() == NULL) {
      DEBUG_M("Loading phong shader..."); //TODO: Use relative paths (seems to break gDEBugger
      phong_ = GLSLShaderPtr(loadShaders("Data/Shaders/Phong.vert", "Data/Shaders/Phong.frag"));
   }
   /*TODO Debug code...
   if(phong_.get() == NULL) {
      DEBUG_M("Loading phong shader..."); //TODO: Use relative paths (seems to break gDEBugger
      phong_ = GLSLShaderPtr(loadShaders("Data/Shaders/NormalDebug.vert", "Data/Shaders/NormalDebug.frag"));
   }*/
   /*if(phong_.get() == NULL) {
      DEBUG_M("Loading phong shader..."); //TODO: Use relative paths (seems to break gDEBugger
      phong_ = GLSLShaderPtr(loadShaders("Data/Shaders/Brick.vert", "Data/Shaders/Brick.frag"));
   }*/
   return phong_;
}

GLSLShaderPtr GLSLShaderManager::getFlat() {
   if(flat_.get() == NULL) {
      DEBUG_M("Loading blinn phong shader..."); //TODO: Use relative paths (seems to break gDEBugger
      flat_ = GLSLShaderPtr(loadShaders("Data/Shaders/Flat.vert", "Data/Shaders/Flat.frag"));
   }
   return flat_;
}

GLSLShaderPtr GLSLShaderManager::getBlinnPhong() {
   if(blinn_phong_.get() == NULL) {
      DEBUG_M("Loading flat shader...");
      blinn_phong_ = GLSLShaderPtr(loadShaders("Data/Shaders/Projection.vert", "Data/Shaders/BlinnPhong.frag"));
   }
   return blinn_phong_;
}

GLSLShaderPtr GLSLShaderManager::getNormalDebug() {
   if(flat_.get() == NULL) {
      DEBUG_M("Loading normal debug shader..."); //TODO: Use relative paths (seems to break gDEBugger
      flat_ = GLSLShaderPtr(loadShaders("Data/Shaders/NormalDebug.vert", "Data/Shaders/NormalDebug.frag"));
   }
   return flat_;
}

string GLSLShaderManager::loadFile_(const string& filename) {
   ifstream file(filename);
   if(!file) {
      ERROR("Failed to load shader file '%s'.", filename.c_str());
      return "";
   }
   stringstream data;
   data << file.rdbuf();
   file.close();
   return data.str();
}

GLSLShaderPtr GLSLShaderManager::loadShaders(const string& vertex_file, const string& fragment_file) {
   string vertex_raw = loadFile_(vertex_file);
   string fragment_raw = loadFile_(fragment_file);
   if(vertex_raw.empty()) {
      ERROR("Failed to load vertex shader '%s', vertex_file");
      return GLSLShaderPtr();
   }
   if(fragment_raw.empty()) {
      ERROR("Failed to load fragment shader '%s', fragment_file");
      return GLSLShaderPtr();
   }

   GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
   GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

   const char* vertex_c = vertex_raw.c_str();
   const char* fragment_c = fragment_raw.c_str();

   const GLchar** vertex_gc = &vertex_c;
   const GLchar** fragment_gc = &fragment_c;
   
   glShaderSource(vertex_id, 1, vertex_gc, NULL);
   glShaderSource(fragment_id, 1, fragment_gc, NULL);
   
   glCompileShader(vertex_id);
   glCompileShader(fragment_id);
   
   displayInfoLog(vertex_id);
   displayInfoLog(fragment_id);
   
   int program_id = glCreateProgram();
   glAttachShader(program_id, vertex_id);
   glAttachShader(program_id, fragment_id);
   glLinkProgram(program_id);
   displayInfoLog(program_id);
   
   GLSLShaderPtr shader(new GLSLShader(program_id));
   return shader;
}

void GLSLShaderManager::displayInfoLog(const int& id) {
   string info_log = getInfoLog_(id);
   if(!info_log.empty()) {
      WARNING("%s", info_log.c_str());
   }
}

string GLSLShaderManager::getInfoLog_(const int& id) {
   if(glIsShader(id)) {
      return getShaderInfoLog_(id);
   } else {
      return getProgramInfoLog_(id);
   }
}

string GLSLShaderManager::getShaderInfoLog_(const int& shader_id) {
   int buff_size = 0;
   int bytes = 0;
   glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &buff_size);
   char info_log[buff_size];
   glGetShaderInfoLog(shader_id, buff_size, &bytes, info_log);
   return info_log;
}

string GLSLShaderManager::getProgramInfoLog_(const int& program_id) {
   int buff_size = 0;
   int bytes = 0;
   glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &buff_size);
   char info_log[buff_size];
   glGetProgramInfoLog(program_id, buff_size, &bytes, info_log);
   return info_log;
}
