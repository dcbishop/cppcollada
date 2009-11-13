#include "ViewWindow.hpp"

#include <iostream>
using namespace std;

#include "SDL.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "console.h"

#include "Renderable.hpp"
#include "Camera.hpp"
#include "Collada.hpp"
#include "ColladaRendererGL.hpp"

ViewWindow::ViewWindow(int width, int height) {
   width_ = width;
   height_ = height;

   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      cerr << "SDL: Failed to init video: " << SDL_GetError();
      throw "SDL init";
   }

   if(SDL_SetVideoMode(width_, height_, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
      cerr << "SDL: Failed to set video mode: " << SDL_GetError();
      SDL_Quit();
      throw "SDL setvideo";
   }
   position_ = shared_ptr<Position>(new Position);
   camera_ = shared_ptr<Camera>(new Camera);

   position_->setX(0.0f);
   position_->setY(-2.0f);
   position_->setY(-20.0f);
   
   grid_ = shared_ptr<Grid>(new Grid);
   cam_move_ = false;
}

void ViewWindow::setCollada(shared_ptr<Collada> collada) {
   collada_ = collada;
   collada_->setRenderer(&renderer_);
   /*if(camera_) {
      shared_ptr<Position> position = static_pointer_cast<Position, Collada>(collada);
      camera_->setTarget(position);
   }*/
}

void ViewWindow::setCamera(shared_ptr<Camera> camera) {
   camera_ = camera;
   camera_->setRenderer(&renderer_);
   camera_->setTarget(position_);
}

void ViewWindow::setTitle(const string title) {
   SDL_WM_SetCaption(title.c_str(), NULL);
}

void ViewWindow::setPerspective_() {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, width_ / height_, 0.1f, 10000.0f);
   glMatrixMode(GL_MODELVIEW);
}

 /**
 * Renders the scene using OpenGL.
 */
void ViewWindow::draw_() {
   static int frame = 0;
   static int last_render_time = 0;
   static int last_fps_time = 0;
   static bool limit_fps_ = true;
   static int fps_ = 0;
   static int mpf_ = 0;
   
   int current_time = getComputerTime();

   // Limit framerate
   if(limit_fps_ && !( (current_time - last_render_time) >= 1000/60) ) {
      return;
   }

   // Calculate FPS
   frame++;
   if(current_time - last_fps_time > 1000) {
      fps_ = frame*1000.0f/(current_time-last_fps_time);
      last_fps_time = current_time;
      frame = 0;
      LOG("FPS: %d,\tMPF: %d",fps_, mpf_);
   }
   last_render_time = current_time;

   setPerspective_();
   glLoadIdentity();
   camera_->render();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   grid_->render();

   if(collada_) {
      collada_->render();
   }

   glFlush();
   SDL_GL_SwapBuffers();

   mpf_ = getComputerTime() - current_time;
}

/**
 * Checks for any SDL events that have occured.
 */
void ViewWindow::checkEvents_() {
   SDL_Event event;
   while(SDL_PollEvent(&event)) {
      switch(event.type) {
         case SDL_QUIT:
            finished_ = true;
            break;
         case SDL_KEYDOWN:
            //handleKeyDown_(event);
            finished_ = true;
            break;
         case SDL_KEYUP:
            //handleKeyUp_(event);
            break;
         case SDL_MOUSEMOTION:
            mx_ = event.motion.x;
            my_ = event.motion.y;
            if(cam_move_) {
               camera_->setRotX(camera_->getRotX() + (GLfloat)event.motion.xrel / width_ * 100);
               camera_->setRotY(camera_->getRotY() - (GLfloat)event.motion.yrel / height_ * 100);
            }
            break;
         case SDL_MOUSEBUTTONDOWN:
            DEBUG_L("Mouse button %d down at (%d, %d)", event.button.button, event.button.x, event.button.y);

            if(event.button.button == 3) {
               cam_move_ = true;
            }
            break;
         case SDL_MOUSEBUTTONUP:
            DEBUG_L("Mouse button %d up at (%d, %d)", event.button.button, event.button.x, event.button.y);
            switch(event.button.button) {
               case 1:
                  //handleMouse1_(event);
                  break;
               case 2:
                  //handleMouse3_(event);
                  break;
               case 3:
                  cam_move_ = false;
                  break;
               case 5:
                  camera_->setZoom(camera_->getZoomTarget() + ZOOM_STEP);
                  break;
               case 4:
                  camera_->setZoom(camera_->getZoomTarget() - ZOOM_STEP);
                  break;
            }
            break;
         case SDL_VIDEORESIZE:
            //resizeEvent_(event);
            break;
         default:
            DEBUG_L("Unknown event occured...");
            break;
      }
   }
}

/**
 * The main rendering and input loop.
 */
void ViewWindow::mainLoop() {
   DEBUG_L("Interface::mainLoop()");

   while(!finished_) {
      checkEvents_();
      draw_();
   }
}

/**
 * Returns the current time that the interface has been running.
 * @return The time.
 */
int ViewWindow::getComputerTime() {
   return SDL_GetTicks();
}
