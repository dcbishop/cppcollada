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
#include "Geometry.hpp"
#include "InstanceGeometry.hpp"
#include "Material.hpp"
#include "Phong.hpp"
#include "Grid.hpp"

#include "console.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

void ColladaRendererGL::init() {
   
}

void ColladaRendererGL::preFrame() {
   setPerspective_();
   glLoadIdentity();
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ColladaRendererGL::postFrame() {
   glFlush();
}

void ColladaRendererGL::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
}

void ColladaRendererGL::setPerspective_() {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, width_ / height_, 0.1f, 10000.0f);
   glMatrixMode(GL_MODELVIEW);
}

void ColladaRendererGL::render(ColladaObject* colladaObject) {
   DEBUG_H("ColladaRendererGL::render(ColladaObject* colladaObject)");
   WARNING("Tried to render raw ColladaObject '%s'", colladaObject->getId().c_str());
   //colladaObject->render();
   
}

void ColladaRendererGL::fixAxis_(const Collada* collada) {
   DEBUG_H("void ColladaRendererGL::fixAxis_(const Collada* collada) {");
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

void ColladaRendererGL::debugRotationHack(const Collada* collada) {
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

   static float pos = 1.0f;
   pos+=0.01;
   glDisable(GL_LIGHTING);
   glPushMatrix();

   float lx = 0.0;
   float ly = 0.0;
   float lz = pos;
   
   glTranslatef(lx, ly, lz);
   renderAxis_();
   glPopMatrix();
   
   
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glPolygonMode( GL_FRONT, GL_FILL );
   glEnable(GL_CULL_FACE);
   glCullFace(GL_FRONT);
   glFrontFace(GL_CW);
   

   float light_pos[] = {lx, ly, lz, 1.0};
   glLightfv(GL_LIGHT0,GL_POSITION,light_pos);

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
   DEBUG_H("void ColladaRendererGL::renderAxis_()");
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
   DEBUG_H("void ColladaRendererGL::render(Camera* camera)");
   float cx = 0.0f;
   float cy = 0.0f;
   float cz = 0.0f;

   shared_ptr<Position> target = camera->getTarget();
   if(target) {
      cx = target->getX();
      cy = target->getY();
      cz = target->getZ();
   }

   gluLookAt( camera->getX()+cx, camera->getY()+cy, camera->getZ()+cz, cx, cy, cz, 0.0f, 10.0f, 0.0f );
}

void ColladaRendererGL::render(Grid* grid) {
   DEBUG_H("void ColladaRendererGL::render(Grid* grid)");

   glDisable(GL_LIGHTING);
   
   int size_x = grid->getSizeX();
   int size_y = grid->getSizeY();
   //int size_z = grid->getSizeZ();

   float spacing = grid->getSpacing();

   // TODO: This is a stupid way of drawing grid
   glColor3f(0.2f, 0.2f, 0.2f);
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
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_TRIANGLES);
      triangles->GeometricPrimitive::render();
   glEnd();
}

void ColladaRendererGL::render(GeometricPrimitive* geometry) {
   DEBUG_H("ColladaRendererGL::render(GeometricPrimitive* geometry)");

   static int what;
   if(!what) {
      WARNING("Inefficient primitive rendering!, TODO: convert to vertex buffer object first!");
      what = 1;
   }

   PrimIterator iter = geometry->getFirstPrimitive();
   int inputCount = geometry->getInputCount();
   /*while(iter != geometry->getEndPrimitive()) {
      int primNum = geometry->getVertexNum(*iter);
      DEBUG_H("%d %d x=%f. y=%f, z=%f", *iter, primNum, geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glNormal3f(geometry->getNX(*iter), geometry->getNY(*iter), geometry->getNZ(*iter));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      iter+=inputCount;
   }*/
   
   int prim_num = 0;
   while(iter != geometry->getEndPrimitive()) {
      //glNormal3f(geometry->getNX(prim_num), geometry->getNY(prim_num), geometry->getNZ(prim_num));

      /*for(int i = 0; (i < inputCount) || (iter==geometry->getEndPrimitive()); i++) {
         DEBUG_M("%d", inputCount);
         glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
         iter++;
      }*/
      float x[3], y[3], z[3];
      
      
      float nx = geometry->getNX(*iter);
      float ny = geometry->getNY(*iter);
      float nz = geometry->getNZ(*iter);
      /*nx = 0.0;
      ny = 1.0;
      nz = 0.0;*/
      
      glNormal3f(nx, ny, nz);
      glBegin(GL_TRIANGLES);
      for(int i = 0; i < 3; i++) {
         x[i] = geometry->getX(*iter);
         y[i] = geometry->getY(*iter);
         z[i] = geometry->getZ(*iter);
         
         glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
         iter+=inputCount;
      }
      glEnd();
      
      glEnable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      //glDisable(GL_DEPTH_TEST);
      iter-=inputCount;
      
      glEnable(GL_COLOR_MATERIAL);
      for(int i = 0; i < 3; i++) {
         glBegin(GL_LINES);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(x[i], y[i], z[i]);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(x[i]+nx, y[i]+ny, z[i]+nz);
            
            /*glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
            glVertex3f(geometry->getX(*iter)+geometry->getNX(*iter),
               geometry->getY(*iter)+geometry->getNY(*iter),
               geometry->getZ(*iter)+geometry->getNZ(*iter));*/
               
            /*DEBUG_H("A: %f %f %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
            DEBUG_H("N: %f %f %f", geometry->getNX(*iter), geometry->getNY(*iter), geometry->getNZ(*iter));
            DEBUG_H("X: %f %f %f", geometry->getX(*iter)+geometry->getNX(*iter),
               geometry->getY(*iter)+geometry->getNY(*iter),
               geometry->getZ(*iter)+geometry->getNZ(*iter));*/
         glEnd();
      }
      //glEnable(GL_DEPTH_TEST);
      glDisable(GL_COLOR_MATERIAL);
      iter+=inputCount;
      glEnable(GL_LIGHTING);
   }
}

void ColladaRendererGL::render(InstanceGeometry* ig) {
   DEBUG_H("void ColladaRendererGL::render(InstanceGeometry* ig) {");
   shared_ptr<Geometry> geometry = ig->getGeometry();

   GeoPrimIterator iter = geometry->getFirstPrimitive();
   while(iter != geometry->getEndPrimitive()) {
      string material_s = (*iter)->getMaterial();

      #warning ['TODO']: Render a default grey material if none is found.
      if(!material_s.empty()) {
         shared_ptr<Material> material(ig->getInstanceMaterial(material_s));

         if(material.get() != NULL) {
            material->render();
         }
      }

      (*iter)->render();
      iter++;
   }
}

void ColladaRendererGL::render(Material* material) {
   DEBUG_H("void ColladaRendererGL::render(Material* material)");
   shared_ptr<Effect> effect = material->getEffect();
   effect->render();
}

void ColladaRendererGL::render(Phong* phong) {
   DEBUG_H("void ColladaRendererGL::render(Phong* phong)");
   const float (&ambient)[4] = phong->getAmbient().getArray();
   const float (&diffuse)[4] = phong->getDiffuse().getArray();
   const float (&specular)[4] = phong->getSpecular().getArray();
   const float (&emission)[4] = phong->getEmission().getArray();
   float shininess[1] = {phong->getShininess()};

   #warning ['TODO']: Apply per-pixel Phong shader...

   glDisable(GL_COLOR_MATERIAL);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   //const float ambient[4] = .getArray();
   //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, 
}

