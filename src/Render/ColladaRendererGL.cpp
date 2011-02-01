#include "../Render/ColladaRendererGL.hpp"

#include "../Collada/Collada.hpp"
#include "../Collada/Scene.hpp"
#include "../Collada/VisualScene.hpp"
#include "../Collada/ColladaNode.hpp"
#include "../GameData/Position.hpp"
#include "../GameData/RotationGL.hpp"
#include "../Render/Renderable.hpp"
#include "../Collada/Triangles.hpp"
#include "../Collada/Geometry.hpp"
#include "../Collada/InstanceGeometry.hpp"
#include "../Collada/Material.hpp"
#include "../Collada/ColladaLitShader.hpp"
#include "../Collada/Phong.hpp"
#include "../Collada/Lambert.hpp"
#include "../Collada/Effect.hpp"
#include "../GameData/Grid.hpp"

#include "../GameObjects/GameObject.hpp"
#include "../GameObjects/ColladaMesh.hpp"
#include "../GameObjects/Area.hpp"
#include "../GameObjects/Camera.hpp"
#include "../GameObjects/Octree.hpp"

#include "../Debug/console.h"
#include "../Debug/TestRenderable.hpp"




#include <iostream>

void ColladaRendererGL::init() {
   LOG("Initilizing OpenGL renderer...");
   glewInit_ = false;
   defaultMaterial_.setRenderer(this);
   debugPrimDraw = -1;
   imageLoader_.init();
   glEnable(GL_MULTISAMPLE);
  // glutInit();

   LOG("Initilized OpenGL renderer...");
}

/**
 * OpenGL stuff to run prior to each drawing of the frame.
 */
void ColladaRendererGL::preFrame() {
	if(glewInit_ == false) {
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			ERROR("%s", glewGetErrorString(err));
		}
		DEBUG_M("GLEW inited version %s", glewGetString(GLEW_VERSION));
		glewInit_ = true;
	}
   setPerspective_();
   glLoadIdentity();
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   setPolygonMode_();
   setRenderMode_();
}

/**
 * OpenGL stuff to run after each drawing of the frame.
 */
void ColladaRendererGL::postFrame() {
   setRenderMode_();
   setPolygonMode_();
   glDisable(GL_CULL_FACE); //Cullface interfears with Qt for some reason
   glFlush();
   
   // Log any OpenGL errors.
   int glerrno = glGetError();
   if(glerrno) {
		const GLubyte *glerr = gluErrorString(glerrno);
		ERROR("OpenGL Error #%d: %s!", glerrno, glerr);
	}
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
   static bool nospam = false;
   if(!nospam) {
      WARNING("Tried to render raw ColladaObject '%s'", colladaObject->getId().c_str());
      nospam = true;
   }
}

void ColladaRendererGL::fixAxis_(const Collada* collada) {
   DEBUG_H("void ColladaRendererGL::fixAxis_(const Collada* collada) {");
   static const int Z_UP = 0;
   static const int X_UP = 1;
   static const int Y_UP = 2;

   #warning ['TODO']: Store and query axis from DAE file!
   int upAxis = Z_UP;

   if(upAxis == Z_UP) {
      //This seems to work for Z-Axis up
      glRotatef(90.f, -1.0f, 0.0f, 0.0f);
      glScalef(-1.0f, -1.0f, 1.0f);
   } else if(upAxis == Y_UP) {
      
   } else {
      
   }

}

void ColladaRendererGL::render(Area* area) {
   GameObjectIterator goi = area->getFirstGameObject();
   GameObjectIterator goie = area->getEndGameObject();

   while(goi != goie) {
      (*goi)->render();
      goi++;
   }
}

void ColladaRendererGL::render(GameObject* gameObject) {
   gameObject->Position::render();
   gameObject->RotationGL::render();
   gameObject->Scale::render();
}

void ColladaRendererGL::render(ColladaMesh* colladaMesh) {
   glPushMatrix();
      colladaMesh->GameObject::render();
      colladaMesh->getCollada()->render();
   glPopMatrix();
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

   VisualSceneIterator vsi = scene->getFirstVisualScene();
   VisualSceneIterator vsie = scene->getEndVisualScene();
   while(vsi != vsie) {
      (*vsi)->render();
      vsi++;
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

/**
 * Renders a devutting axis.
 */
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

/**
 * Applies transformation.
 */
void ColladaRendererGL::render(Position* position) {
   DEBUG_H("ColladaRendererGL::render(Position* position)");
   glTranslatef(position->getX(), position->getY(), position->getZ());
}

/**
 * Applies rotation.
 */
void ColladaRendererGL::render(RotationGL* rotation) {
   DEBUG_H("ColladaRendererGL::render(RotationGL* rotation)");
   float angle, x, y, z;
   for(int i = 0; i < 3; i++) {
      rotation->getRotationGL(i, x, y, z, angle);
      glRotatef(angle, x, y, z);
   }
}

/**
 * Applies scale.
 */
void ColladaRendererGL::render(Scale* scale) {
   DEBUG_H("ColladaRendererGL::render(Scale* scale)");
   glScalef(scale->getScaleX(), scale->getScaleY(), scale->getScaleZ());
}

/**
 * The render function for the base render class (shouldn't be called...).
 */
void ColladaRendererGL::render(Renderable* renderable) {
   DEBUG_H("ColladaRendererGL::render(Renderable* renderable)");
   //renderable->render();
}

/**
 * Renders a visible camera (For debugging).
 */
void ColladaRendererGL::render(Camera* camera) {
   DEBUG_H("void ColladaRendererGL::render(Camera* camera)");
   glPushMatrix();
      camera->GameObject::render();
      renderAxis_();
   glPopMatrix();
}

/**
 * Positions the camera for OpenGL.
 */
void ColladaRendererGL::setCamera(Camera* camera) {
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

   static int nospam;
   if(!nospam) {
      WARNING("Inefficient primitive rendering!, TODO: convert to vertex buffer object first!");
      nospam = 1;
   }

   // DEBUG: debugfun used to filter used to draw on a specific polygon number for testing purposes
   //static int debugfun = -1;
   //debugfun++;

   
   int vertexCount = geometry->getVertexCount();
   for(int i = 0; i < vertexCount; i++) {
      glTexCoord2f(geometry->getS(i), geometry->getT(i));
      glNormal3f(geometry->getNX(i), geometry->getNY(i), geometry->getNZ(i));
      glVertex3f(geometry->getX(i), geometry->getY(i), geometry->getZ(i));
   }

   // TODO: Move this bool somewhere else...
   bool renderNormals = false;
   if(!renderNormals) {
      return;
   }

   setUnlitMode_();
   glEnd();
   glEnable(GL_COLOR_MATERIAL);
   glColor4f(1.0, 0.0, 0.0, 1.0);
   glDisable(GL_TEXTURE_2D);
   glBegin(GL_LINES);
   //Render Normals
   for(int i = 0; i < vertexCount; i++) {
      glVertex3f(geometry->getX(i), geometry->getY(i), geometry->getZ(i));
      glVertex3f(geometry->getX(i) + geometry->getNX(i),
         geometry->getY(i)+geometry->getNY(i),
         geometry->getZ(i)+geometry->getNZ(i));
   }
   setLights_();
   setRenderMode_();
   return;

   //glEnd();
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
      //int vertexNum = geometry->getVertexNum(*iter);
      //int normalNum = geometry->getNormalNum(*iter+1);
      #warning ['TODO']: Plus input offset not +1...
      
      glBegin(GL_TRIANGLES);
      //DEBUG_M("%d VTX: %d, NML: %d", num, *iter, *(iter+1));
      glTexCoord2f(geometry->getS(*iter), geometry->getT(*iter));
      glNormal3f(geometry->getNX(*(iter)), geometry->getNY(*(iter)), geometry->getNZ(*(iter)));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      
      //DEBUG_M("X: %f, Y: %f, Z: %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //DEBUG_M("NX: %f, NY: %f, NZ: %f", geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      iter++;
      
      //DEBUG_M("%d VTX: %d, NML: %d", num, *iter, *(iter+1));
      glTexCoord2f(geometry->getS(*iter), geometry->getT(*iter));
      glNormal3f(geometry->getNX(*(iter)), geometry->getNY(*(iter)), geometry->getNZ(*(iter)));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      
      
      //DEBUG_M("X: %f, Y: %f, Z: %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //DEBUG_M("NX: %f, NY: %f, NZ: %f", geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      iter++;

      //DEBUG_M("%d VTX: %d, NML: %d", num, *iter, *(iter+1));
      glTexCoord2f(geometry->getS(*iter), geometry->getT(*iter));
      glNormal3f(geometry->getNX(*(iter)), geometry->getNY(*(iter)), geometry->getNZ(*(iter)));
      glVertex3f(geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));

      //DEBUG_M("X: %f, Y: %f, Z: %f", geometry->getX(*iter), geometry->getY(*iter), geometry->getZ(*iter));
      //DEBUG_M("NX: %f, NY: %f, NZ: %f", geometry->getNX(*(iter+1)), geometry->getNY(*(iter+1)), geometry->getNZ(*(iter+1)));
      glEnd();
      iter++;

      
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
   if(effect.get()) {
      effect->render();
   } else {
      static bool nospam = false;
      if(!nospam) {
         WARNING("Failed to load an Effect in Material '%s'. Future failed material load warnings will be supressed.", material->getId().c_str());
         nospam = true;
      }
   }
}

void ColladaRendererGL::render(TestRenderable* tr) {
   DEBUG_H("void ");
   tr->ColladaNode::render();
   renderCube_(tr->getScaleX());
}

void ColladaRendererGL::renderCube_(const float size) {
	// Render a cube from a VBO
	static GLuint cubeid = 0;
	static int offset = 0;
	if(cubeid == 0) {
		GLfloat vertices[] = {1,1,1,		-1,1,1,		-1,-1,1,		1,-1,1, //BACK OR FRONT
									 1,1,1,		1,-1,1,		1,-1,-1,  	1,1,-1, //LEFT
                            1,1,1,		1,1,-1,		-1,1,-1,  	-1,1,1, //TOP
                            -1,1,1,		-1,1,-1,		-1,-1,-1,  	-1,-1,1, // RIGHT
                            -1,-1,-1,	1,-1,-1,		1,-1,1,		-1,-1,1, // BOTTOM
                            1,-1,-1,	-1,-1,-1,	-1,1,-1, 	 1,1,-1 //FRONT
                            };

		GLfloat normals[] = {0,0,1,	0,0,1,   0,0,1,   0,0,1,
                           1,0,0,   1,0,0,   1,0,0,	1,0,0,
                           0,1,0,   0,1,0,   0,1,0,	0,1,0,
                           -1,0,0,  -1,0,0,	-1,0,0,  -1,0,0,
                           0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0,
                           0,0,-1,  0,0,-1,  0,0,-1,  0,0,-1
                           };
                           
		offset = sizeof(vertices);
      
      //cubeid = 1;               
		DEBUG_M("Initilizing cube VBO.");
		glGenBuffers(1, &cubeid);
		glBindBuffer(GL_ARRAY_BUFFER, cubeid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(normals), 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//setPolygonMode_();
	glBindBuffer(GL_ARRAY_BUFFER, cubeid);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glNormalPointer(GL_FLOAT, 0, (void*)offset);
	
	glDrawArrays(GL_QUADS, 0, 24);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Lazy cube
   float hsize = size/2;

   // Front faces
   float left_front_bottom[] = {-hsize, -hsize, -hsize};
   float right_front_bottom[] = {hsize, -hsize, -hsize};
   float left_back_bottom[] = {-hsize, hsize, -hsize};
   float right_back_bottom[] = {hsize, hsize, -hsize};

   // Back faces 
   float right_back_top[] = {hsize, hsize, hsize};
   float left_back_top[] = {-hsize, hsize, hsize};
   float left_front_top[] = {-hsize, -hsize, hsize};
   float right_front_top[] = {hsize, -hsize, hsize};

   setRenderMode_();
   glBegin(GL_QUADS);
      // Front face
      glNormal3f(0.0, -1.0, 0.0);
      glVertex3fv(left_front_bottom);
      glVertex3fv(right_front_bottom);
      glVertex3fv(right_front_top);
      glVertex3fv(left_front_top);

      // Back face
      glNormal3f(0.0, 1.0, 0.0);
      glVertex3fv(left_back_top);
      glVertex3fv(right_back_top);
      glVertex3fv(right_back_bottom);
      glVertex3fv(left_back_bottom);

      // Top face
      glNormal3f(0.0, 0.0, 1.0);
      glVertex3fv(left_front_top);
      glVertex3fv(right_front_top);
      glVertex3fv(right_back_top);
      glVertex3fv(left_back_top);

      // Bottom face
      glNormal3f(0.0, 0.0, -1.0);
      glVertex3fv(left_back_bottom);
      glVertex3fv(right_back_bottom);
      glVertex3fv(right_front_bottom);
      glVertex3fv(left_front_bottom);
      
      // Right face
      glNormal3f(1.0, 0.0, 0.0);
      glVertex3fv(right_front_bottom);
      glVertex3fv(right_back_bottom);
      glVertex3fv(right_back_top);
      glVertex3fv(right_front_top);

      // Left face
      glNormal3f(-1.0, 0.0, 0.0);
      glVertex3fv(left_front_top);
      glVertex3fv(left_back_top);
      glVertex3fv(left_back_bottom);
      glVertex3fv(left_front_bottom);
   glEnd();
	*/
}


void ColladaRendererGL::setRenderMode_() {
   glDisable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
}

void ColladaRendererGL::setUnlitMode_() {
   glDisable(GL_LIGHTING);
}

void ColladaRendererGL::setPolygonMode_() {
   glPolygonMode(GL_FRONT, GL_FILL);
   glFrontFace(GL_CCW);
   glCullFace(GL_BACK);
   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);
}

void ColladaRendererGL::setWireframeMode_() {
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   setUnlitMode_();
   glDisable(GL_CULL_FACE);
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

void ColladaRendererGL::render(ColladaLitShader* lit) {
   DEBUG_H("void ColladaRendererGL::render(Phong* phong)");

   setRenderMode_();

   const float (&ambient)[4] = lit->getAmbient().getArray();
   const float (&diffuse)[4] = lit->getDiffuse().getArray();
   const float (&emission)[4] = lit->getEmission().getArray();

   #warning ['TODO']: Apply per-pixel Phong shader...

   glColor4f(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

   if(lit->getTextureHack()) {
      int texid = lit->getTextureHackId();
      if(!texid) {
         texid = imageLoader_.loadImage(lit->getTextureHack());
         lit->setTextureHackId(texid);
      }
      if(texid > 0) {
         glBindTexture(GL_TEXTURE_2D, texid);
         glEnable(GL_TEXTURE_2D);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      } else {
         glDisable(GL_TEXTURE_2D);
      }
   } else {
      glBindTexture(GL_TEXTURE_2D, NULL); //TODO: C++0x nullptr
   }
}

void ColladaRendererGL::render(Phong* phong) {
   const float (&specular)[4] = phong->getSpecular().getArray();
   float shininess[1] = {phong->getShininess()};

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   phong->ColladaLitShader::render();
}

void ColladaRendererGL::render(Lambert* lambert) {
   lambert->ColladaLitShader::render();
}

void ColladaRendererGL::renderOctreeNode_(Octree* octree) {
   glEnable(GL_COLOR_MATERIAL);
   if(octree->getIsSolid()) {
      //setPolygonMode_();
      //glColor3f(0.0f, 1.0f, 0.0f);
      ColorRGBAPtr thecolor = octree->getColor();
      glColor3f(thecolor->getRed(), thecolor->getGreen(), thecolor->getBlue());
      renderCube_(1.0);
   } /*else {
      setWireframeMode_();
   }*/
   glDisable(GL_COLOR_MATERIAL);

}

void ColladaRendererGL::render(Octree* octree) {
   glPushMatrix();

	setPolygonMode_();
   octree->GameObject::render();
   
   if(octree->getHasChildren()) {
      for(int i = 0; i < 8; i++) {
         OctreePtr child = octree->getChild(i);
         if(child != OctreePtr()) {
            glPushMatrix();
            glScalef(0.5, 0.5, 0.5);

            // Left/Right offset
            if(i == 0 || i == 2 || i == 4 || i == 6) {
               glTranslatef(0.5, 0.0, 0.0);
            } else {
               glTranslatef(-0.5, 0.0, 0.0);
            }

            // Up/Down
            if(i == 0 || i == 1 || i == 4 || i == 5) {
               glTranslatef(0.0, -0.5, 0.0);
            } else {
               glTranslatef(0.0, 0.5, 0.0);
            }

            // Front/Back
            if(i >= 4) {
               glTranslatef(0.0, 0.0, 0.5);
            } else {
               glTranslatef(0.0, 0.0, -0.5);
            }

            child->render();
            glPopMatrix();
         }
      }
   }
   renderOctreeNode_(octree);

   glPopMatrix();
}
