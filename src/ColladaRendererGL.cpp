#include "ColladaRendererGL.hpp"

#include "Collada.hpp"
#include "Scene.hpp"
#include "VisualScene.hpp"
#include "ColladaNode.hpp"
#include "Position.hpp"
#include "RotationGL.hpp"
#include "Renderable.hpp"

#include "console.h"

#include <GL/gl.h>

#include <iostream>

void ColladaRendererGL::render(ColladaObject* colladaObject) {
   DEBUG_H("ColladaRendererGL::render(ColladaObject* colladaObject)");
   colladaObject->render();
}

void ColladaRendererGL::render(Collada* collada) {
   DEBUG_H("ColladaRendererGL::render(Collada* collada)");
   collada->getScene()->render();
}

void ColladaRendererGL::render(Scene* scene) {
   DEBUG_H("ColladaRendererGL::render(Scene* scene)");
   scene->getVisualScene()->render();
}

void ColladaRendererGL::render(VisualScene* vs) {
   DEBUG_H("ColladaRendererGL::render(VisualScene* vs)");
   ColladaNodeIterator ni = vs->getFirstColladaNode();
   while(ni != vs->getEndColladaNode()) {
      (*ni)->render();
      ni++;
   }
}

void ColladaRendererGL::render(ColladaNode* node) {
   DEBUG_H("ColladaRendererGL::render(ColladaNode* node)");
   float x = node->getX();
   float y = node->getY();
   float z = node->getZ();

   glColor3f(0.0f, 1.0f, 1.0f);
   glBegin(GL_LINES);
      glColor3f(0.0, 0.0, 0.0);
      glColor3f(x, y, z);
   glEnd();

   glPushMatrix();
   
   node->Position::render();
   node->RotationGL::render();
   node->Scale::render();

   // Draw debug axis...
   glBegin(GL_LINES);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);

      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);

      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 1.0);
   glEnd();
   glPopMatrix();
}

void ColladaRendererGL::render(Position* position) {
   DEBUG_H("ColladaRendererGL::render(Position* position)");
   glTranslatef(position->getX(), position->getY(), position->getZ());
}

void ColladaRendererGL::render(RotationGL* rotation) {
   DEBUG_H("ColladaRendererGL::render(RotationGL* rotation)");
   float angle, x, y, z;
   for(int i = 0; i < 3; i++) {
      rotation->getRotationGL(i, x, y, z, angle);
      glRotatef(angle, x, y, z);
   }
}

void ColladaRendererGL::render(Scale* scale) {
   DEBUG_H("ColladaRendererGL::render(Scale* scale)");
   glScalef(scale->getScaleX(), scale->getScaleY(), scale->getScaleZ());
}


void ColladaRendererGL::render(Renderable* renderable) {
   DEBUG_H("ColladaRendererGL::render(Renderable* renderable)");
   //renderable->render();
}
