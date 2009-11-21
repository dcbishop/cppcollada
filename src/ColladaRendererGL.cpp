#include "ColladaRendererGL.hpp"

#include "Collada.hpp"
#include "Scene.hpp"
#include "VisualScene.hpp"
#include "ColladaNode.hpp"
#include "Position.hpp"
#include "RotationGL.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "ViewWindow.hpp"

#include "console.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

/*void ColladaRendererGL::render(ColladaObject* colladaObject) {
   DEBUG_H("ColladaRendererGL::render(ColladaObject* colladaObject)");
   colladaObject->render();
}*/

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

   glPushMatrix();
   
   node->Position::render();

   // TODO: Render child nodes...

   node->RotationGL::render();
   node->Scale::render();

   // TODO: Render geometry

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

/**
 * Positions the camera for OpenGL.
 */
void ColladaRendererGL::render(Camera* camera) {
	float cx = 0.0f;
	float cy = 0.0f;
	float cz = 0.0f;

	#warning ['TODO']: Is this expensive?
	//shared_ptr<Position> target = target_.lock();
	shared_ptr<Position> target = camera->getTarget();
	if(target) {
		cx = target->getX();
		cy = target->getY();
		cz = target->getZ();
	}

	gluLookAt( camera->getX()+cx, camera->getY()+cy, camera->getZ()+cz, cx, cy, cz, 0.0f, 10.0f, 0.0f );
}

void ColladaRendererGL::render(Grid* grid) {
   int size_x = grid->getSizeX();
   int size_y = grid->getSizeY();
   //int size_z = grid->getSizeZ();

   float spacing = grid->getSpacing();

   // TODO: This is a stupid way of drawing grid
   glColor3f(1.0f, 1.0f, 1.0f);
   glBegin(GL_LINES);
   for(int y = 0; y < size_y; y++) {
      float y1 = y * spacing;
      float y2 = y1 + spacing;
      for(int x = 0; x < size_x; x++) {
         float x1 = x * spacing;
         float x2 = x1 + spacing;

         glVertex3f(x1, 0.0, y1);
         glVertex3f(x2, 0.0, y1);
         glVertex3f(x1, 0.0, y1);
         glVertex3f(x1, 0.0, y2);

         glVertex3f(x1, 0.0, -y1);
         glVertex3f(x2, 0.0, -y1);
         glVertex3f(x1, 0.0, -y1);
         glVertex3f(x1, 0.0, -y2);

         glVertex3f(-x1, 0.0, y1);
         glVertex3f(-x2, 0.0, y1);
         glVertex3f(-x1, 0.0, y1);
         glVertex3f(-x1, 0.0, y2);

         glVertex3f(-x1, 0.0, -y1);
         glVertex3f(-x2, 0.0, -y1);
         glVertex3f(-x1, 0.0, -y1);
         glVertex3f(-x1, 0.0, -y2);
      }
   }
   glEnd();
}
