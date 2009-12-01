#include "ColladaRendererGL.hpp"

#include "Collada.hpp"
#include "Scene.hpp"
#include "VisualScene.hpp"
#include "ColladaNode.hpp"
#include "Position.hpp"
#include "RotationGL.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Triangles.hpp"
#include "ViewWindow.hpp"
#include "Geometry.hpp"

#include "console.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

void ColladaRendererGL::render(ColladaObject* colladaObject) {
   DEBUG_H("ColladaRendererGL::render(ColladaObject* colladaObject)");
   WARNING("Tried to render raw ColladaObject '%s'", colladaObject->getId().c_str());
   //colladaObject->render();
   
}

void ColladaRendererGL::fixAxis_(const Collada* collada) {
   static const int Z_UP = 0;
   static const int X_UP = 1;
   static const int Y_UP = 2;

   #warning ['TODO']: Store and query axis!
   int upAxis = Z_UP;

   if(upAxis == Z_UP) {
      //This seems to work for Z-Axis up
      glRotatef(90.f, -1.0f, 0.0f, 0.0f);
      glScalef(-1.0f, -1.0f, 1.0f);
   } else if(upAxis == Y_UP) {
      
   } else {
      
   }

}

void ColladaRendererGL::debugRotationHack(Collada* collada) {
   shared_ptr<Rotation> rotation;
   rotation = collada->debugRotationHack;
   if(rotation) {
      rotation->render();
   }
}

void ColladaRendererGL::render(Collada* collada) {
   DEBUG_H("ColladaRendererGL::render(Collada* collada)");


   glPushMatrix();
   debugRotationHack(collada); // For testing something...
   fixAxis_(collada);
   collada->getScene()->render();
   glPopMatrix();
}

void ColladaRendererGL::render(Scene* scene) {
   DEBUG_H("ColladaRendererGL::render(Scene* scene)");
   if(scene->getVisualScene()) {
      scene->getVisualScene()->render();
   }
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

   glPushMatrix();
   
   node->Position::render();

   // TODO: Render child nodes...

   node->RotationGL::render();
   node->Scale::render();

   // TODO: Render geometry
   InstanceIterator ii = node->getFirstInstance();
   while(ii != node->getEndInstance()) {
      (*ii)->render();
      ii++;
   }

   renderAxis_(); // DEBUG

   glPopMatrix();
}

void ColladaRendererGL::renderAxis_() {
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

   //shared_ptr<Position> target = target_.lock(); // Is this expensive?
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

void ColladaRendererGL::render(Geometry* geometry) {
   DEBUG_H("void ColladaRendererGL::render(Geometry* '%s')", geometry->getId().c_str());
   GeoPrimIterator iter = geometry->getFirstPrimitive();
   while(iter != geometry->getEndPrimitive()) {
      (*iter)->render();
      iter++;
   }
}

void ColladaRendererGL::render(Triangles* triangles) {
   DEBUG_H("ColladaRendererGL::render(Triangles* triangles)");
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_TRIANGLES);
      triangles->GeometricPrimitive::render();
   glEnd();
}

void ColladaRendererGL::render(const GeometricPrimitive* geometry) {
   DEBUG_H("ColladaRendererGL::render(GeometricPrimitive* geometry)");

   static int what;
   if(!what) {
      WARNING("Inefficient primitive rendering!, TODO: convert to vertex buffer object first!");
      what = 1;
   }
   
   PrimIterator iter = geometry->getFirstPrimitive();
   int inputCount = geometry->getInputCount();
   while(iter != geometry->getEndPrimitive()) {
      int primNum = geometry->getVertexNum(*iter);
      DEBUG_H("%d %d x=%f. y=%f, z=%f", *iter, primNum, geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //float x = geometry->getX(primNum);
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      iter+=inputCount;
   }
}
