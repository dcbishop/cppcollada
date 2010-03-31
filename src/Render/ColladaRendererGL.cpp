#include "../Render/ColladaRendererGL.hpp"

#include "../Collada/Collada.hpp"
#include "../Collada/Scene.hpp"
#include "../Collada/VisualScene.hpp"
#include "../Collada/ColladaNode.hpp"
#include "../GameData/Position.hpp"
#include "../GameData/RotationGL.hpp"
#include "../Render/Renderable.hpp"
#include "../GameData/Camera.hpp"
#include "../Collada/Triangles.hpp"
#include "../Collada/Geometry.hpp"
#include "../Collada/InstanceGeometry.hpp"
#include "../Collada/Material.hpp"
#include "../Collada/Phong.hpp"
#include "../GameData/Grid.hpp"

#include "../Debug/console.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

void ColladaRendererGL::init() {
   defaultMaterial_.setRenderer(this);
   debugPrimDraw = -1;
   glEnable(GL_MULTISAMPLE);
}

/**
 * OpenGL stuff to run prior to each drawing of the frame.
 */
void ColladaRendererGL::preFrame() {
   setPerspective_();
   glLoadIdentity();
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * OpenGL stuff to run after each drawing of the frame.
 */
void ColladaRendererGL::postFrame() {
   glFlush();
}

/**
 * Set the size of the OpenGL renderer.
 */
void ColladaRendererGL::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
   DEBUG_M("setSize(%d, %d)=%f", width, height, width_ / height_);
   //TODO: Set perspective here? or just let the next frame update do it?
}

void ColladaRendererGL::setPerspective_() {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0f, 1.0 * width_ / height_, 0.1f, 10000.0f);
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

void ColladaRendererGL::render(Collada* collada) {
   DEBUG_H("ColladaRendererGL::render(Collada* collada)");

   glPushMatrix();
   fixAxis_(collada);

   glEnable(GL_DEPTH_TEST);
   setRenderMode_();
   setPolygonMode_();

   setLights_();


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
   glColor3f(1.0, 1.0, 1.0);
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

   setUnlitMode_();
   
   int size_x = grid->getSizeX();
   int size_y = grid->getSizeY();
   //int size_z = grid->getSizeZ();

   float spacing = grid->getSpacing();

   // TODO: This is a stupid way of drawing grid. Add Z grid.
   glColor3f(grid->getRed(), grid->getGreen(), grid->getBlue());
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

   // DEBUG: debugfun used to filter used to draw on a specific polygon number for testing purposes
   //static int debugfun = -1;
   //debugfun++;

   glEnd();
   int num = -1;
   PrimIterator iter = geometry->getFirstPrimitive();
   int inputCount = geometry->getInputCount();
   while(iter != geometry->getEndPrimitive()) {
      num++;
      
      //if(num != debugfun) {iter+=inputCount*3; continue;}; //DEBUG: Draw a specific prim number...
      
      /*int primNum = geometry->getVertexNum(*iter);
      DEBUG_H("%d %d x=%f. y=%f, z=%f", *iter, primNum, geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glNormal3f(geometry->getNX(*iter), geometry->getNY(*iter), geometry->getNZ(*iter));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      iter+=inputCount;*/
      int vertexNum = geometry->getVertexNum(*iter);
      //int normalNum = geometry->getNormalNum(*iter+1);
      #warning ['TODO']: Plus input offset not +1...
      
      glBegin(GL_TRIANGLES);
      //DEBUG_M("%d VTX: %d, NML: %d", num, *iter, *(iter+1));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glNormal3f(geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      //DEBUG_M("X: %f, Y: %f, Z: %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //DEBUG_M("NX: %f, NY: %f, NZ: %f", geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      iter+=inputCount;
      
      //DEBUG_M("%d VTX: %d, NML: %d", num, *iter, *(iter+1));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glNormal3f(geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      //DEBUG_M("X: %f, Y: %f, Z: %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //DEBUG_M("NX: %f, NY: %f, NZ: %f", geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      iter+=inputCount;

      //DEBUG_M("%d VTX: %d, NML: %d", num, *iter, *(iter+1));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glNormal3f(geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      //DEBUG_M("X: %f, Y: %f, Z: %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //DEBUG_M("NX: %f, NY: %f, NZ: %f", geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      glEnd();
      iter+=inputCount;

      
      // DEBUG DRAW NORMAL LINES!
      if(num != debugPrimDraw) {continue;}; //DEBUG: Draw a specific prim number...
      //continue;
      iter-=inputCount*3;
      setUnlitMode_();
      glEnable(GL_COLOR_MATERIAL);
      glColor3f(1.0,0,0);
      
      glBegin(GL_LINES);
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glVertex3f(geometry->getX(*iter)+geometry->getNX(*(iter+1)),
               geometry->getY(*iter)+geometry->getNY(*(iter+1)),
               geometry->getZ(*iter)+geometry->getNZ(*(iter+1)));
      glEnd();
      iter+=inputCount;
      glBegin(GL_LINES);
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glVertex3f(geometry->getX(*iter)+geometry->getNX(*(iter+1)),
               geometry->getY(*iter)+geometry->getNY(*(iter+1)),
               geometry->getZ(*iter)+geometry->getNZ(*(iter+1)));
      glEnd();
      iter+=inputCount;
      glBegin(GL_LINES);
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glVertex3f(geometry->getX(*iter)+geometry->getNX(*(iter+1)),
               geometry->getY(*iter)+geometry->getNY(*(iter+1)),
               geometry->getZ(*iter)+geometry->getNZ(*(iter+1)));
      glEnd();
      iter+=inputCount;

      glDisable(GL_COLOR_MATERIAL);
      setRenderMode_();

   }
}
#if 0
   PrimIterator iter = geometry->getFirstPrimitive();
   int inputCount = geometry->getInputCount();
   /*while(iter != geometry->getEndPrimitive()) {
      int primNum = geometry->getVertexNum(*iter);
      DEBUG_H("%d %d x=%f. y=%f, z=%f", *iter, primNum, geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      glNormal3f(geometry->getNX(*iter), geometry->getNY(*iter), geometry->getNZ(*iter));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      iter+=inputCount;
   }*/
   glEnable(GL_NORMALIZE);
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
      
      
      //glDisable(GL_LIGHTING);
      //glDisable(GL_DEPTH_TEST);
      iter-=inputCount;
      
#if 0
      //glEnable(GL_COLOR_MATERIAL);
      //for(int i = 0; i < 3; i++) {
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

#endif
      iter+=inputCount;
      //glEnable(GL_LIGHTING);

   }
}
#endif

void ColladaRendererGL::render(InstanceGeometry* ig) {
   DEBUG_H("void ColladaRendererGL::render(InstanceGeometry* ig) {");
   shared_ptr<Geometry> geometry = ig->getGeometry();

   GeoPrimIterator iter = geometry->getFirstPrimitive();
   while(iter != geometry->getEndPrimitive()) {
      string material_s = (*iter)->getMaterial();

      if(!material_s.empty()) {
         shared_ptr<Material> material(ig->getInstanceMaterial(material_s));

         if(material.get() != NULL) {
            material->render();
         } else {
            renderDefaultMaterial_();
         }
      } else {
         renderDefaultMaterial_();
      }

      (*iter)->render();
      iter++;
   }
}

void ColladaRendererGL::renderDefaultMaterial_() {
   defaultMaterial_.render();
}

void ColladaRendererGL::render(Material* material) {
   DEBUG_H("void ColladaRendererGL::render(Material* material)");
   shared_ptr<Effect> effect = material->getEffect();
   effect->render();
}

void ColladaRendererGL::setRenderMode_() {
   glDisable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

void ColladaRendererGL::setUnlitMode_() {
   glDisable(GL_LIGHTING);
}

void ColladaRendererGL::setPolygonMode_() {
   glPolygonMode(GL_FRONT, GL_FILL);
   //glEnable(GL_CULL_FACE);
   glCullFace(GL_FRONT);
   glFrontFace(GL_CW);
}

/**
 * Setup the lights. This is currently a fixed light for debugging purposes.
 */
#warning ['TODO']: Use actual lights...
void ColladaRendererGL::setLights_() {
   // DEBUG: Move the light up, render some axis
   //static float debugPos = 1.0f;
   //debugPos+=0.01;
   glDisable(GL_LIGHTING);
   glPushMatrix();

   float lx = -2.0;
   float ly = -2.0;
   float lz = 2.0;
   //float lz = debugPos;
   
   glTranslatef(lx, ly, lz);
   renderAxis_();
   glPopMatrix();

   float light_pos[] = {lx, ly, lz, 1.0};
   glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
}

void ColladaRendererGL::render(Phong* phong) {
   DEBUG_H("void ColladaRendererGL::render(Phong* phong)");

   setRenderMode_();

   const float (&ambient)[4] = phong->getAmbient().getArray();
   const float (&diffuse)[4] = phong->getDiffuse().getArray();
   const float (&specular)[4] = phong->getSpecular().getArray();
   const float (&emission)[4] = phong->getEmission().getArray();
   float shininess[1] = {phong->getShininess()};

   #warning ['TODO']: Apply per-pixel Phong shader...

   glColor4f(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   //const float ambient[4] = .getArray();
   //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, 
}

